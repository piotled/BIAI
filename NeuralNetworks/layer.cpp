#include "Layer.h"
#include "StructureException.h"
#include "ThreadBlockWrapper.h"

namespace NN {

	Layer::Layer(uint neuronCount, IFloatSource * weightSource) : neuronCount(neuronCount) {
		if (neuronCount == 0)
			throw StructureException("Invalid neuron count in layer");
		else {

			/*
				FIlling vector of neurons in layer. 
			*/
			for (int i = 0; i < neuronCount; i++) {
				neurons.push_back(new Neuron(weightSource));
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
		uint posiibleThreads = std::thread::hardware_concurrency() * 2; //Name a bit incorrect. It is number of physical cores * 2
		if (neuronCount < posiibleThreads) {
			for (int i = 0; i < neuronCount; i++) {
				neurons[i]->calculate();
			}
		}
		else {
			ThreadBlockWrapper threadBlock(posiibleThreads);
			//Divide neurons into groups. Number of groups equal to numbers of possible threads.
			uint res = neuronCount % posiibleThreads; //Residual - in case when neuronCount is not divible by possible thread count 
			uint groupCapacity = (posiibleThreads - res + neuronCount) / posiibleThreads; //Maximum group capactity. If res != 0, remaining space in last group wont be used.
			uint rangeStart = 0;
			uint rangeEnd = rangeStart + groupCapacity - 1;
			while (rangeStart < neuronCount) { //Stop when all possible threads are created
				threadBlock.save(new std::thread(&Layer::calculateInRange, this, rangeStart, rangeEnd < neuronCount ? rangeEnd : neuronCount - 1));
				rangeStart += groupCapacity;
				rangeEnd += groupCapacity;
			}
		}

	}

	void Layer::calculateInRange(uint rangeStart, uint rangeEnd) {
		for (uint i = rangeStart; i <= rangeEnd; i++) {
			neurons[i]->calculate();
		}
	}

	std::vector<float> Layer::getOutputVector()
	{
		std::vector<float> outputVector; //Prepare vector
		for (int i = 0; i < neuronCount; i++) { //For each neuron in layer
			outputVector.push_back(neurons[i]->getValue()); //Assign neuron getValue to outputVector
		}
		return outputVector;
	}

	Neuron * Layer::operator[](uint position)
	{
		if (position > neuronCount - 1) return nullptr;
		else return neurons[position];
	}

}