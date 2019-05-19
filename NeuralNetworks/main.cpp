#include "console.h"
#include "controller.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

/*void displayDigit(const Digit & d) {
	for (int i = 0; i < 28 * 28; i++) {
		if (i % 28 == 0)
			std::cout << std::endl;
			std::cout << (d.pixels[i] > 0.5 ? '1' : '0') << " ";
			
	}
}*/

int main(int argc, char ** argv) {
	Controller * cnt;
	if (argc != 1) {
		cnt = new Controller(new Console(), argc, argv);
	}
	else {
		cnt = new Controller(new Console());
	}
	cnt->run();
	delete cnt;

	/*//Opening files, in binary mode
	std::ifstream data("tr-data", std::ios::in | std::ios::binary);
	std::ifstream labels("tr-labels", std::ios::in | std::ios::binary);
	DigitDataSet digits(data, labels);
	//Read net
	BIAI::Perceptron net("net");
	//Get digit
	Digit d = digits.getNext();
	//Expected values vector
	std::vector<double> expected;
	for (int i = 0; i < 10; i++) {
		if (d.label == i)
			expected.push_back(1.0);
		else
			expected.push_back(0.0);
	}
	std::vector<double> result = net(d.pixels);
	for (int i = 0; i < 10; i++) {
		std::cout << result[i] << " " << expected[i] << std::endl;
	}
	system("pause");
	/*std::vector<uint> x = { 28 * 28, 20, 20, 10 };
	BIAI::Perceptron net(x);
	net.save("net");*/
}

