#include "perceptron.h"
#include "nnstructureerror.h"
#include "nnruntimeerror.h"
#include "sigmoid.h"


namespace BIAI {

	Perceptron::Perceptron(std::initializer_list<uint> layerElementNumbers)
	{
		//Check if amount of arguments is correct
		if (layerElementNumbers.size() < 2) //At least one layer + number of inputs, so at least 2 arguments
			throw NNStructureError("Too few layers");
		else {
			//To construct a perceptron, first create acitivation function
			activationFunction = new Sigmoid(); //Default is sigmoid

			//Prepare iterator
			std::initializer_list<uint>::iterator it = layerElementNumbers.begin();

			if (*it > 0) { //Check if number of inputs is greater than 0
				inputCount = *(it++); //Save number of inputs
				inputBuffer.resize(inputCount);//Reserve space for input values
				while (it != layerElementNumbers.end()) { //As long as there are elements in argument list 
					//Create layer
					layers.push_back(Layer(*(it++), &activationFunction)); //Construct layer with given number of neurons
				}
				connectNet(); //Connect neurons to each other
				return;
			}
			throw NNStructureError("Invalid number of inputs");
		}
	}

	void Perceptron::connectNet() {
		/*
			Starting from last layer, connect outputs of neurons in previous layer to inputs of neurons in current layer
		*/
		for (int layerIndex = layers.size() - 1; layerIndex > 0; layerIndex--) { //For each layer except first one
			for (int neuronIndex = 0; neuronIndex < layers[layerIndex].getNeuronCount(); neuronIndex++) { //For each neuron in layer
				for (int previousLayerNeuronIndex = 0; previousLayerNeuronIndex < layers[layerIndex - 1].getNeuronCount(); previousLayerNeuronIndex++) { //For each neuron in previous layer 
					layers[layerIndex][neuronIndex]->connectInput(layers[layerIndex - 1][previousLayerNeuronIndex]); //Connect neuron in previous layer to neuron in current layer
				}
			}
		}
		/*
			Connect input buffer to first layer
		*/
		for (int neuronIndex = 0; neuronIndex < layers[0].getNeuronCount(); neuronIndex++) { //For each neuron in first layer
			for (int i = 0; i < inputBuffer.size(); i++) { //For each input 
				layers[0][neuronIndex]->connectInput(&inputBuffer[i]); //Connect input to neuron
			}
		}
	}

	Perceptron::~Perceptron() {
		delete activationFunction; //Deallocate activation function object TODO(if external actfun change to avoid problems)
	}

	std::vector<double> Perceptron::operator()(const std::vector<double> & inputValues) { //Gets vector containing input values for network
		//Check if number length of input vector is correct
		if (inputValues.size() != inputCount) throw NNRuntimeError("Length of input vector doesn't mach input count");
		//Copy values to input buffer
		for (int i = 0; i < inputBuffer.size(); i++) {
			inputBuffer[i] = inputValues[i];
		}
		for (int i = 0; i < layers.size(); i++) { //For each layer
			layers[i].calculate(); //Calculate output values
		}

		return layers[layers.size() - 1].getOutputVector(); //Return results from last layer
	}

}