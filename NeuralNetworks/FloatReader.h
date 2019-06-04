#pragma once

#include "IFloatSource.h"
#include <fstream>

class floatReader : public IFloatSource {
	std::ifstream & source;
public:
	floatReader(std::ifstream & source) : source(source) {}
	virtual float get() {
		if(source.eof())  throw std::exception("File empty");
		float n;
		source.read((char *)&n, sizeof(n));
		if (source.fail()) throw std::exception("File empty");
		return n;
	}
};