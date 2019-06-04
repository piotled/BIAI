#include "controller.h"
#include "Result.h"
#include <algorithm>
#include <utility>

Controller::~Controller() {
	if (net)
		delete net;
	if (trainingSet)
		delete trainingSet;
	if (testSet)
		delete testSet;
}


void Controller::run() {
	/*
		Nets and data sets might have been loaded if command line arguments were used. 
		If they were not, ask user to choose what to do.
	*/
	if (!net) { 
		createNeuralNetwork();
	}
	if (!trainingSet) { 
		readDataSet("training set", trainingSet);
	}
	if (!testSet) { 
		readDataSet("test set", testSet);
	}
	if (console.yesNo("Continue?")) { 
		if (trainingSet)
			train();
		if (testSet)
			test();
		saveNet();
	}
}

void Controller::createNeuralNetwork()
{
	while (true) {
		int choice = console.menu({ "Choose network type", "Perceptron", "Convolutional" });
		if (console.yesNo("Read net from file?")) { 
			//Reading net from file
			std::string fileName = console.getLine("Please type file path:");
			try {
				if (choice == 0) {
					net = new NN::Perceptron(fileName);
				}
				else {
					//net = new NN::CNN(fileName);
				}
				return;
			}
			catch (std::exception & exc) {
				console.putText("Unable to read net from specified file. Error: ");
				console.putText(exc.what());
				net = nullptr;
			}
		}
		else {
			//Reading net from user desciption
			try {
				if (choice == 0) {
					net = new NN::Perceptron(getPerceptronDescription());
				}
				else {
					//net = new NN::CNN(getCNNDescription));
				}
				return;
			}
			catch (std::exception & exc) {
				console.putText("Unable to create network using provided description. Error: ");
				console.putText(exc.what());
				net = nullptr;
			}
		}

	}
}



std::vector<uint> Controller::getPerceptronDescription() {
	uint argCnt = console.get_uint("Type number of layers, including input buffer:"); 
	std::vector<uint> netStrucDesc; //Prepare vector
	for (int i = 1; i <= argCnt; i++) { //In loop get number of integers according to argCnt
		netStrucDesc.push_back(console.get_uint("Type number of elements in " + std::to_string(i) + " layer"));
	}
	return netStrucDesc;
}

void Controller::readDataSet(std::string dataSetName, DigitDataSet *& dataSet)
{
	while (true) {
		try { //Reading data sets in not mandatory
			if (console.yesNo(std::string("Read ") + dataSetName + std::string("?"))) {
				std::string digitFileName = console.getLine("Digit file name:");
				std::string labelFileName = console.getLine("Label file name:");
				dataSet = new DigitDataSet(digitFileName, labelFileName);
			}
			return;
		}
		catch (std::exception & exc) {
			console.putText(exc.what());
			console.putText("No training will be performed");
			trainingSet = nullptr;
			if (!console.yesNo("Retry?"))
				return;
			else
				continue;
		}
		if (!console.yesNo("Inproper path was typed. Retry?"))
			return;
	}
}

std::pair<uint,uint> Controller::getElementRange(uint dataSetSize) {
	while (true) {
		uint start = console.get_uint("Please type starting element index in data set:");
		uint end = console.get_uint("Please type ending element index in data set:");
		if (start >= dataSetSize || end >= dataSetSize) { //Indices from 0 to dataSetSize - 1
			console.putText("Error: Exceeded maximum data set size");
			continue;
		}
		else if(start > end) { //If start exceedes ending index
			console.putText("Error: Starting index grater than ending index");
			continue;
		}
		else return { start, end };
	}
}

float Controller::getTrainRate() {
	while (true) {
		float tr = console.get_float("Please type train rate value:");
		if (tr < 0) {
			console.putText("Error: train rate cant be negative");
			continue;
		}
		else return tr;
	}
}

void Controller::train()
{
	//Check if training set is present
	if (trainingSet) {
		trainer.setNetwork(net);
		//Ok, inform user how big is data set
		console.putText("Size of training set: " + std::to_string(trainingSet->size()));
		//Ask user to choose range of elements from data set
		std::pair<uint, uint> range = getElementRange(trainingSet->size()); //0 - size -1
		//Ask user to choose train rate
		int choice = console.menu({ "Choose train rate", "User specified", "Adjusted during training" });
		float trainRate;
		if (choice == 0) {
			//Get positive float from user
			trainRate = getTrainRate();
			trainer.useTrainRate(trainRate);
		}
		else {
			trainer.useAdjustedTrainRate();
		}
		//Move pointer in training set to specified position
		for (int i = 0; i < range.first; i++) {
			trainingSet->getNext();
		}

		//Settings summary
		console.putText(net->description());
		console.putText("");
		console.putText("Summary");
		console.putText("Size of training set: " + std::to_string(trainingSet->size()));
		console.putText("Training range: " + std::to_string(range.first) + " to " + std::to_string(range.second));
		if (choice == 0)
			console.putText("Learn rate: " + std::to_string(trainRate));
		else
			console.putText("Learn rate: error adjusted");
		console.pause();
		//Peform training
		int it = 0; //Number of iteration
		while (it + range.first <= range.second) {
			it++;
			Digit curDig = trainingSet->getNext(); //Read digit 
			//Prepare expected output vector
			std::vector<float> expected;
			expected.resize(10); //Resize for 10 digits
			expected[curDig.label] = 1.0; 
			NN::Result result = trainer.train(curDig.pixels, expected); //Train net with provided input and expected output
			console.clear();
			//TODO
			std::cout << it << " " << result.meanSquareError << std::endl;
			//displayResults(it, result.outputVector, expected, result.meanSquareError);
		}
	}
}

void Controller::test()
{
	if (testSet) {
		trainer.setNetwork(net);
		//Ok, inform user how big is data set
		console.putText("Size of test set: " + std::to_string(testSet->size()));
		//Ask user to choose range of elements from data set
		std::pair<uint, uint> range = getElementRange(testSet->size()); //0 - size -1
		//Move pointer in training set to specified position
		for (int i = 0; i < range.first; i++) {
			testSet->getNext();
		}
		bool stopWhenWrong = false;
		if (console.yesNo("Stop when digit classified incorrectly?"))
			stopWhenWrong = true;

		//Settings summary
		console.putText(net->description());
		console.putText("");
		console.putText("Summary");
		console.putText("Size of test set: " + std::to_string(testSet->size()));
		console.putText("Test range: " + std::to_string(range.first) + " to " + std::to_string(range.second));
		console.pause();

		//Peform test
		int it = 0; //Number of iteration
		uint wrongResults = 0; //Number of mistakes
		while (it + range.first <= range.second) {
			it++;
			Digit curDig = testSet->getNext(); //Read digit 
			//Prepare expected output vector
			std::vector<float> expected;
			expected.resize(10); //Resize for 10 digits
			expected[curDig.label] = 1.0; //Set proper neuron value to 1
			NN::Result result = trainer.test(curDig.pixels, expected);
			console.clear();
			if (curDig.label != result.outputNeuronIndex) { //If resulting acitve output neuron is incorrect 
				wrongResults++;
				if (stopWhenWrong) {
					console.writeDigit(curDig);
					console.putText("Classified as: " + std::to_string((int)result.outputNeuronIndex));
					if (console.yesNo("Type 'y' to skip testing. Any other key to continue.")) {

						break;
					}
				}
			}
			console.putText("Current index: " + std::to_string(it - 1));
		}

		console.clear();
		console.putText("Summary");
		console.putText("Size of test set: " + std::to_string(testSet->size()));
		console.putText("Test range: " + std::to_string(range.first) + " to " + std::to_string(range.second));
		console.putText("Number of iterations: " + std::to_string(it - 1));
		console.putText("Number of wrong results: " + std::to_string(wrongResults));
		console.putText("Error: " + std::to_string((float)wrongResults / (float)(it -1)));
		console.pause();

	}
}

void Controller::displayResults(int it, std::vector<float> result, std::vector<float> expected, float meanError)
{
	console.clear();
	console.putText(std::to_string(it) + " Test result: "); 
	for (int i = 0; i < result.size(); i++) {
		console.putText(std::to_string(result[i]) + "  " + std::to_string(expected[i]));
	}
	console.putText("Mean square error: " + std::to_string(meanError));
}

void Controller::saveNet()
{
	if (!console.yesNo("Save net?"))
		return;
	while (true) {
		if (net->save(console.getLine("File to save:"))) { //If saved successfully
			console.putText("Saved succesfully");
			return; //Leave loop
		}
		else { //If error occured while saving net
			if (!console.yesNo("Unable to save. Retry?"))
				return;
		}
	}
}
