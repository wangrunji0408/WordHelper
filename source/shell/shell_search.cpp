// 作者：王润基

#include "shell.h"
#include <iomanip>

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