#include "perceptron.h"
#include "nnstructureerror.h"
#include "nnruntimeerror.h"
#include "sigmoid.h"
#include "DoubleGenerator.h"
#include "DoubleReader.h"

namespace BIAI {

	/*
		ctors
	*/

	Perceptron::Perceptron(std::vector<uint> layerElementNumbers)
	{
		weightSource = new DoubleGenerator(-1, 1);
		tresholdSource = new DoubleGenerator(-1, 1);
		constructNet(layerElementNumbers);
	}

	Perceptron::Perceptron(std::string fileName)
	{
		//Open file in binary mode
		std::ifstream inputFile(fileName, std::ios::in | std::ios::binary);
		//Read number of unsigned integer elements describing network structure
		uint tmp;
		inputFile.read((char *)&tmp, sizeof(tmp));
		//Read network description to vector
		std::vector<uint> netDesc;
		netDesc.resize(tmp);
		for (int i = 0; i < tmp; i++) {
			inputFile.read((char *)&netDesc[i], sizeof(uint));
		}
		//Create treshold source
		tresholdSource = new DoubleReader(inputFile);
		//Create weight source
		weightSource = new DoubleReader(inputFile);
		constructNet(netDesc);
	}

	/*
		methods
	*/

	void Perceptron::constructNet(std::vector<uint> layerElementNumbers) {
		//Check if amount of arguments is correct
		if (layerElementNumbers.size() < 2) //At least one layer + number of inputs, so at least 2 arguments
			throw NNStructureError("Too few layers");
		else {
			//Prepare iterator
			std::vector<uint>::iterator it = layerElementNumbers.begin();

			if (*it > 0) { //Check if number of inputs is greater than 0
				inputCount = *(it++); //Save number of inputs
				inputBuffer.resize(inputCount);//Reserve space for input values
				while (it != layerElementNumbers.end()) { //As long as there are elements in argument list 
					//Create layer
					layers.push_back(Layer(*(it++), weightSource, tresholdSource)); //Construct layer with given number of neurons
				}
				connectNet(); //Connect neurons to each other
				delete weightSource; //Deallocates space used for network construction objects
				delete tresholdSource;
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



	std::vector<double> Perceptron::operator()(const std::vector<double> & inputValues) { //Gets vector containing input values for network
		return calc(inputValues);
	}

	std::vector<double> Perceptron::calc(const std::vector<double>& inputValues)
	{
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

	bool Perceptron::save(std::string fileName)
	{
		std::ofstream outputFile(fileName, std::ios::out | std::ios::binary | std::ios::trunc); //Open file in binary mode
		if (outputFile.is_open()) { //Continue if file opened succesfully
			//First, save network structure descritption in form of layer count and layer element count numbers
			uint tmp = layers.size() + 1; //Save integer data count. Layer count + 1 for input buffer 
			outputFile.write((const char *)&tmp, sizeof(tmp));
			//Write sizes of input buffer and layers
			tmp = inputBuffer.size();
			outputFile.write((const char *)&tmp, sizeof(tmp));
			for (int i = 0; i < layers.size(); i++) {
				tmp = layers[i].getNeuronCount();
				outputFile.write((const char *)&tmp, sizeof(tmp));
			}
			//Write tresholds of every neuron in layer starting from first to last
			for (int i = 0; i < layers.size(); i++) {
				for (int j = 0; j < layers[i].getNeuronCount(); j++) {
					double tmp = layers[i][j]->getTreshold();
					outputFile.write((const char *)&tmp, sizeof(tmp));
				}
			}
			//Write every weight value starting from first neuron in last layer to last neuron in first layer
			for (int i = layers.size() - 1; i >= 0 ; i--) {
				for (int j = 0; j < layers[i].getNeuronCount(); j++) {
					const std::vector<double> & weights = layers[i][j]->getWeights();
					for (int k = 0; k < weights.size(); k++) {
						double tmp = weights[k];
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

}