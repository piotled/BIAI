#include "controller.h"

Controller::Controller(IView * view, int argc, char ** argv) : view(view), net(nullptr), trainingSet(nullptr), testSet(nullptr) {
	//First, check argument count
	if (argc != 6) {
		view->putString("Wrong number of arguments");
		ready = false;
	}
	else {
		try {
			trainingSet = new DigitDataSet(argv[1], argv[2]);
			testSet = new DigitDataSet(argv[3], argv[4]);
			net = new BIAI::Perceptron(argv[5]);
			ready = true;//Ok, all objects created correctly
		}
		catch (std::exception & exc) {
			view->putString(exc.what());
			ready = false;
		}
	}
}


Controller::~Controller() {
	if (view)
		delete view;
	if (net)
		delete net;
	if (trainingSet)
		delete trainingSet;
	if (testSet)
		delete testSet;
}

void Controller::run() {
	if (ready) { //If no error occured while creating objects
		try {
			if (!net) { //If no net specified ask to create one
				if (view->yesNo("Read net from file?")) { //Ask wheter user wants to read net from file
					//Get string from user and use it as path to file with net data
					net = new BIAI::Perceptron(view->getString("Type path to file with net description"));
					//Exception here stops program
				}
				else {//Ask user to type values describing net 
					std::vector<uint> netDesc = getDescFromUser();
					net = new BIAI::Perceptron(netDesc);
					//Exception here stops program
				}
			}
			if (!trainingSet) { //If no training set specified, ask to read one
				try { //Reading training set in not mandatory
					if (view->yesNo("Read training set?"))
						readDataSet(trainingSet);
				}
				catch (std::exception & exc) {
					view->putString(exc.what());
				}
			}
			if (!testSet) { //If no test set specified, ask to read one
				try { //Reading test set is not mandatory
					if (view->yesNo("Read test set?"))
						readDataSet(testSet);
				}
				catch (std::exception & exc) {
					view->putString(exc.what());
				}
			}

			//Now network is constructed. If training set is present, perform training.
			//If Test set is present, perform tests
			//When finished, ask whether to save net
			if (trainingSet)
				train();
			if (testSet)
				trainer.test(net, testSet);
			saveNet();

		}
		catch (std::exception & exc) {
			view->putString(exc.what());
		}
	}
}

std::vector<uint> Controller::getDescFromUser() {
	uint argCnt = view->getUInt("Type number of layers, including input buffer:"); //Get argument count
	std::vector<uint> netConf; //Prepare vector
	for (int i = 0; i < argCnt; i++) { //In loop get number of integers according to argCnt
		netConf.push_back(view->getUInt("Type number of elements in " + std::to_string(i) + " layer"));
	}
	return netConf;
}

void Controller::readDataSet(DigitDataSet *& dataSet)
{
	std::string digitFileName = view->getString("Digit file name:");
	std::string labelFileName = view->getString("Label file name:");
	dataSet = new DigitDataSet(digitFileName, labelFileName);
}

void Controller::train()
{
	//TODO
}

void Controller::saveNet()
{
	//Ask wheter to save net
	while (view->yesNo("Save net?")) {
		if (net->save(view->getString("File to save:"))) { //If saved successfully
			view->putString("Saved succesfully");
			return; //Leave loop
		}
		else view->putString("Unable to save"); //In case of failurw while saving network
	}
}
