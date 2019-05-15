#include "perceptron.h"
#include "DigitDataSet.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

void displayDigit(const Digit & d) {
	for (int i = 0; i < 28 * 28; i++) {
		if (i % 28 == 0)
			std::cout << std::endl;
			std::cout << (d.pixels[i] > 0.5 ? '1' : '0') << " ";
			
	}
}

int main() {
	//Opening files, in binary mode
	std::ifstream data("tr-data", std::ios::in | std::ios::binary);
	std::ifstream labels("tr-labels", std::ios::in | std::ios::binary);
	//Prepare object to read data from 
	/*DigitDataSet digits(data, labels);
	for (uint i = 0; i < digits.size(); i++) {
		system("cls");
		displayDigit(digits.getNext());
		std::cout << i << std::endl;
		system("pause");
	}*/
	BIAI::Perceptron x = { 2, 3, 4 };
	std::vector<double> y = { 0.4};
	x(y);
}

