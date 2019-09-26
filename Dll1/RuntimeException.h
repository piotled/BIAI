#pragma once
#include <exception>
#include <string>

class RuntimeException : public std::exception {
	std::string message;
public:

	RuntimeException(const char * newMessage) {
		message = newMessage;
	}

	char const* what() const
	{
		return message.c_str();
	}
};