#pragma once
#include <cmath>

class Sigmoid {
public:
	~Sigmoid() {}
	float operator()(float input) {
		const float e = 2.71828182846;
		return 1.0 / (1.0 + pow(e, -input));
	}
};