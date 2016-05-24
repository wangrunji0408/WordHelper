// 作者：王润基

#include "shell.h"

#include <iomanip>
#include <cctype>	// isalpha()

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
	out << "word_select_strategy" << " = " << kernel->getWordSelectStrategy() << endl; 
	out << endl;
	
	out << "test_mode: ";
	for(string const& name: kernel->getTestModeList())
		out << name << " ";
	out << endl;

	out << "word_select_strategy: ";
	for(string const& name: kernel->getWordSelectStrategyList())
		out << name << " ";
	out << endl;
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
	if(word->tagList.empty() && word->userTagList.empty())
		out << "(empty)" << endl;
	else
	{
		for(string const& tag: word->tagList)
			out << '[' << tag << "] ";
		for(string const& tag: word->userTagList)
			out << '{' << tag << "} ";
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

	out << "UserSetence: ";
	if(word->userSentenceList.empty())
		out << "(empty)" << endl;
	else
	{
		out << endl;
		int i = 1;
		for(auto const& sentence: word->userSentenceList)
		{
			out << std::setw(2) << i++ << ". > " << sentence.str << endl;
			out << "      " << sentence.trans << endl;
		}
	}
	printDividingLine();
}
void Shell::printWordInJson (const WordInfo* word) const
{
	out << (Json::Value)* static_cast<const WordDictInfo*>(word) << endl
		<< (Json::Value)* static_cast<const WordUserInfo*>(word);
}