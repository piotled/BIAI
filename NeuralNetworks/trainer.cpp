#pragma once

#include "trainer.h"
#include "ThreadBlockWrapper.h"

namespace NN {

	Result Trainer::test(const std::vector<float>& inputVector, const std::vector<float>& expectedOutputVector)
	{
		std::vector<float> netResult = net->calculate(inputVector); //Calulate network value
		float meanSquareError = 0.0; 
		//Mean square error: sum of squares of differences of acual output value for neuron and expected value for neuron
		//Sum is divided by 2
		for (int i = 0; i < expectedOutputVector.size(); i++) { //Calculate mean network error
			float outputValueDifference = expectedOutputVector[i] - netResult[i];
			meanSquareError += (outputValueDifference)*(outputValueDifference);
		}
		meanSquareError /= 2.0;
		//Check if result is correct
		uint maxIndex = 0;
		for (int i = 1; i < netResult.size(); i++) { //Find max element index
			if (netResult[i] > netResult[maxIndex])
				maxIndex = i;
		}
		return {netResult, meanSquareError, maxIndex}; //return test result
	}

	Result Trainer::train(const std::vector<float>& inputVector, const std::vector<float>& expectedOutputVector)
	{
		Result rs = test(inputVector, expectedOutputVector); //Perform test to get net output values
		//Calculate eta
		const float maxMeanSquareError = 5.0;
		if (adjustLearnRate) { //If no user specified learn rate
			eta = rs.meanSquareError / maxMeanSquareError + 0.2; //For low error this value will be close to constant
		}
		/*
			Weight correction is performed as follows: first, deltas for last layer are calculated. 
			Calculation of last layer deltas is different, so it is done in different method.
			Then, deltas for each hidden layers are calculated. This operation requires weight values and delta values from next layer.
			After each hidden layer delta calulation, weights in next layer can be updated. This is done by invoking Neuron class method and passing delta values and eta value.
			In the end, first layer is updated and process is finished.
		*/

		std::vector<float> oldDeltas; //Stores deltas from next layer
		std::vector<float> currentDeltas; //Stores deltas from current layer

		//Calculate detas for last layer - differently than for hidden layers
		oldDeltas = calculateLastLayerDeltas(rs.outputVector, expectedOutputVector);

		for (int i = net->getLayerCount() - 2; i >= 0; i--) { //For each layer except output layer
			/*
				First, calculate deltas. To do so, deltas and weights from next layer are needed. 
				Current deltas are saved into cuurentDeltas vector.
			*/
			currentDeltas = calculateDeltas(i, oldDeltas);
			/*
				Weights in next layer are no longer needed, so they can be updated. Uses eta, deltas and index of layer
			*/
			updateWeights(i + 1, oldDeltas);
			/*
				Swap vectors storing deltas
			*/
			oldDeltas = currentDeltas;
		}
		//Update weights in first layer
		updateWeights(0, oldDeltas);
		return rs;
	}

	std::vector<float> Trainer::calculateLastLayerDeltas(const std::vector<float> & outputVector, const std::vector<float> & expectedOutputVector) {
		std::vector<float> deltas; //Vector to store deltas
		float derivativeValue; //Stores value of derivative of activation function for vector
		uint lastLayerIndex = net->getLayerCount() - 1; 
		Layer * lastLayer = (*net)[lastLayerIndex];
		for (int i = 0; i < outputVector.size(); i++) { //For each neuron in last layer
			derivativeValue = (*lastLayer)[i]->derivativeValue(); //Get value of activation function derivative for neuron
			deltas.push_back( (expectedOutputVector[i] - outputVector[i]) * derivativeValue );
		}
		return deltas;
	}

	std::vector<float> Trainer::calculateDeltas(uint layerIndex, const std::vector<float> & nextLayerDeltas) {
		//BIG TODO
		/*Layer * currentLayer = (*net)[layerIndex];
		Layer * nextLayer = (*net)[layerIndex + 1];
		uint curLayNeuCnt = currentLayer->getNeuronCount();
		std::vector<float> deltas; //Stores calculated deltas
		for (int i = 0; i < curLayNeuCnt; i++) { //For each neuron in current layer
			float delta = (*currentLayer)[i]->derivativeValue(); // derivativeValue
			float tmp = 0; 
			for (int j = 0; j < nextLayer->getNeuronCount(); j++) {
				tmp += nextLayerDeltas[j] * (*nextLayer)[j]->weight(i);
			}
			delta *= tmp;
			deltas.push_back(delta);
		}
		return deltas;*/
		Layer * currentLayer = (*net)[layerIndex];
		Layer * nextLayer = (*net)[layerIndex + 1];
		uint curLayNeuCnt = currentLayer->getNeuronCount();
		std::vector<float> deltas; //Stores calculated deltas
		uint posiibleThreads = std::thread::hardware_concurrency() * 2; //Name a bit incorrect. It is number of physical cores * 2
		if (curLayNeuCnt < posiibleThreads) {
			for (int i = 0; i < curLayNeuCnt; i++) { //For each neuron in current layer
				float delta = (*currentLayer)[i]->derivativeValue(); // derivativeValue
				float tmp = 0;
				for (int j = 0; j < nextLayer->getNeuronCount(); j++) {
					tmp += nextLayerDeltas[j] * (*nextLayer)[j]->weight(i);
				}
				delta *= tmp;
				deltas.push_back(delta);
			}
		}
		else {
			ThreadBlockWrapper threadBlock(posiibleThreads);
			deltas.resize(curLayNeuCnt);
			//Divide neurons into groups. Number of groups equal to numbers of possible threads.
			uint res = curLayNeuCnt % posiibleThreads; //Residual - in case when neuronCount is not divible by possible thread count 
			uint groupCapacity = (posiibleThreads - res + curLayNeuCnt) / posiibleThreads; //Maximum group capactity. If res != 0, remaining space in last group wont be used.
			uint rangeStart = 0;
			uint rangeEnd = rangeStart + groupCapacity - 1;
			while (rangeStart < curLayNeuCnt) { //Stop when all possible threads are created
				threadBlock.save(new std::thread(&Trainer::calculateDeltasInRange, this, currentLayer, nextLayer, rangeStart, rangeEnd < curLayNeuCnt ? rangeEnd : curLayNeuCnt - 1, &deltas, nextLayerDeltas));
				rangeStart += groupCapacity;
				rangeEnd += groupCapacity;
			}
		}
		return deltas;
	}

	void Trainer::calculateDeltasInRange(Layer * currentLayer, Layer * nextLayer, uint rangeStart, uint rangeEnd, std::vector<float> * deltas, const std::vector<float> & nextLayerDeltas) {
		for (int i = rangeStart; i <= rangeEnd; i++) { 
			float delta = (*currentLayer)[i]->derivativeValue(); 
			float tmp = 0;
			for (int j = 0; j < nextLayer->getNeuronCount(); j++) {
				tmp += nextLayerDeltas[j] * (*nextLayer)[j]->weight(i);
			}
			delta *= tmp;
			(*deltas)[i] = delta;
		}
	}

	void Trainer::calculateNeuronDelta(Neuron * deltaNeuron, int neuronIndexAsInput, float * deltaDestination, Layer * nextLayer, const std::vector<float> * nextLayerDeltas) {
		*deltaDestination = deltaNeuron->derivativeValue(); 
		float tmp = 0;
		for (int i = 0; i < nextLayer->getNeuronCount(); i++) {
			tmp += (*nextLayerDeltas)[i] * (*nextLayer)[i]->weight(neuronIndexAsInput);
		}
		*deltaDestination *= tmp;
	}

	void Trainer::updateWeights(uint layerIndex, const std::vector<float> & deltas) {
		Layer * layer = (*net)[layerIndex];
		uint layerNeuronCount = layer->getNeuronCount();
		/*for (int i = 0; i < layer->getNeuronCount(); i++) {
			(*layer)[i]->modifyWeights(eta*deltas[i]); //Modify weights for each neuron in layer
		}*/

		uint posiibleThreads = std::thread::hardware_concurrency() * 2; //Name a bit incorrect. It is number of physical cores * 2
		if (layerNeuronCount < posiibleThreads) {
			for (int i = 0; i < layerNeuronCount; i++) {
				(*layer)[i]->modifyWeights(eta*deltas[i]); //Modify weights for each neuron in layer
			}
		}
		else {
			ThreadBlockWrapper threadBlock(posiibleThreads);
			//Divide neurons into groups. Number of groups equal to numbers of possible threads.
			uint res = layerNeuronCount % posiibleThreads; //Residual - in case when neuronCount is not divible by possible thread count 
			uint groupCapacity = (posiibleThreads - res + layerNeuronCount) / posiibleThreads; //Maximum group capactity. If res != 0, remaining space in last group wont be used.
			uint rangeStart = 0;
			uint rangeEnd = rangeStart + groupCapacity - 1;
			while (rangeStart < layerNeuronCount) { //Stop when all possible threads are created
				threadBlock.save(new std::thread(&Trainer::modifyNeuronWeightsInRange, this, layer, rangeStart, rangeEnd < layerNeuronCount ? rangeEnd : layerNeuronCount - 1, eta, deltas));
				rangeStart += groupCapacity;
				rangeEnd += groupCapacity;
			}
		}
	}

	void Trainer::modifyNeuronWeightsInRange(Layer * layer, uint rangeStart, uint rangeEnd, float eta, const std::vector<float> & deltas)
	{
		for (int i = rangeStart; i <= rangeEnd; i++)
			(*layer)[i]->modifyWeights(eta * deltas[i]);
	}
}