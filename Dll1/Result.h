#pragma once
#include <vector>

namespace NN {

	//Struct containing extended result of NN operation 
	struct Result {
		std::vector<float> outputVector;
		float meanSquareError;
		uint outputNeuronIndex;
	};

}
