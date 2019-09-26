#include "perceptron.h"
#include "StructureException.h"
#include "RuntimeException.h"
#include "Sigmoid.h"
#include "floatGenerator.h"
#include "floatReader.h"

namespace NN {

	/*
		ctors
	*/

	Perceptron::Perceptron(std::vector<uint> layerElementNumbers)
	{
		weightSource = new floatGenerator(-1, 1);
		constructNet(layerElementNumbers);
	}

	Perceptron::Perceptron(std::string fileName)
	{
		//Open file in binary mode
		std::ifstream inputFile(fileName, std::ios::in | std::ios::binary);
		//Read first byte in file. It stores net type ifentifier
		if (inputFile.good()) {
				//Read 32 bit unsigned int from file. It should contain number of layers (with input buffer)
				uint layerCount;
				inputFile.read((char *)&layerCount, sizeof(layerCount));
				if (inputFile.good()) {
					std::vector<uint> netDesc; //Prepare vector to which numbers of layer elements will be read
					netDesc.resize(layerCount); //Allocate memory
					for (int i = 0; i < layerCount; i++) { //Read unsigned int values (numbers of neurons in layers) from file
						inputFile.read((char *)&netDesc[i], sizeof(uint));
					}
					//Check if file ok
					if (inputFile.good()) {
						//Create weight source (pass file stream to object that reads floats from it)
						weightSource = new floatReader(inputFile);
						constructNet(netDesc);
						return;
					}
 				}
			else {
				throw StructureException("File does not store perceptron nn");
			}
		}
		//If gets here, this means that file is too short or other file error occured
		throw StructureException("File too short or other file associated error");
	}

	/*
		methods
	*/

	void Perceptron::constructNet(std::vector<uint> layerElementNumbers) {
		//Check if amount of arguments is correct
		if (layerElementNumbers.size() < 2) //2 elements mandatory, 1st is number of network inputs and second is number of elements in first layer
			throw StructureException("Too few layers");
		else {
			std::vector<uint>::iterator it = layerElementNumbers.begin();

			if (*it > 0) { //Check if number of inputs is greater than 0
				inputCount = *(it++); //Save number of inputs
				inputBuffer.resize(inputCount);//Reserve space for input values
				while (it != layerElementNumbers.end()) { //As long as there are elements in argument list 
					//Create layer
					layers.push_back(Layer(*(it++), weightSource)); //Construct layer with given number of neurons
				}
				connectNet(); //Connect neurons to each other
				delete weightSource; //Deallocates space used for network construction objects
				return;
			}
			throw StructureException("Invalid number of inputs");
		}
	}


	void Perceptron::connectNet() {
		/*
			Starting from last layer, connect outputs of neurons in previous layer to inputs of neurons in current layer
		*/
		for (int layerIndex = layers.size() - 1; layerIndex > 0; layerIndex--) { //For each layer except first one
			uint layerElements = layers[layerIndex].getNeuronCount();
			for (int neuronIndex = 0; neuronIndex < layerElements; neuronIndex++) { //For each neuron in layer
				uint previousLayerElements = layers[layerIndex - 1].getNeuronCount();
				for (int previousLayerNeuronIndex = 0; previousLayerNeuronIndex < previousLayerElements;  previousLayerNeuronIndex++) { //For each neuron in previous layer 
					layers[layerIndex][neuronIndex]->connectInput(layers[layerIndex - 1][previousLayerNeuronIndex]); //Connect neuron in previous layer to neuron in current layer
				}
				//After connecting all neurons to current neuron, connect additional non-existent neuron. It creates value equal to 1 that acts as an input associated with bias;
				layers[layerIndex][neuronIndex]->connectInput((Neuron*)nullptr);
			}
		}
		/*
			Connect input buffer to first layer
		*/
		for (int neuronIndex = 0; neuronIndex < layers[0].getNeuronCount(); neuronIndex++) { //For each neuron in first layer
			for (int i = 0; i < inputBuffer.size(); i++) { //For each input 
				layers[0][neuronIndex]->connectInput(&inputBuffer[i]); //Connect input to neuron
			}
			layers[0][neuronIndex]->connectInput((Neuron*)nullptr);
		}
	}

	std::vector<float> Perceptron::calculate(const std::vector<float>& inputValues)
	{
		//Check if number length of input vector is correct
		if (inputValues.size() != inputCount) throw RuntimeException("Length of input vector doesn't match input count");
		//Copy values to input buffer
		for (int i = 0; i < inputBuffer.size(); i++) {
			inputBuffer[i] = inputValues[i];
		}
		for (int i = 0; i < layers.size(); i++) { //For each layer
			layers[i].calculate(); //Calculate output values
		}

		return layers[layers.size() - 1].getOutputVector(); //Return results from last layer
	}

	bool Perceptron::save(std::string fileName)
	{
		std::ofstream outputFile(fileName, std::ios::out | std::ios::binary | std::ios::trunc); //Open file in binary mode
		if (outputFile.is_open()) { //Continue if file opened succesfully
			//Write byte value containing network type identifie

			//Write unsigned int value containing number of layers (includes input buffer)
			uint layerCount = layers.size() + 1;
			outputFile.write((const char *)&layerCount, sizeof(layerCount));
			//Write sizes of input buffer and layers
			uint sizeValue = inputBuffer.size();
			outputFile.write((const char *)&sizeValue, sizeof(sizeValue));
			for (int i = 0; i < layers.size(); i++) {
				sizeValue = layers[i].getNeuronCount();
				outputFile.write((const char *)&sizeValue, sizeof(sizeValue));
			}
			//Write every weight value starting from first neuron in last layer to last neuron in first layer
			for (int i = layers.size() - 1; i >= 0 ; i--) {
				for (int j = 0; j < layers[i].getNeuronCount(); j++) {
					const std::vector<float> & weights = layers[i][j]->getWeights(); //Contains bias
					for (int k = 0; k < weights.size(); k++) {
						float tmp = weights[k];
						outputFile.write((const char *)&tmp, sizeof(tmp));
					}
				}
			}
			if (outputFile.good()) {
				outputFile.close();
				return true;
			}
			else {
				outputFile.close();
				return false;
			}
		}
		else return false;
	}

	std::string Perceptron::description()
	{
		return std::string();
	}

}