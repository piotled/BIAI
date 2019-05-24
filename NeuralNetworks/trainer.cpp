#pragma once

#include "trainer.h"

namespace BIAI {

	Trainer::Result Trainer::test(const std::vector<double>& input, const std::vector<double>& expectedOutput)
	{
		std::vector<double> netResult = net->calc(input); //Calulate network value
		double meanError = 0.0; 
		//Mean error: sum of squares of differences of acual output value for neuron and expected value for neuron
		//Sum is divided by 2
		for (int i = 0; i < expectedOutput.size(); i++) { //Calculate mean network error
			double outputValueDifference = expectedOutput[i] - netResult[i];
			meanError += (outputValueDifference)*(outputValueDifference);
		}
		meanError /= 2.0;
		return {netResult, meanError}; //return test result
	}

	Trainer::Result Trainer::train(const std::vector<double>& input, const std::vector<double>& expectedOutput)
	{
		Result rs = test(input, expectedOutput); //Perform test to get net value
		//Calculate eta, learn rate as current mean error to max mean error ratio
		//Max mean error = 10 * 1 / 2 = 5
		const double maxMeanError = 5.0;
		double eta = 0.5; // rs.meanError / maxMeanError;

		/*
			Weight correction is performed as follows: first, deltas for last layer are calculated. 
			Calculation of last layer deltas is different, so it is done in different method.
			Then, deltas for each hidden layers are calculated. This operation requires weight values and delta values from next layer.
			After each hidden layer delta calulation, weights in next layer can be updated. This is done by invoking Neuron class method and passing delta values and eta value.
			In the end, first layer is updated and process is finished.
		*/

		std::vector<double> oldDeltas; //Stores deltas from next layer
		std::vector<double> currentDeltas; //Stores deltas from current layer

		//Calculate detas for last layer - differently than for hidden layers
		oldDeltas = calculateLastLayerDeltas(rs.result, expectedOutput);

		for (int i = net->getLayerCount() - 2; i >= 0; i--) { //For each layer except output layer
			/*
				First, calculate deltas. To do so, deltas and weights from next layer are needed. 
				Current deltas are saved into cuurentDeltas vector.
			*/
			currentDeltas = calculateDeltas(i, oldDeltas);
			/*
				Weights in next layer are no longer needed, so they can be updated. Uses eta, deltas and index of layer
			*/
			updateWeights(i + 1, eta, oldDeltas);
			/*
				Swap vectors storing deltas
			*/
			oldDeltas = currentDeltas;
		}
		//Update weights in first layer
		updateWeights(0, eta, oldDeltas);
		return rs;
	}

	std::vector<double> Trainer::calculateLastLayerDeltas(const std::vector<double> & output, const std::vector<double> & expectedOutput) {
		std::vector<double> deltas; //Vector to store deltas
		double derivativeValue; //Stores value of derivative of activation function for vector
		uint lastLayerIndex = net->getLayerCount() - 1; 
		Layer * lastLayer = (*net)[lastLayerIndex];
		for (int i = 0; i < output.size(); i++) { //For each neuron in last layer
			derivativeValue = (*lastLayer)[i]->derivativeValue(); //Get value of activation function derivative for neuron
			deltas.push_back( (expectedOutput[i] - output[i]) * derivativeValue );
		}
		return deltas;
	}

	std::vector<double> Trainer::calculateDeltas(uint layerIndex, const std::vector<double> & nextLayerDeltas) {
		Layer * currentLayer = (*net)[layerIndex];
		Layer * nextLayer = (*net)[layerIndex + 1];

		std::vector<double> deltas; //Stores calculated deltas

		for (int i = 0; i < currentLayer->getNeuronCount(); i++) { //For each neuron in current layer
			double delta = (*currentLayer)[i]->derivativeValue(); // derivativeValue
			
			double tmp = 0; 

			for (int j = 0; j < nextLayer->getNeuronCount(); j++) {
				tmp += nextLayerDeltas[j] * (*nextLayer)[j]->weight(i);
			}

			delta *= tmp;

			//Save delta
			deltas.push_back(delta);
		}
		return deltas;
	}

	void Trainer::updateWeights(uint layerIndex, double eta, const std::vector<double> & deltas) {
		Layer * layer = (*net)[layerIndex];
		for (int i = 0; i < layer->getNeuronCount(); i++) {
			(*layer)[i]->modifyWeights(eta*deltas[i]); //Modify weights for each neuron in layer
		}
	}
}