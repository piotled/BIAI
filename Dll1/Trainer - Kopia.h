#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "DigitDataSet.h"
#include "Perceptron.h"

namespace NN {

	/*
		Class that tests or trains network provided by user
	*/

	class Trainer {
		INet * net; //Network
		float eta;
		bool adjustLearnRate;
	public:
		/*
			Sets neural net poiter to null. Adjusts eta by default. 
		*/
		Trainer() : net(nullptr), adjustLearnRate(true) {}

		/*
			Sets net to train
		*/
		void setNetwork(INet * net) {
			this->net = net;
		}
		/*
			Use provided train rate value
		*/
		void useTrainRate(float newEta) {
			eta = newEta;
			adjustLearnRate = false;
		}
		/*
			Enable train rate adjusting
		*/
		void useAdjustedTrainRate() {
			adjustLearnRate = true;
		}
		void calculateNeuronDelta(Neuron * deltaNeuron , int i, float * deltaDestination, Layer * nextLayer, const std::vector<float> * nextLayerDeltas);

		/*
			Tests network by providing input values and expected output values
		*/
		Result test(const std::vector<float> & inputVector, const std::vector<float> & expectedOutputVector);

		/*
			Trains network by providing input values and expected output values and changing weights accordingly
		*/
		Result train(const std::vector<float> & inputVector, const std::vector<float> & expectedOutputVector);
		
		/*
			Calculates and returns delta values for neurons in last layer. As arguments gets network output values and expected output values
		*/
		std::vector<float> calculateLastLayerDeltas(const std::vector<float>& outputVector, const std::vector<float>& expectedOutputVector);
		
		/*
			Calculates and returns delta values for hidden layer specified by layerIndex. Uses delta values from next layer stored in nextLayerDeltas vector.
		*/
		std::vector<float> calculateDeltas(uint layerIndex, const std::vector<float>& nextLayerDeltas);

		void calculateDeltasInRange(Layer * currentLayer, Layer * nextLayer, uint rangeStart, uint rangeEnd, std::vector<float> * deltas, const std::vector<float> & nextLayerDeltas);

		
		/*
			Updates weights in layer specified by layerIndex. Uses learn rate eta and deltas in provided vector
		*/
		void updateWeights(uint layerIndex, const std::vector<float>& deltas);
		/*
			Changes weights according to provided multiplier of neurons indexed within specified range
		*/
		void modifyNeuronWeightsInRange(Layer * layer, uint rangeStart, uint rangeEnd, float eta, const std::vector<float> & deltas);
	};
}