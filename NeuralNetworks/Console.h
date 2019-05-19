#pragma once
#include "IView.h"
#include <iostream>

/*
	Implementation of viev interface for standard in/out
*/

class Console : public IView  {
public:
	~Console() override {};
	std::string getString() override {
		std::string str;
		std::getline(std::cin, str);
		return str;
	}
	std::string getString(std::string msg) override {
		putString(msg);
		return getString();
	}
	void putString(std::string str) override {
		std::cout << str << std::endl;
	}
	bool yesNo(std::string msg) override {
		putString(msg);
		putString("Y/N");
		std::string choice = getString();
		
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
	uint getUInt(std::string msg) override {
		putString(msg);
		uint i;
		std::cin >> i;
		std::cout << std::endl;
		//clear stream
		std::string trash;
		std::getline(std::cin, trash);
		return i;
	}
};