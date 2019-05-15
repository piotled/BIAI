#pragma once

#include <fstream>
#include <defines.h>
#include "Digit.h"

//Size of digit buffer
const int BUFFSIZE = 30;

class DigitDataSet {
	//Reference to file containing digits. Binary mode required
	std::ifstream & digitSource;
	//Reference to file containing labels. Binary mode required
	std::ifstream & labelSource;
	//Digit count in file
	uint digitCount;
	//Index of current digit in file
	uint digitIndex;
	//Index of digit in buffer
	uint bufferIndex;
	//Buffer containing digit set fragment
	Digit digitBuffer[BUFFSIZE];

	//CHenges msb to lsb of 4 byte integer
	inline uint MSBtoLSB(uint x);
	//Fill buffer with next values from file TODO(Doesnt check if file is not too short)
	void load();

public:
	/*
		Checks if data describing file format (stored in file headers) is correct, if not throws exception.
		Initializes class members with values.
	*/
	DigitDataSet(std::ifstream & digitSourceArg, std::ifstream & labelSourceArg);
	
	/*
		 Returns next digit from file. In case of read a number indexed beyond digitCount, return value is undefined. 
		 May throw exception if error occurs while reading file
	*/
	Digit getNext();
	
	/*
		Returns number of digits in file 
	*/
	uint size() {
		return digitCount;
	}
};

