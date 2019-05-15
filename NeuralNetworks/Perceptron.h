#pragma once

#include <fstream>
#include <defines.h>
#include "layer.h"

namespace BIAI {


	/*
		Class representing a given type of neural network. 
		Is responsible for managing structure of nn.
	*/

	class Perceptron {
		//Stores number of inputs
		uint inputCount;
		//Stores layers
		std::vector<Layer> layers; 
		//Buffer for input values
		std::vector<double> inputBuffer;
		//Activation function pointer
		ActivationFunction * activationFunction;
		/*
			Connects neurons to each other, creates initial weights
		*/
		void connectNet();
	public:
		/*
			Constructs a network composed of a number of layers equal to number of elements in initializer_list object.
			First element corresponds to input layer, and last to output layer.

			Throws exception if number of elements in "layerElementNumbers" is not correct or if any of those numbers is 0.
		*/
		Perceptron(std::initializer_list<uint> layerElementNumbers);

		/*
			Recreates a network previously saved from data read from specified source.

			Throws exception if read data is in any way incorrect.
		*/
		//Perceptron(std::ifstream & source);

		/*
			Deallocates memory.
		*/
		~Perceptron();
		/*
			Performs calculations. Returns vector of output values. Throws exception if vector under address provided in argument contains 
			number of values that doesn't match number of network inputs.
		*/
		std::vector<double> operator()(const std::vector<double> & inputValues);
		/*
			Writes information about neural network to provided output stream. Allows to recreate network.
		*/
		//bool save(std::ostream & output);
	};



}
