#ifndef _WORD_KERNEL_H
#define _WORD_KERNEL_H

#include "../word/word.h"

class WordKernel
{
protected:
	WordInfo* word;
public:
	WordKernel (WordInfo* _word);
	// 获得WordInfo的常量指针，外部只读数据不可修改
	const WordInfo* getWordInfoPtr () const;
	// 修改通过以下方法
	void addNote (string const&);
	void addTag (string const&);
	void addMeaning (string const& partOfSpeech, string const& explain);
	void addSentence (int meaningId, string const& str, string const& trans);
	void delNote (int noteId);
	void delTag (string const&);
	void delMeaning (int meaningId);
	void delSentence (int meaningId, int sentenceId);
};

#endif //_WORD_KERNEL_H