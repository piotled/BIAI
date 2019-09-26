#pragma once

#include <fstream>
#include <defines.h>
#include "Digit.h"

//Size of digit buffer
const int BUFFSIZE = 50;

class DigitDataSet {
	//File containing digits. Binary mode required
	std::ifstream digitSource;
	//File containing labels. Binary mode required
	std::ifstream labelSource;
	//Digit count in file
	uint digitCount;
	//Index in file of last digit in buffer
	uint digitIndex;
	//Index of digit in buffer
	uint bufferIndex;
	//Index of currently pointed digit in file
	uint currentDigit;
	//Buffer containing digit set fragment
	Digit digitBuffer[BUFFSIZE];

	//CHenges msb to lsb of 4 byte integer
	inline uint MSBtoLSB(uint x);
	//Fill buffer with next values from file 
	void load();

public:
	/*
		Checks if data describing file format (stored in file headers) is correct, if not throws exception.
		Initializes class members with values.
	*/
	DigitDataSet(std::string digitFileName, std::string labelFileName);
	

	/*
		Closes files
	*/
	~DigitDataSet() {
		digitSource.close();
		labelSource.close();
	}

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

	/*
		Returns current digit number.
	*/
	uint getCurrentIndex() {
		return currentDigit;
	}
};

