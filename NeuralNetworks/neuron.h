#pragma once

#include <defines.h>
#include <vector>
#include "IDoubleSource.h"
#include "Sigmoid.h"

namespace BIAI {

	/*
		Class responsible for calculating an output value of a neuron from provided input arguments and weights stored in this object.
	*/
	class Neuron {
		//Sources for weights and tresholds
		IDoubleSource * tresholdSource;
		IDoubleSource * weightSource;
		//Activation function
		Sigmoid actFun;
		//Vector of pointers to variables storing outputs of neurons from previous layer that are connected to this neuron
		std::vector<const double *> inputs;
		//Vector of weights for each connection
		std::vector<double> weights;
		//Threshold value
		double treshold;
		//Output value
		double outputValue;
	public:
		/*
			Assigns address of activation function object and assigns random value to threshold
		*/
		Neuron(IDoubleSource * weightSource, IDoubleSource * tresholdSource);


		/*
			Calculates a value from range <0;1>
		*/
		void operator()();
		void calc();

		/*
			Connects this neuron as input to specified target neuron
		*/
		void connectInput(const Neuron * source);
	
		/*
			Connects double variable address to this neuron as input
		*/
		void connectInput(const double * source);
	
		/*
			Uses value provided in argument to modify weights and treshold: new weight = old wight + argument value * associated input value 
			
		*/
		void modifyWeights(double val);


		/*
			Returns output value of this neuron
		*/
		double value() {
			return outputValue;
		}

		/*
			Returns value of activation function derivative. (For sigmoid)
		*/
		double derivativeValue() {
			return outputValue * (1 - outputValue);
		}

		/*
			Returns treshold value
		*/
		double getTreshold() {
			return treshold;
		}

		/*
			Returns weight vector reference. Allows operation on weights without copying vector
		*/
		const std::vector<double> & getWeights() {
			return weights;
		}

		/*
			Returns single weight value. Returns 0 if index out of bounds
		*/
		double weight(uint i) {
			if (i >= weights.size())
				return 0;
			
			return weights[i];
		}
	};

 }