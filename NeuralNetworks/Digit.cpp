#include "Digit.h"

void Digit::loadPixels(std::ifstream & input)
{
	pixels.resize(0); //Clear pixel data
	for (int i = 0; i < IMSIZE * IMSIZE; i++) { //Load one pixel value in each iteration
		uchar temp; //Used to store byte value read from file
		input.read((char*)&(temp), sizeof(temp)); //Read pixel value from file
		if (!input.good()) { //Check for errors
			throw std::exception("Error occured  before reading specified number of digits");
		}
		//No errors, change integer vale to real
		const float maxPixelValue = 255;
		pixels.push_back((float) temp / maxPixelValue);
	}
}

void Digit::loadLabel(std::ifstream & input)
{
	input.read((char*)&(label), sizeof(label));
	if (!input.good())
		throw std::exception("Encountered end of file befor reading specified number of labels");
}
