#pragma once

#include <string>
#include <defines.h>
/*
	Simple view  interface 
*/

class IView {
public:
	virtual ~IView() {}; 
	//Get string from user
	virtual std::string getString() = 0;
	//Get string from user with message
	virtual std::string getString(std::string msg) = 0;
	//Put string on display
	virtual void putString(std::string str) = 0;
	//Ask user for confiramtion
	virtual bool yesNo(std::string msg) = 0;
	//Gets unsigned int
	virtual uint getUInt(std::string msg) = 0;
};