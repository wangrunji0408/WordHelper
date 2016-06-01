#ifndef _TEST_KERNEL_H
#define _TEST_KERNEL_H

#include "../word/database.h"
#include "word_select_strategy.h"

class TestKernel
{
protected:
	DataBase* const		dataBase;
	vector<WordInfo*> 	list;
	int 				present = 0;
	int 				wordNum;
public:
	TestKernel (DataBase*, WordSelectStrategy*, int _wordNum);
	int getSize () const;
	const WordInfo* getWordInfoPtr () const;
	void goNext ();
	bool isEnd () const;
	void setCurrectWordLevelMax () const;
	int getNowOrder() const;
};

// 单词测试模式1：给出英文，让用户回忆中文，询问记住没记住
class TestKernel_RecallMode: public TestKernel
{
public:
	using TestKernel::TestKernel;
	// 以下接口按顺序调用
	string getWordString () const;
	void returnUserAction (bool remember);
	// getWordInfoPtr();	已在父类中定义
	// goNext();			已在父类中定义
};

// 单词测试模式2：给出中文，让用户拼写英文，检查是否正确
class TestKernel_SpellMode: public TestKernel
{
public:
	using TestKernel::TestKernel;
	// 以下接口按顺序调用
	// getWordInfoPtr();	已在父类中定义
	bool returnUserAction (string const& userSpell) const;
	// goNext();			已在父类中定义
};

// 单词测试模式3：给出中文/英文，并给出几个选项，让用户选择正确的
class TestKernel_ChoiceMode: public TestKernel
{
protected:
	int const				optionSize;
	int 					rightAnswerId;	// getOptionList时修改
	vector<const WordInfo*> allWordList;	// 用于随机抽取，构造时赋值
public:
	TestKernel_ChoiceMode (DataBase*, WordSelectStrategy*, int _wordNum, int _optionSize = 4);
	// 以下接口按顺序调用
	virtual string getQuestion () const = 0;
	virtual vector<string> getOptionList () = 0;
	bool returnUserAction (int choiceId) const;
	int getAnswerId () const;
	// getWordInfoPtr();	已在父类中定义
	// goNext();			已在父类中定义
};

// 单词测试模式3-1：给英文，选中文
class TestKernel_ChoiceChinese: public TestKernel_ChoiceMode
{
public:
	using TestKernel_ChoiceMode::TestKernel_ChoiceMode;
	virtual string getQuestion () const override;
	virtual vector<string> getOptionList () override;
};

// 单词测试模式3-1：给中文，选英文
class TestKernel_ChoiceEnglish: public TestKernel_ChoiceMode
{
public:
	using TestKernel_ChoiceMode::TestKernel_ChoiceMode;
	virtual string getQuestion () const override;
	virtual vector<string> getOptionList () override;
};


#endif //_TEST_KERNEL_H