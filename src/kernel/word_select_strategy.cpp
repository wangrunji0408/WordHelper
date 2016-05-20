// 作者：赵嘉霖

#include "word_select_strategy.h"
WordSelectStrategy::WordSelectStrategy (const DataBase* _database)
{
	dataBase = _database;
}

vector<WordInfo*> WordSelectStrategy_Random::getWordList (int number) const
{
	class Func
	{
		int max ;
		int sign = 0;
	public:
		Func(int _max): max(_max) {}
		bool operator() (WordInfo const& word)
		{
			if(sign == max)
				return false;
			bool result = false;
			if(word.rememberLevel < 7)
			{
				result = true;
			}
			if(result)
				++sign;
			return result;
		}
	};
	Func temp(number);
	vector<WordInfo*> list = dataBase->getWordList(temp);
	return list;
}
