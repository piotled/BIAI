#include "Neuron.h"
#include "Sigmoid.h"
#include "FloatGenerator.h"
#include "StructureException.h"

namespace NN {

	Neuron::Neuron(IFloatSource * weightSource) : weightSource(weightSource), biasInput(1.0)
	{
	}

	void Neuron::calculate() {
		outputValue = 0; //Clear value
		for (int i = 0; i < inputs.size(); i++) { //For each input calculate
			outputValue += *inputs[i] * weights[i]; //Value of input * its weight
		}
		outputValue = actFun(outputValue); //Use activation function to chage output value to value in range from 0 to 1
	}

	void Neuron::connectInput(const float * source)
	{
		inputs.push_back(source);
		weights.push_back(weightSource->get()); //May throw exception in case of reading from file
	}

	void Neuron::modifyWeights(float val)
	{
		for (int i = 0; i < weights.size(); i++) { //For each weight
			weights[i] += ( val * (*inputs[i]) ); //Modify weight
		}
	}

	void Neuron::connectInput(const Neuron * source)
	{
		if (source == nullptr) {
			inputs.push_back(&biasInput);
		}
		else {
			inputs.push_back(&source->outputValue);
		}
		weights.push_back(weightSource->get()); //May throw exception in case of reading from file
	}

}