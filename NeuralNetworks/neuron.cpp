#include "neuron.h"
#include "sigmoid.h"
#include "DoubleGenerator.h"

namespace BIAI {

	Neuron::Neuron(ActivationFunction ** actFunAddr) : actFun(actFunAddr)
	{
		treshold = DoubleGenerator(-10, 10)();
	}

	void Neuron::operator()()
	{
		outputValue = 0; //Clear value
		for (int i = 0; i < inputs.size(); i++) { //For each input calculate
			outputValue += *inputs[i] * weights[i]; //Value of input * its weight
		}
		outputValue += treshold; //Add treshold
		outputValue = (*actFun)->operator()(outputValue); //Use activation function to chage output value to value in range from 0 to 1
	}

	/*void Neuron::connectTo(const Neuron * target)
	{
		target->inputs.push_back(&target->outputValue);
		weights.push_back(DoubleGenerator(-10, 10)());
	}*/

	void Neuron::connectInput(const double * source)
	{
		inputs.push_back(source);
		weights.push_back(DoubleGenerator(-10, 10)());
	}

	void Neuron::connectInput(const Neuron * source)
	{
		inputs.push_back(&source->outputValue);
		weights.push_back(DoubleGenerator(-10, 10)());
	}

}