#pragma once
#include <exception>

class StructureException : public std::exception {
	std::string message;
public:

	StructureException(const char * newMessage) {
		message = newMessage;
	}

	char const* what() const
	{
		return message.c_str();
	}
};