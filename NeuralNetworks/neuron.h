#pragma once

#include <defines.h>
#include <vector>
#include "IFloatSource.h"
#include "Sigmoid.h"

namespace NN {

	/*
		Class responsible for calculating an output getValue of a neuron from provided input arguments and weights stored in this object.
	*/
	class Neuron {
		//Value for input associated with bias, set to 1.0
		float biasInput;
		//Sources for weights and tresholds
		IFloatSource * weightSource;
		//Activation function
		Sigmoid actFun;
		//Vector of pointers to variables storing outputs of neurons from previous layer that are connected to this neuron
		std::vector<const float *> inputs;
		//Vector of weights for each connection
		std::vector<float> weights;
		//Output value
		float outputValue;
	public:
		/*
			Creates neuron and saves provided float source as source of values used when creating weights
		*/
		Neuron(IFloatSource * weightSource);

		/*
			Calculates a value from range <0;1>
		*/
		void calculate();

		/*
			Connects source neuron as input to this neuron (by address of outpuValue member). 
			If address is nullptr, connects biasInput
		*/
		void connectInput(const Neuron * source);
	
		/*
			Connects float variable address to this neuron as input
		*/
		void connectInput(const float * source);
	
		/*
			Uses getValue provided in argument to modify weights and treshold: new weight = old wight + argument getValue * associated input getValue 
			
		*/
		void modifyWeights(float val);


		/*
			Returns output value of this neuron
		*/
		float getValue() {
			return outputValue;
		}

		/*
			Returns value of activation function derivative. (For sigmoid)
		*/
		float derivativeValue() {
			return outputValue * (1 - outputValue);
		}

		/*
			Returns weight vector reference. Allows operation on weights without copying vector
		*/
		const std::vector<float> & getWeights() {
			return weights;
		}

		/*
			Returns single weight value. Returns 0 if index out of bounds
		*/
		float weight(uint i) {
			if (i >= weights.size())
				return 0;
			
			return weights[i];
		}
	};

 }