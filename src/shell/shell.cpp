// 作者：王润基

#include "shell.h"

#include <iomanip>
#include <cctype>	// isalpha()
using std::setw;

Shell_Base::Shell_Base (Kernel* _kernel, istream& _in, ostream& _out):
	kernel(_kernel), in(_in), out(_out) {}

void Shell::clearScreen () const
{
	#ifdef _WIN32
	system("cls");
	#else	// Unix
	system("clear");
	#endif
}
void Shell::printLn (string const& str) const
{
	out << str << endl;
}
void Shell::printTitle (string const& str) const
{
	int const TOTAL_LENGTH = 30;
	int const LENGTH1 = (TOTAL_LENGTH + str.length()) / 2;
	out << std::setfill('-');
	out << std::setw(LENGTH1) << str;
	out << std::setw(TOTAL_LENGTH - LENGTH1) << "" << endl;
	out << std::setfill(' ');
}
void Shell::printHello () const
{
	printTitle("WordHelper 0.1");
	printLn("Enter \"help\" to get command list.");
}
void Shell::printHelpInfo () const
{
	printLn("---------------------------------");
	printLn("          Command List");
	printLn("  exit");
	printLn("  help");
	printLn("  history [max_size]");
	printLn("  search  <word>");
	printLn("  word    <word>");
	printLn("  voctest [test_mode] [word_size]");
	printLn("    test_mode: spell recall choiceE choiceC");
	printLn("  set     <variable> <value>");
	printLn("    variable:  default_test_size");
	printLn("  analyze <file>");
	printLn("---------------------------------");
}
void Shell::printHistory (int size) const
{
	printTitle("Word Search History");
	auto const& historyList = kernel->getSearchHistory(size);
	if(historyList.empty())
	{
		out << "(No Entry)" << endl;
		return;
	}
	int i = 0;
	for(string const& word: historyList)
		out << std::setw(2) << i++ << "  " << word << endl;
}
void Shell::printError (string const& errorInfo) const
{
	out << "Error: " << errorInfo << endl;
}
void Shell::printWordSimple (const WordInfo* word) const
{
	out << std::setiosflags(std::ios::left);		// 设为左对齐
	out << std::setw(10) << word->word << "  |";
	out << std::resetiosflags(std::ios::left);
	for(auto meaning: word->meaningList)
		out << meaning.partOfSpeech << ". " << meaning.explain << "|";
}
void Shell::printWordFull (const WordInfo* word) const
{
	out << word -> word << "  |" << word -> pronunciation << "|" << endl;
	for(auto const& meaning: word -> meaningList)
	{
		out << std::setw(4) << meaning.partOfSpeech << ". " << meaning.explain << endl;
		for(auto const& sentence: meaning.exampleList)
		{
			out << "    > " << sentence.str << endl;
			out << "      " << sentence.trans << endl;
		}
	}

	out << "Tag:  ";
	if(word->tagList.empty())
		out << "(empty)" << endl;
	else
	{
		for(string const& tag: word->tagList)
			out << tag << ' ';
		out << endl;
	}
	
	out << "Note: ";
	if(word->noteList.empty())
		out << "(empty)" << endl;
	else
	{
		int i = 0;
		for(string const& note: word->noteList)
			out << std::setw(2) << i << ". " << note << endl;
	}
	out << endl;
}
void Shell::printWordInJson (const WordInfo* word) const
{
	out << (Json::Value)*word;
}


void Shell::searchWord (string const& str) const
{
	static const int RESULT_MAX_SIZE = 5;
	vector<const WordInfo*> wordList;
	if(isalpha(str[0]))	// 判断是英文
	{
		/*
		auto ptr = kernel->strictSearchByEnglish(str);
		if(ptr != nullptr)
			wordList.push_back(ptr);
			*/
		wordList = kernel->fuzzySearchByEnglish(str);
	}
	else	// 判断是中文
		wordList = kernel->fuzzySearchByChinese(str);
	if(wordList.empty())
	{
		printLn("(No Entry)");
		return;
	}
	int i = 1;
	for(auto word: wordList)
	{
		out << i++ << "  ";
		printWordSimple(word);
		out << endl;
	}
}

bool Shell::parseCommand (string const& command)
{
	std::stringstream stm;
	string cmd;

	stm << command;
	stm >> cmd;

	if(cmd == "exit")
		return false;
	if(cmd == "")
		return true;
	if(cmd == "help")
		printHelpInfo();
	else if(cmd == "history")
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
	else if(cmd == "search")
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
	else if(cmd == "word")
	{
		string word;
		stm >> word;
		if(stm.fail())
			printError("Failed to read word.");
		else
		{
			auto wordinfo = kernel->strictSearchByEnglish(word);
			if(wordinfo == nullptr)
				printLn("No such word.");
			else
				wordManage(wordinfo);
			return true;
		}
		printLn("Usage: word    <word>");

	}
	else if(cmd == "voctest")
	{
		string modeName;
		stm >> modeName;
		if(stm.fail())
		{
			if(!stm.eof())	
				printError("Failed to read mode name.");
			else	// 没有参数
			{
				int const testModeId = kernel->getDefaultTestModeId();
				// {"recall", "spell", "choiceE", "choiceC"}
				if(testModeId == 0)
					Test_RecallMode(0);
				else if(testModeId == 1)
					Test_SpellMode(0);
				else if(testModeId == 2)
					Test_ChoiceMode(0, true);
				else if(testModeId == 3)
					Test_ChoiceMode(0, false);
				return true;
			}
		}
		else
		{
			int size = 0;
			stm >> size;
			if(stm.fail() && !stm.eof())	// int解析失败
				printError("Failed to read word_size.");
			else if(modeName == "spell")
			{
				Test_SpellMode(size);
				return true;
			}
			else if(modeName == "recall")
			{
				Test_RecallMode(size);
				return true;
			}
			else if(modeName == "choiceE")
			{
				Test_ChoiceMode(size, true);
				return true;
			}
			else if(modeName == "choiceC")
			{
				Test_ChoiceMode(size, false);
				return true;
			}
			else
				printError("No such mode name.");
		}
		printLn("Usage: voctest [test_mode] [word_size]");
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
		else
			printError("No such variable name.");
		printLn("Usage: set <variable> <value>");
		printLn("\tvariable: default_test_size ");
	}
	else if(cmd == "analyze")
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
	else
	{
		printError("Invalid command.");
	}
	return true;
}

void Shell::run ()
{
	string command;
	printHello();
	do
	{
		out << "$ ";
		std::getline(in, command);
	}
	while(parseCommand(command));
}