#pragma once
#include <stdexcept>
#include <windows.h>

class MyException : public std::runtime_error
{
	DWORD _error;
public:
	MyException(DWORD error, const std::string& errorMessage) :_error(error), runtime_error(errorMessage) {}
	inline DWORD getError()const { return _error; }
};