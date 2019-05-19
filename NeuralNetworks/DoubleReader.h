#pragma once

#include "IDoubleSource.h"
#include <fstream>

class DoubleReader : public IDoubleSource {
	std::ifstream & source;
public:
	DoubleReader(std::ifstream & source) : source(source) {}
	virtual double get() {
		if(source.eof())  throw std::exception("File empty");
		double n;
		source.read((char *)&n, sizeof(n));
		if (source.fail()) throw std::exception("File empty");
		return n;
	}
};