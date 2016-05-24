// 作者：王润基

#include "shell.h"
#include <iomanip>

Shell_Base::Shell_Base (Kernel* _kernel, istream& _in, ostream& _out):
	kernel(_kernel), in(_in), out(_out) {}

bool Shell::parseCommand (string const& command)
{
	std::stringstream stm;
	string cmd;

	stm << command;
	commandHistoryList.push_back(command);

	stm >> cmd;
	if(cmd == "exit" || cmd == "x")
		return false;
	if(cmd == "")
		return true;
	if(cmd == "help" || cmd == "?")
		printHelpInfo();
	else if(cmd == "history" || cmd == "h")
	{
		int count = DEFAULT_HISTORY_COUNT;
		stm >> count;
		if(stm.good() || stm.eof())	// 读入一个整数或没有别的参数
		{
			printHistory(count);
			return true;
		}
		printLn("Usage: history [max_size]");
	}
	else if(cmd == "search" || cmd == "s")
	{
		string word;
		stm >> word;
		if(stm.fail())
			printError("Failed to read word.");
		else
		{
			searchWord(word);
			return true;
		}
		printLn("Usage: search  <word>");
	}
	else if(cmd == "word" || cmd == "w")
	{
		string word;
		stm >> word;
		if(stm.fail())
			printError("Failed to read word.");
		else
		{
			auto wordinfo = kernel->strictSearchByEnglish(word, false);	// without logging
			if(wordinfo == nullptr)
				printLn("No such word.");
			else
				wordManage(wordinfo);
			return true;
		}
		printLn("Usage: word    <word>");

	}
	else if(cmd == "test" || cmd == "t")
	{
		string modeName;
		stm >> modeName;
		if(stm.fail())
		{
			if(!stm.eof())	
				printError("Failed to read mode name.");
			else	// 没有参数
			{
				if(Test( kernel->getDefaultTestMode(), 0 ))
					return true;
			}
		}
		else
		{
			int size = 0;
			stm >> size;
			if(stm.fail() && !stm.eof())	// int解析失败
				printError("Failed to read word_size.");
			else
			{
				if(Test(modeName, size))
					return true;
			}
		}
		printLn("Usage: test [test_mode] [word_size]");
		printLn("     test_mode: spell recall choiceE choiceC");
	}
	else if(cmd == "set")
	{
		string name;
		stm >> name;
		if(stm.fail())
			printError("Failed to read variable name.");
		else if(name == "default_test_size")
		{
			int size;
			stm >> size;
			if(stm.fail())
				printError("Failed to read number.");
			else
			{
				kernel->setDefaultTestSize(size);
				return true;
			}
		}
		else if(name == "default_test_mode")
		{
			string name;
			stm >> name;
			if(stm.fail())
				printError("Failed to read mode name.");
			else
			{
				kernel->setDefaultTestMode(name);
				return true;
			}
		}
		else if(name == "word_select_strategy")
		{
			string name;
			stm >> name;
			if(stm.fail())
				printError("Failed to read mode name.");
			else
			{
				kernel->setWordSelectStrategy(name);
				return true;
			}
		}
		else
		{
			printError("No such variable name.");
		}
		printLn("Usage: set <variable> <value>");
	}
	else if(cmd == "analyze" || cmd == "a")
	{
		string fileName;
		stm >> fileName;
		if(stm.fail())
			printError("Failed to read file name.");
		else
		{
			textAnalyze(fileName);
			return true;
		}
		printLn("Usage: analyze <file>");
	}
	else if(cmd == "get")
	{
		printVariables();
	}
	else if(cmd == "show")
	{
		string word;
		stm >> word;
		if(stm.fail())
			printError("Failed to read word.");
		else
		{
			auto wordinfo = kernel->strictSearchByEnglish(word, false);	// without logging
			if(wordinfo == nullptr)
				printLn("No such word.");
			else
				printWordInJson(wordinfo);
			return true;
		}
	}
	else
	{
		printError("Invalid command.");
	}
	return true;
}

void Shell::run ()
{
	string command;
	clearScreen();
	printHello();
	do
	{
		out << "$ ";
		std::getline(in, command);
	}
	while(parseCommand(command));
}