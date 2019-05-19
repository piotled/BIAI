#pragma once

#include "trainer.h"
#include "Perceptron.h"
#include "DigitDataSet.h"
#include "IView.h"

class Controller {

	/*
		View reference
	*/
	IView * view;
	/*
		Digit sources
	*/
	DigitDataSet * trainingSet;
	DigitDataSet * testSet;
	/*
		Neural network
	*/
	BIAI::Perceptron * net;
	/*
		Trainer
	*/
	BIAI::Trainer trainer;
	/*
		Indicates wheter all is set up and ready for work
	*/
	bool ready;

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

	Controller(IView * view, int argc, char ** argv);

	/*
		Constructor
	*/

	Controller(IView * view) : view(view), net(nullptr), trainingSet(nullptr), testSet(nullptr), ready(true) {}

	/*
		Deallocates memory for view object and all other
	*/
	~Controller();

	/*
		Main method
	*/

	void run();

	/*
		Gets vector if integers describing network
	*/
	std::vector<uint> getDescFromUser();

	/*
		Reads filename for specified data set
	*/
	void readDataSet(DigitDataSet* & dataSet);

	/*
		Manages training of network
	*/
	void train();

	/*
		Ask user wheter to save net, then asks for file name and then saves net
	*/
	void saveNet();
};