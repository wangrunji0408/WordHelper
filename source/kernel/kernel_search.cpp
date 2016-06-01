#include "kernel.h"

vector<const WordInfo*> Kernel::fuzzySearchByEnglish (string const& str, bool log) 
{
	if(log)
		searchHistoryList.push_back(str);
	auto filter = [&](WordInfo const& word) -> bool
	{
		return word.word.substr(0, str.length()) == str;
	};
	return dataBase->getWordListConst(filter);
}
vector<const WordInfo*> Kernel::fuzzySearchByChinese (string const& str, bool log) 
{
	if(log)
		searchHistoryList.push_back(str);
	auto filter = [&](WordInfo const& word) -> bool
	{
		for(auto const& meaning: word.meaningList)
			if(meaning.explain.find(str) != string::npos)
				return true;
		return false;
	};
	//printLog((string)"Not finished function:  " + "Kernel::fuzzySearchByChinese  " + str);
	return dataBase->getWordListConst(filter);
}
const WordInfo* Kernel::strictSearchByEnglish (string const& word, bool log) 
{
	if(log)
		searchHistoryList.push_back(word);
	return dataBase->getWord(word);
}
vector<const WordInfo*> Kernel::customSearch ( function<bool(WordInfo const&)> filter )
{
	return dataBase->getWordListConst(filter);
}