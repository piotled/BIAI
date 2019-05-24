#pragma once

#include <fstream>
#include <defines.h>
#include "layer.h"
#include "IDoubleSource.h"

namespace BIAI {


	/*
		Class representing a given type of neural network. 
		Is responsible for managing structure of nn.
	*/

	class Perceptron {
		//Sources of weights and tresholds used to build network
		IDoubleSource * weightSource;
		IDoubleSource * tresholdSource;
		//Stores number of inputs
		uint inputCount;
		//Stores layers
		std::vector<Layer> layers; 
		//Buffer for input values
		std::vector<double> inputBuffer;
		/*
			Constructs network, creates layers and neurons. Throws exceptions if structure is not correct
		*/
		void constructNet(std::vector<uint> layerElementNumbers);
		/*
			Connects neurons to each other, creates initial weights
		*/
		void connectNet();
	public:
		/*
			Constructs a network composed of a number of layers equal to number of elements in argument vector object.
			First element corresponds to input layer, and last to output layer.

			Throws exception if number of elements in "layerElementNumbers" is not correct or if any of those numbers is 0.
		*/
		Perceptron(std::vector<uint> layerElementNumbers);

		/*
			Recreates a network from data stored in specified file

			Throws exception if read data is in any way incorrect.
		*/
		Perceptron(std::string fileName);

		/*
			Performs calculations. Returns vector of output values. Throws exception if vector under address provided in argument contains 
			number of values that doesn't match number of network inputs.
		*/
		std::vector<double> operator()(const std::vector<double> & inputValues);
		std::vector<double> calc(const std::vector<double> & inputValues);
		/*
			Gives access to layer
		*/
		Layer * operator[](uint i) {
			if (i > layers.size() - 1)
				return nullptr;
			return &layers[i];
		}
		/*
			Writes information about neural network to specified file. Returns false if unable to open file.
		*/
		bool save(std::string fileName);
		/*
			Returns layer count
		*/
		uint getLayerCount() {
			return layers.size();
		}
	};



}
