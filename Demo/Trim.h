#pragma once


#include <algorithm>
#include <cctype>
#include <locale>
#include <regex>
#include <string>

namespace Trim
{

	void ltrim(std::string &s);
	void rtrim(std::string &s);
	void trim(std::string &s);
}