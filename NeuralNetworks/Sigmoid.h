#pragma once
#include <cmath>
#include "activationfunction.h"

class Sigmoid : public ActivationFunction {
public:
	~Sigmoid() {}
	double operator()(double input) {
		const double e = 2.71828182846;
		return 1.0 / (1.0 + pow(e, -input));
	}
};