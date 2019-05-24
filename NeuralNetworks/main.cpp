#include "console.h"
#include "controller.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

void displayDigit(const Digit & d) {
	for (int i = 0; i < 28 * 28; i++) {
		if (i % 28 == 0)
			std::cout << std::endl;
			std::cout << (d.pixels[i] > 0.5 ? '1' : '0') << " ";
			
	}
	std::cout << std::endl << (int)d.label << std::endl;
}

int main(int argc, char ** argv) {
	Controller * cnt;
	IView * console = new Console();
	if (argc != 1) {
		cnt = new Controller(console, argc, argv);
	}
	else {
		cnt = new Controller(console);
	}
	cnt->run();
	delete cnt;
	delete console;
	/*
	DigitDataSet digits("trd", "trl");
	while (digits.getCurrentIndex() != 59998) {
		digits.getNext();
	}
	while (1) {
		Digit x = digits.getNext();
		displayDigit(x);
		system("pause");
	}*/
}

