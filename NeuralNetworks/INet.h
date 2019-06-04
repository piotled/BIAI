#pragma once
#include <vector>
#include "Result.h"
#include "Layer.h"
/*
	Interface grouping common operations for different types of neutral networks
*/

namespace NN {

	class INet
	{
	protected:
		/*
			Grants access to layers in network. 
		*/
		virtual Layer * operator[](uint i) = 0;
	public:
		friend class Trainer;

		virtual ~INet() {};
		/*
			Method taking input vector for network as an argumet and returning output vector
		*/
		virtual std::vector<float> calculate(const std::vector<float> & inputVector) = 0;
		/*
			Returns string with net descritption.
		*/
		virtual std::string description() = 0;
		/*
			Save network to file with provided name. Requirements for file format:
			8bit value that contains value identificating network type at the beggining of a file
		*/
		virtual bool save(std::string fileName) = 0;
		/*
			Returns number of layers
		*/
		virtual uint getLayerCount() = 0;
	};

}



