#pragma once
#include <defines.h>
#include <vector>
#include "Neuron.h"

namespace NN {

	/*
		Class representing layer.
		Has access to neurons assigned to this layer.
		Is responsible for organizing calculations 
	*/
	class Layer {
		uint neuronCount; //Stores number of neurons in layer
		std::vector<Neuron *> neurons; //Vector of neurons, created dynamically  
	public:
		/*
			Constructs a layer with given neuron amount. 
		*/
		Layer(uint neuronCount, IFloatSource * weightSource);

		/*
			Move constructor
		*/
		Layer(Layer && source);
		/*
			Deallocates memory
		*/
		~Layer();
		/*
			Calculates neuron values in this layer
		*/
		void calculate();

		/*
			Calculates neuron outputs for neurons with indexes from range <rangeStart; rangeEnd>
		*/
		void calculateInRange(uint rangeStart, uint rangeEnd);
		/*
			Returns output values
		*/
		std::vector<float> getOutputVector();
		/*
			Returns pointer to neuron on specified position. Returns nullpointer if out of bounds
		*/
		Neuron * operator[](uint position);
		/*
			Returns neuron count in layer
		*/
		uint getNeuronCount() {
			return neuronCount;
		}

	};
}