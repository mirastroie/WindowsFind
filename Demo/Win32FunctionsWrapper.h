#pragma once
#include <Windows.h>
class Win32FunctionsWrapper
{
private:
	//a structure that contains info about the files or directories found
	WIN32_FIND_DATA _ffd;
	//the search handle i'm going to use for the subsequent calls
	HANDLE _hSearch = INVALID_HANDLE_VALUE;
public:
	Win32FunctionsWrapper(const LPCWSTR);
	inline HANDLE getSearchHandle() { return _hSearch; }
	inline WIN32_FIND_DATA getffd() { return _ffd; }
	// rule of three + to avoid double closing
	Win32FunctionsWrapper(const Win32FunctionsWrapper&);
	Win32FunctionsWrapper operator=(const Win32FunctionsWrapper&);
	bool nextFile();
	~Win32FunctionsWrapper();
};