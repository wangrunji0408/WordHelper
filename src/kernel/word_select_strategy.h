#ifndef _WORD_SELECT_STRATEGY_H
#define _WORD_SELECT_STRATEGY_H

#include "../word/database.h"

// 单词选择策略，属于TestKernel。其实是个函数，根据Database，输出单词的有序列表
class WordSelectStrategy
{
public:
	// 接口
	virtual ~WordSelectStrategy () = default;
	virtual vector<WordInfo*> getWordList (const DataBase* dataBase, int number) const = 0;
};

class WordSelectStrategy_Random: public WordSelectStrategy
{
public:
	using WordSelectStrategy::WordSelectStrategy;
	virtual vector<WordInfo*> getWordList (const DataBase* dataBase, int number) const;
};

#endif //_WORD_SELECT_STRATEGY_H