// 作者：赵嘉霖

#include "word_select_strategy.h"

vector<WordInfo*> WordSelectStrategy_Random::getWordList (const DataBase* dataBase, int number) const
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
			if(word.rememberLevel < WORD_LEVEL_MAX)
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
