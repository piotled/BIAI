#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "DigitDataSet.h"
#include "Perceptron.h"

namespace BIAI {

	class Trainer {

		//Result of one training iteration
		struct TrainingResults {
			std::vector<double> result;
			std::vector<double> expected;
			double meanError;
		};

		//Contains results of last network operation
		TrainingResults currentResults;

		//Object to read data from
		DigitDataSet * digits;
		//Neural network TODO(Change to inteface)
		Perceptron * net;
		//Learing coeficcient
		double eta;

		/*
			Constructor creating object to read digits
		*/
		Trainer(std::string digitFileName, std::string labelFileName, double coeficcient) {
			digits = new DigitDataSet(digitFileName, labelFileName);
			eta = coeficcient;
		}

		/*
			Perapres vector of expected values according to label value
		*/
		std::vector<double> prepareExpectedValueVector(int label);

	public:
		Trainer() {};

		/*
			Constructor creating new neural network 
		*/
		Trainer(std::string digitFileName, std::string labelFileName, std::vector<uint> netConf, double coeficcient = 1.0) : Trainer(digitFileName, labelFileName, coeficcient) {
			net = new Perceptron(netConf); //Create network
		}

		/*
			Constructor creating neural network from file data
		*/
		Trainer(std::string digitFileName, std::string labelFileName, std::string netFileName, double coeficcient = 1.0) : Trainer(digitFileName, labelFileName, coeficcient) {
			net = new Perceptron(netFileName); //Create network
		}

		/*
			Dealoccates memory
		*/
		~Trainer() {
			delete digits;
			delete net;
		}

		/*
			Perform next iteration. Uses one example from training set to change weight values, returns
			false if no examples are available.
		*/
		bool iterate();

		/*
			Calculate last layer backpropagation and return deltas
		*/
		std::vector<double> calculateLastLayer();

		/*
			Calculate hidden layer backpropagation and return deltas
		*/
		std::vector<double> calculateHiddenLayer(std::vector<double> & prevDeltas);

		/*
		
		*/
		TrainingResults getCurrentResults() {
			return currentResults;
		}

		void test(Perceptron * net, DigitDataSet * dig) {}

	};
}