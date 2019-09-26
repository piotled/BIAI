#pragma once
#include "Perceptron.h"

extern "C"
{
	class Controller
	{
		__declspec(dllexport) static NN::Perceptron * network;
	public:

		Controller() {
		}


		~Controller() {
		}



		bool LoadNetwork(char * filePath) {
			network = nullptr;
			return true;
		}

	};
}
