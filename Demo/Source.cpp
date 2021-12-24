#include "MyException.h"
#include "Win32FunctionsWrapper.h"
#include "SearchAppManager.h"
#include <regex>
#include <memory>
#include "Trim.h"
using namespace Trim;
using namespace std;


enum Command{FIND,HELP,EXIT};


TCHAR currentDirectoryPath[MAX_PATH];

bool isValidCommand(string command)
{
	smatch match;
	regex expr("(find)[^ ]*([A-Z]*[a-z]*[1-9]*[-|#|!|.|*|^\]*)+");
	regex_search(command, match, expr);
	return !match.empty();
}
Command getCommandType(string command)
{
	if (regex_match(command, regex("(find)(.)*")))
		return FIND;
	if (regex_match(command, regex("(help)(.)*")))
		return HELP;
	if (regex_match(command, regex("(exit)(.)*")))
		return EXIT;
}
void displayWelcomeMessage()
{
	cout << "This is a simple Win32 C++ console application that implements \n find command from linux\
 with minimal functionalities.\n";
	cout << "Right now you are in the following directory: \n";
	wcout << currentDirectoryPath << "\n";
	cout << " The searching will we done relatively to this directory.Type help for more info.\n";
}
SearchAppManager* SearchAppManager::Instance = nullptr;
void processInput()
{
	unique_ptr<SearchAppManager> manager(SearchAppManager::getInstance());
	string command;
	getline(cin, command);
	trim(command);
	Command commandType = getCommandType(command);
	while(true)
	{
		switch (commandType)
		{
		case HELP:
		{  cout << "exit -- exit console application\nfind  -- search for files in a\
\ directory hirarchy. Searches the directory tree rooted at each given\
\ starting point. If no starting point is specified, the directory in\
\ which the console application is run is assumed.\n";
		break;
		}

		case FIND:
		{   
			wstring searchPath = currentDirectoryPath;
			wstring searchFile;
			if (isValidCommand(command))
			{
				manager->search(command, currentDirectoryPath);
			}
			break;
		}
		case EXIT:
			return;
		}

		getline(cin, command);
		trim(command);
		commandType = getCommandType(command);

	};


}
int main()
{
	GetCurrentDirectory(MAX_PATH, currentDirectoryPath);
	displayWelcomeMessage();
	processInput();

}

// lists of possible commands:
// find *
// find directoryname
// find filename
// find generalRelativePath (example: find Desktop\hello)
// find absolutePath (example: C:\Users\Mira\Desktop\design\felicitare.gif)
// find *.type
// find subdir1\subdir2\*.type



// References:
/*
https://stackoverflow.com/questions/33226628/c-windows-api-recursive-search-is-not-returning-expected-directory
https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
*/