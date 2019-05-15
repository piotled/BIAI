#include "layer.h"
#include "nnstructureerror.h"
#include <thread> 

namespace BIAI {

	Layer::Layer(uint neuronCount, ActivationFunction ** actFunAddr) : neuronCount(neuronCount) {
		if (neuronCount == 0)
			throw NNStructureError("Invalid neuron count in layer");
		else {
			/*
				FIlling vector of neurons in layer. Neurons use activation function
				under specified address
			*/
			for (int i = 0; i < neuronCount; i++) {
				neurons.push_back(new Neuron(actFunAddr));
			}
		}
	}

	Layer::Layer(Layer && source) {
		neurons = source.neurons;
		neuronCount = source.neuronCount;
		for (int i = 0; i < neurons.size(); i++) {
			source.neurons[i] = nullptr;
		}
	}

	Layer::~Layer() {
		for (int i = 0; i < neuronCount; i++) {
			delete neurons[i];
		}
	}

	void Layer::calculate() {
		/*
			An array of pointers to std::thread objects. Grants access to each thread object created.
		*/
		std::thread ** threads = new std::thread *[neuronCount];
		/*
			For every neuron spawn new thread
		*/
		for (int i = 0; i < neuronCount; i++) {
			//Spawn new thread. Args: address of method, address of object
			threads[i] = new std::thread(&Neuron::operator(), neurons[i]);
		}
		/*
			Wait until every thread finishes
		*/
		for (int i = 0; i < neuronCount; i++) {
			threads[i]->join();
			delete threads[i]; //Delete thread object because it is no longer needed.
		}
		delete[] threads; //Delete thread array
	}

	std::vector<double> Layer::getOutputVector()
	{
		std::vector<double> outputVector; //Prepare vector
		for (int i = 0; i < neuronCount; i++) { //For each neuron in layer
			outputVector.push_back(neurons[i]->value()); //Assign neuron value to outputVector
		}
		return outputVector;
	}

	Neuron * Layer::operator[](uint position)
	{
		if (position > neuronCount - 1) return nullptr;
		else return neurons[position];
	}

}