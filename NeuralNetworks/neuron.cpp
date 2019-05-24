#include "neuron.h"
#include "sigmoid.h"
#include "DoubleGenerator.h"
#include "NNStructureError.h"

namespace BIAI {

	Neuron::Neuron(IDoubleSource * weightSource, IDoubleSource * tresholdSource) : weightSource(weightSource), tresholdSource(tresholdSource)
	{
		try {
			treshold = tresholdSource->get(); //May throw exception in case of reading from file
		}
		catch (...) {
			throw NNStructureError("Error while reading treshold values");
		}
	}

	void Neuron::operator()()
	{
		calc();
	}

	void Neuron::calc() {
		outputValue = 0; //Clear value
		for (int i = 0; i < inputs.size(); i++) { //For each input calculate
			outputValue += *inputs[i] * weights[i]; //Value of input * its weight
		}
		outputValue += treshold; //Add treshold
		outputValue = actFun(outputValue); //Use activation function to chage output value to value in range from 0 to 1
	}

	void Neuron::connectInput(const double * source)
	{
		inputs.push_back(source);
		try {
			weights.push_back(weightSource->get()); //May throw exception in case of reading from file
		}
		catch (...) {
			throw NNStructureError("Error while reading weight values");
		}
	}

	void Neuron::modifyWeights(double val)
	{
		for (int i = 0; i < weights.size(); i++) { //For each weight
			weights[i] += ( val * (*inputs[i]) ); //Modify weight
		}
		//Modify treshold
		treshold += val;
	}

	void Neuron::connectInput(const Neuron * source)
	{
		inputs.push_back(&source->outputValue);
		try {
			weights.push_back(weightSource->get()); //May throw exception in case of reading from file
		}
		catch (...) {
			throw NNStructureError("Error while reading weight values");
		}
	}

}