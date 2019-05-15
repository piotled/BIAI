#pragma once
#include <exception>
#include <string>

class NNRuntimeError : public std::exception {
	std::string message;
public:

	NNRuntimeError(const char * newMessage) {
		message = newMessage;
	}

	char const* what() const
	{
		return message.c_str();
	}
};