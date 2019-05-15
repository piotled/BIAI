#pragma once
#include <exception>

class NNStructureError : public std::exception {
	std::string message;
public:

	NNStructureError(const char * newMessage) {
		message = newMessage;
	}

	char const* what() const
	{
		return message.c_str();
	}
};