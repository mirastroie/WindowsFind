#pragma once
#include <iostream>
#include <string>
#include "MyException.h"
#include "Win32FunctionsWrapper.h"
#include <tchar.h>
#include <regex>
#include <exception>

class SearchAppManager
{

private:
	static SearchAppManager*Instance;
	SearchAppManager() {};
public:
	SearchAppManager(const SearchAppManager&) = delete;
	void operator = (SearchAppManager const&) = delete;
	static SearchAppManager* getInstance()
	{
		if (!Instance)
			Instance = new SearchAppManager;
		return Instance;
	}
	void recursive_search(const std::wstring &, const std::wstring &, std::wstring );
	bool isFullPath(std::string, std::wstring &, std::wstring &);
	bool isRelativePath(std::string , std::wstring &, std::wstring &, std::wstring);
	void search(std::string, std::wstring);
	std::wstring getSubdirectory(std::wstring);
};