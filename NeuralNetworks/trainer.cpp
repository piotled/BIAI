#pragma once

#include "trainer.h"

namespace BIAI {

	bool Trainer::iterate()
	{
		/*if (digits->getCurrentIndex() >= digits->size())
			return false;
		
		//Read digit
		Digit d = digits->getNext();
		//Calculate result from net
		currentResults.result = (*net)(d.pixels);
		currentResults.expected = prepareExpectedValueVector(d.label);

		std::vector<double> deltas = calculateLastLayer(); //Calculates corrections for last layer and returns deltas from last layes

		for (int i = net->getLayerCount() - 2; i >= 0; i--) { //For each layer, from last to first except last layer
			deltas = calculateHiddenLayer(deltas); //Calculate corrections with deltas from previous layer and reu=turn new deltas
		}*/

		return true;

	}

	std::vector<double> Trainer::calculateLastLayer() {
		std::vector<double> deltas;
		/*for (int i = 0; i < (*net)[net->getLayerCount()].getNeuronCount(); i++) { //For each neuron in last layer
			deltas.push_back(- (currentResults.expected[i] - currentResults.result[i]) * currentResults.result[i] * (1 - currentResults.result[i]));
		}*/
		return deltas;
	}

	std::vector<double> Trainer::calculateHiddenLayer(std::vector<double>& prevDeltas)
	{
		return std::vector<double>();
	}

	std::vector<double> Trainer::prepareExpectedValueVector(int label) {
		std::vector<double> v;
		for (int i = 0; i < 10; i++) { //TODO(changing source from digits to vectors of data and expected data can make this trainer universal, for now explicitly for digits
			if (i == label) {
				v.push_back(1.0);
			}
			else {
				v.push_back(0.0);
			}
		}
		return v;
	}

}

//TODO(activation function when reading from file, some identifier to know what function has to be set)