#pragma once

class ActivationFunction {
public:
	virtual ~ActivationFunction() {
	};
	virtual double operator()(double) = 0;
};

