
#include "SearchAppManager.h"
#include "Trim.h"




void SearchAppManager::recursive_search(const std::wstring &folder, const std::wstring &filename, std::wstring currentDirectoryPath)
{
	try {
		std::wstring WILDCARD = L"*";
		std::wstring toSearch = folder + L"\\" + filename;
		Win32FunctionsWrapper find(toSearch.c_str());
		do
		{
			WIN32_FIND_DATA file = find.getffd();
			std::wstring fileName(file.cFileName);
			std::wstring path = folder + L"\\" + getSubdirectory(filename) + fileName;

			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{

				std::string normalFileName(fileName.begin(), fileName.end());
				if (normalFileName != "." && normalFileName != "..")
				{
					std::wcout << path << "\n";
					recursive_search(path, WILDCARD, currentDirectoryPath);
				}
			}
			else
			{
				std::wcout << path << "\n";
			}

		} while (find.nextFile());
	}
	catch (const MyException& exp)
	{
		throw;
	}
}
//std::regex exprFullPath("^(C:)(([A-Z]*[a-z]*[1-9]*[-|#|!|.]*)+)^\([^\]+)$");
std::wstring SearchAppManager::getSubdirectory(std::wstring filename)
{
	std::string norrowFilePath(filename.begin(), filename.end());
	std::size_t found = norrowFilePath.find_last_of("/\\");
	if (found != std::string::npos)
	{
		std::string token = norrowFilePath.substr(0, found);
		std::wstring subDirectory(token.begin(), token.end());
		return subDirectory + L"\\";
	}
	return L"";

}
bool SearchAppManager::isRelativePath(std::string command, std::wstring &searchFile, std::wstring &searchPath, std::wstring currentDirectoryPath)
{
	std::regex exprTakeName("[^ ]*([A-Z]*[a-z]*[1-9]*[-|#|!|.|*|^\]*)+$");
	std::smatch take;
	std::regex_search(command, take, exprTakeName);
	if (!take.empty())
	{
		searchPath = currentDirectoryPath;
		std::string norrowFilePath = take[0];
		Trim::trim(norrowFilePath);
		std::wstring localSearchFile(norrowFilePath.begin(), norrowFilePath.end());

		std::size_t found2 = norrowFilePath.find_last_of("/\\");
		if (found2 != std::string::npos)
		{
			std::string token = norrowFilePath.substr(0, found2);
			std::string localFile = norrowFilePath.substr(found2 + 1);
			std::wstring subDirectory(token.begin(), token.end());
			std::wstring widelocalFile(localFile.begin(), localFile.end());
			searchPath = searchPath;
			searchFile = subDirectory + L"\\" + widelocalFile;
		}
		else
		{
			searchFile = std::wstring(norrowFilePath.begin(), norrowFilePath.end());
		}
		return true;
	}
	return false;
}
bool SearchAppManager::isFullPath(std::string command, std::wstring &searchFile, std::wstring &searchPath)
{
	std::string s2(command.begin(), command.end());
	std::size_t found = s2.find("C:");
	if (found == std::string::npos)return false;
	std::string s = s2.substr(found);
	std::size_t found2 = s.find_last_of("/\\");
	std::string token = s.substr(0, found2);
	std::string localFile = s.substr(found2 + 1);
	std::wstring subDirectory(token.begin(), token.end());
	std::wstring widelocalFile(localFile.begin(), localFile.end());
	searchFile = widelocalFile;
	searchPath = subDirectory;
	return true;
}

void SearchAppManager::search(std::string command, std::wstring currentDirectoryPath)
{

	std::wstring searchPath = currentDirectoryPath;
	std::wstring searchFile;
	
		if (isFullPath(command, searchFile, searchPath) || isRelativePath(command, searchFile, searchPath, currentDirectoryPath))
		{
			try
			{
				
				recursive_search(searchPath, searchFile, currentDirectoryPath);
			}
			catch (const MyException& exp)
			{
				std::cout << exp.what() << "\n";
				std::cout << "Eror code: " << exp.getError()<<"\n";
			}
		}
	
}
