#pragma once
#include <iostream>
#include <string>
#include <defines.h>
#include "Digit.h"

class Console {
public:
	//Get line from console
	std::string getLine() {
		std::string str;
		std::getline(std::cin, str);
		return str;
	}
	//Get line from console with message
	std::string getLine(std::string msg) {
		putText(msg);
		return getLine();
	}
	//Prints text on console
	void putText(std::string str) {
		std::cout << str << std::endl;
	}
	//Ask for confirmation. Prints provided message and returns true if user response matches confirmation character
	bool yesNo(std::string msg) {
		putText(msg);
		putText("Y/y to confirm, any key to cancel");
		std::string choice = getLine();
		
		if (choice.length() != 1)
			return false;
		switch (choice[0]) {
		case 'Y':
		case 'y':
			return true;
		default:
			return false;
		}
	}

	uint get_uint(std::string msg) {
		putText(msg);
		uint i;
		std::cin >> i;
		std::cout << std::endl;
		//clear stream
		std::string trash;
		std::getline(std::cin, trash);
		return i;
	}

	float get_float(std::string msg) {
		putText(msg);
		float i;
		std::cin >> i;
		std::cout << std::endl;
		//clear stream
		std::string trash;
		std::getline(std::cin, trash);
		return i;
	}

	//Pause waiting for input
	void pause() {
		system("pause");
	}

	int menu(std::initializer_list<std::string> menuParts) {
		if (menuParts.size() > 0) { //If arguments given
			uint menuElementCount = menuParts.size() - 1; //Save number of menu elements
			std::initializer_list<std::string>::iterator it = menuParts.begin();
			std::cout << *it << std::endl; //Print menu header (first argument)
			int cnt = 1;
			while (++it != menuParts.end()) { //Print and label every menu part
				std::cout << std::to_string(cnt++) << ". " << *it << std::endl;
			}

			while (true) {
				uint choice = this->get_uint("Choose option:");
				if (choice == 0 || choice > menuElementCount) {
					putText("Type option number");
					continue;
				}
				else return choice - 1;
			}

		}
	}

	void writeDigit(Digit & digit) {
		for (int i = 0; i < IMSIZE * IMSIZE; i++) {
			if (i % IMSIZE == 0)
				std::cout << std::endl;
			std::cout << (digit.pixels[i] > 0.5 ? '1' : '0') << " ";

		}
		std::cout << std::endl << (int)digit.label << std::endl;
	}

	void clear() {
		system("cls");
	}
};