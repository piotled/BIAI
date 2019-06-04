#pragma once

#include <fstream>
#include <defines.h>
#include "INet.h"

namespace NN {

	/*
		Class representing a perceptron
		Is responsible for managing structure of nn.
	*/

	class Perceptron : public INet {
		//Sources of weights and tresholds used to build network
		IFloatSource * weightSource;
		//Stores number of inputs
		uint inputCount;
		//Stores layers
		std::vector<Layer> layers; 
		//Buffer for input values
		std::vector<float> inputBuffer;
		/*
			Constructs network, creates layers and neurons. Throws exceptions if structure is not correct
		*/
		void constructNet(std::vector<uint> layerElementNumbers);
		/*
			Connects neurons to each other, creates initial weights
		*/
		void connectNet();
	protected:
		/*
			Gives access to layer
		*/
		Layer * operator[](uint i) override {
			if (i > layers.size() - 1)
				return nullptr;
			return &layers[i];
		}
	public:
		
		/*
			Constructs a network composed of a number of layers equal to number of elements in argument vector object.
			First element corresponds to input layer(input buffer), and last to output layer.

			Throws exception if number of elements in "layerElementNumbers" is not correct or if any of those numbers is 0.
		*/
		Perceptron(std::vector<uint> layerElementNumbers);

		/*
			Recreates a network from data stored in specified file

			Throws exception if read data is in any way incorrect.
		*/
		Perceptron(std::string fileName);

		~Perceptron() override {}

		/*
			Performs calculations. Returns vector of output values. Throws exception if vector under address provided in argument contains 
			number of values that doesn't match number of network inputs.
		*/
		std::vector<float> calculate(const std::vector<float> & inputValues) override;

		/*
			Writes information about neural network to specified file. Returns false if unable to open file.
		*/
		bool save(std::string fileName) override;
		/*
			Returns layer count
		*/
		uint getLayerCount() override {
			return layers.size();
		}
		/*
			Returns network description in form of string.
		*/
		std::string description() override;
	};



}


