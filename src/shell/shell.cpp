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
void Shell::printDividingLine () const
{
	out << std::setfill('-');
	out << std::setw(CONSOLE_WIDTH) << "" << endl;
	out << std::setfill(' ');
}
void Shell::printLn (string const& str) const
{
	out << str << endl;
}
void Shell::printTitle (string const& str) const
{
	int const TOTAL_LENGTH = CONSOLE_WIDTH;
	int const LENGTH1 = (TOTAL_LENGTH + str.length()) / 2;
	out << std::setfill('=');
	out << std::setw(LENGTH1) << str;
	out << std::setw(TOTAL_LENGTH - LENGTH1) << "" << endl;
	out << std::setfill(' ');
}
void Shell::printHello () const
{
	printTitle("WordHelper " + kernel->getVersion());
	printLn("Welcome " + kernel->getUserName() + "!");
	printLn("Enter \"help\" or \"?\" to get command list.");
}
void Shell::printHelpInfo () const
{
	printTitle("Command List");
	#ifdef _WIN32
	printLn("  [x] exit");
	printLn("  [?] help");
	printLn("  [h] history [max_size]");
	printLn("  [s] search  <word>");
	printLn("  [w] word    <word>");
	printLn("  [t] test    [test_mode] [word_size]");
	printLn("                  └---> spell recall choiceE choiceC");
	printLn("  [a] analyze <file>");
	printLn("  [ ] set     <variable> <value>");
	printLn("  [ ] get");
	#else	// *nix
	printLn("  退    出    [x] exit");
	printLn("  帮    助    [?] help");
	printLn("  搜索历史    [h] history [max_size]");
	printLn("  搜索单词    [s] search  <word>");
	printLn("  单词管理    [w] word    <word>");
	printLn("  单词测试    [t] test    [test_mode] [word_size]");
	printLn("                              └---> spell recall choiceE choiceC");
	printLn("  文本分析    [a] analyze <file>");
	printLn("  变量设置    [ ] set     <variable> <value>");
	printLn("  变量查看    [ ] get");
	#endif
	printDividingLine();
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
void Shell::printVariables () const
{
	out << "default_test_size" << " = " << kernel->getDefaultTestSize() << endl;
	out << "default_test_mode" << " = " << kernel->getDefaultTestMode() << endl;
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
	printDividingLine();
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
			out << '[' << tag << "] ";
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
	printDividingLine();
}
void Shell::printWordInJson (const WordInfo* word) const
{
	out << (Json::Value)* static_cast<const WordDictInfo*>(word)
		<< (Json::Value)* static_cast<const WordUserInfo*>(word);
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

	printTitle("Search Result");
	if(wordList.empty())
		printLn("(No Entry)");
	else
	{
		int i = 1;
		for(auto word: wordList)
		{
			out << std::setw(2) << i++ << "  ";
			printWordSimple(word);
			out << endl;
		}
	}
	printDividingLine();
}

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
			string testModeName;
			stm >> testModeName;
			if(stm.fail())
				printError("Failed to read mode name.");
			else
			{
				kernel->setDefaultTestMode(testModeName);
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