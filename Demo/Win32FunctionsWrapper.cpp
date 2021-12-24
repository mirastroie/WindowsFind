#include "Win32FunctionsWrapper.h"
#include "MyException.h"
#include <iostream>

//the constructor acquires the resource and establishes all class invariants or throws an 
//exception if that cannot be done
Win32FunctionsWrapper::Win32FunctionsWrapper(const LPCWSTR pathFind)
{
	
	if (wcslen(pathFind) >= MAX_PATH)
	{
		throw MyException(GetLastError(), "Path too long!");
	}
	_hSearch = FindFirstFileW(pathFind, &_ffd);
	if (_hSearch == INVALID_HANDLE_VALUE)
	{
		throw MyException(GetLastError(), "No such file or directory!");
	}
	
}
//the destructor releases the resource and never throws exceptions;
Win32FunctionsWrapper :: ~Win32FunctionsWrapper()
{
	
	if (_hSearch != INVALID_HANDLE_VALUE)
		FindClose(_hSearch);
	
}
bool Win32FunctionsWrapper::nextFile() {

	// if it succeeds, the return value is nonzero
	if (!FindNextFile(_hSearch, &_ffd))
	{
		if (GetLastError() != ERROR_NO_MORE_FILES)
			throw MyException(GetLastError(), "FindNextFileW failed!");
		return false;
	}
	return true;
}