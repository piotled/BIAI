#pragma once

#include "trainer.h"
#include "Perceptron.h"
#include "DigitDataSet.h"
#include "Console.h"

class Controller {

	/*
		Object used to write on console
	*/
	Console console;
	/*
		Digit sources
	*/
	DigitDataSet * trainingSet;
	DigitDataSet * testSet;
	/*
		Neural network
	*/
	NN::INet * net;
	/*
		Trainer
	*/
	NN::Trainer trainer;

public:
	
	/*
		Controller recieveing input from command line
		Input:
		1.Training set digit file name
		2.Training set label file name
		3.Test set digit file name
		4.Test set label file name
		5.Neural net file
	*/

	//Controller(int argc, char ** argv);

	/*
		Constructor
	*/

	Controller() : net(nullptr), trainingSet(nullptr), testSet(nullptr) {}

	/*
		Deallocates memory 
	*/
	~Controller();

	/*
		Main method
	*/

	void run();

	/*
		Creates neural network according to user input
	*/
	void createNeuralNetwork();

	/*
		Gets vector if integers describing network
	*/
	std::vector<uint> getPerceptronDescription();

	/*
		Reads filename for specified data set
	*/
	void readDataSet(std::string dataSetName, DigitDataSet* & dataSet);

	std::pair<uint, uint> getElementRange(uint dataSetSize);

	float getTrainRate();

	/*
		Checks whether training is posiible. If is, manages training process
	*/
	void train();

	/*
		Checks whether testing is possible. If it is, tests network.
	*/
	void test();

	/*
		Display results of test/training pass
	*/
	void displayResults(int it, std::vector<float> result, std::vector<float> expected, float meanError);
	/*
		Ask user wheter to save net, then asks for file name and then saves net
	*/
	void saveNet();
};