#include "DigitDataSet.h"
#include <iterator>
#pragma once

//TODO(Change to something more elegant)
inline uint DigitDataSet::MSBtoLSB(uint x)
{
		uint t = x;
		uint r = 0;
		t >>= 24;
		t &= 0x000000FF;
		r += t;
		t = x;
		t >>= 8;
		t &= 0x0000FF00;
		r += t;
		t = x;
		t <<= 8;
		t &= 0x00FF0000;
		r += t;
		x <<= 24;
		x &= 0xFF000000;
		r += x;
		return r;
}

DigitDataSet::DigitDataSet(std::string digitFileName, std::string labelFileName) : digitIndex(0), bufferIndex(0), currentDigit(0)
{
	//Open files 
	digitSource.open(digitFileName, std::ios::in | std::ios::binary);
	labelSource.open(labelFileName, std::ios::in | std::ios::binary);
	if (!digitSource.is_open()) throw std::exception("Unable to open digit file!");
	if (!labelSource.is_open()) throw std::exception("Unable to open label file!");
	uint digRead, labRead; //Int numbers to store configuration data of input files
	digitSource.read((char *)&digRead, sizeof(digRead)); //Read 4 bytes from digit file TODO(4 bytes not always mean int)
	labelSource.read((char *)&labRead, sizeof(labRead)); //Read 4 bytes from label file
	if (labRead == 0x01080000 && digRead == 0x03080000) { //Checks for configuration value for files containing labels and digits (refer to MNIST website) 
		digitSource.read((char *)&digRead, sizeof(digRead)); //Read next 4 bytes from both files
		labelSource.read((char *)&labRead, sizeof(labRead));
		if (digRead == labRead) { //If read number (number of elements in file) is equal in both files, continue
			digitCount = MSBtoLSB(digRead); //Integer numbers in file are in MSB notation, convert it
			//Now, next 2 4 byte integers in digit file contain number of pixels of a digit, one number for one dimension
			//Check if numbers are equal and then check if their value is 28
			digitSource.read((char *)&digRead, sizeof(digRead));
			digitSource.read((char *)&labRead, sizeof(digRead));
			if (digRead == labRead && MSBtoLSB(digRead) == 28) {
				load(); //Fill buffer with initial values
				return; //File format ok, return
			}
		}
	}
	throw std::exception("Wrong file format"); //Configuration data is not correct, throw exception
}

Digit DigitDataSet::getNext() {
	currentDigit++; //Increase index of current digit
	//Check if bufferIndex points to last element in buffer
	if (bufferIndex == BUFFSIZE - 1) {
		//Copy data from buffer
		Digit retVal = digitBuffer[bufferIndex];
		//Reset buffer index
		bufferIndex = 0;
		//Load next digits
		load();
		//Return previously copied data
		return retVal;
	}
	else {
		//Return digit from buffer and increment buffer index
		return digitBuffer[bufferIndex++];
	}
}

void DigitDataSet::load()
{
		//Load digit data into buffer in each iteration until bufer is full
		for (uint i = 0; i < BUFFSIZE; i++) {
			if (digitIndex == digitCount) break; //If no more numbers, leave loop.
			digitBuffer[i].loadPixels(digitSource); //Load pixel data from file
			digitBuffer[i].loadLabel(labelSource); //Load label from file
			digitIndex++; //Increase index of digit in file
		}
}


