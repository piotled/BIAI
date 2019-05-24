#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "DigitDataSet.h"
#include "Perceptron.h"

namespace BIAI {

	/*
		Class that tests or trains network provided by user
	*/

	class Trainer {
		Perceptron * net; //Network

	public:

		//Result of one training iteration
		struct Result {
			std::vector<double> result;
			double meanError;
		};

		/*
			Sets neural net poiter to null
		*/
		Trainer() : net(nullptr) {}

		/*
			Sets net to train
		*/
		void setNetwork(Perceptron * net) {
			this->net = net;
		}

		/*
			Tests network by providing input values and expected output values
		*/
		Result test(const std::vector<double> & input, const std::vector<double> & expectedOutput);

		/*
			Trains network by providing input values and expected output values and changing weights accordingly
		*/
		Result train(const std::vector<double> & input, const std::vector<double> & expectedOutput);
		
		/*
			Calculates and resturns delta values for neurons in last layer. As arguments gets network output values and expected output values
		*/
		std::vector<double> calculateLastLayerDeltas(const std::vector<double>& output, const std::vector<double>& expectedOutput);
		
		/*
			Calculates and returns delta values for hidden layer specified by layerIndex. Uses delta values from next layer stored in nextLayerDeltas vector.
		*/
		std::vector<double> calculateDeltas(uint layerIndex, const std::vector<double>& nextLayerDeltas);
		
		/*
			Updates weights in layer specified by layerIndex. Uses learn rate eta and deltas in provided vector
		*/
		void updateWeights(uint layerIndex, double eta, const std::vector<double>& deltas);
	};
}