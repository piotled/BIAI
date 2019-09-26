#pragma once

#include <defines.h>
#include <vector>
#include <fstream>

//Size of image in pixels. Both X and Y
const uint IMSIZE = 28;

/*
	Contains data of a single digit, pixel values and label
*/

struct Digit {
	//Vector of pixel values. float ranging from 0 to 1
	std::vector<float> pixels;
	//Label value, 0 - 9
	uchar label; 

	/*
		Reads pixel values of digit image from provided input. Throws exception in case of error
	*/
	void loadPixels(std::ifstream & input);

	/*
		Reads label from provided input
	*/
	void loadLabel(std::ifstream & input);
};