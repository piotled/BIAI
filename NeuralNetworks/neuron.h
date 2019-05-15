#pragma once

#include <defines.h>
#include <vector>

class ActivationFunction;

namespace BIAI {

	/*
		Class responsible for calculating an output value of a neuron from provided input arguments and weights stored in this object.
	*/
	class Neuron {
		//Address of pointer to object that represents activation function. Assigned once in constructor
		ActivationFunction ** actFun;
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
		Neuron(ActivationFunction ** actFunAddr);
		
		~Neuron() {}

		/*
			Calculates a value from range <0;1>
		*/
		void operator()();


		/*
			Returns output value of this neuron
		*/
		double value() {
			return outputValue;
		}

		/*
			Connects this neuron as input to specified target neuron
		*/
		void connectInput(const Neuron * source);
	
		/*
			Connects double variable address to this neuron as input
		*/
		void connectInput(const double * source);
	
	};

 }