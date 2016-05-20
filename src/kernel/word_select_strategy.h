#ifndef _WORD_SELECT_STRATEGY_H
#define _WORD_SELECT_STRATEGY_H

#include "../word/database.h"

// 单词选择策略，属于TestKernel。其实是个函数，根据Database，输出单词的有序列表
class WordSelectStrategy
{
protected:
	// 从DataBase只读
	const DataBase* dataBase;
public:
	// 接口
	WordSelectStrategy (const DataBase*);
	virtual ~WordSelectStrategy () {};
	virtual vector<WordInfo*> getWordList (int number) const = 0;
};

class WordSelectStrategy_Random: public WordSelectStrategy
{
protected:
	

public:
	using WordSelectStrategy::WordSelectStrategy;
	virtual vector<WordInfo*> getWordList (int number) const;
};

#endif //_WORD_SELECT_STRATEGY_H