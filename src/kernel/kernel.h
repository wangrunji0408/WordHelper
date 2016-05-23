#ifndef _KERNEL_H
#define _KERNEL_H

#include <iostream>
#include <sstream>
#include <vector>

#include "config.h"
#include "../word/database.h"
#include "test_kernel.h"
#include "word_kernel.h"
#include "text_analyze_kernel.h"

using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::endl;

class Kernel
{
protected:
	vector<string> const WORD_SELECT_STRATEGY_NAME = {"随机", "字典序"};
	vector<string> const TEST_MODE_NAME = {"recall", "spell", "choiceE", "choiceC"};
protected:
	// 全局参数
	string userName = "admin";
	string version = "0.95";
    Config config;
	
	// 重要成员
	DataBase* 						dataBase;
	vector<WordSelectStrategy*> 	wordSelectStrategyList;	// 在构造时new出所有策略，此后为常量，在析构时依次delete
	vector<string> 					searchHistoryList;
protected:
	// 读写
	void loadConfig ();
	void saveConfig();
	void loadDictionary ();
	void saveDictionary ();
	void loadUserWord ();
	void saveUserWord ();
	void login (string const& userName);
	void logout ();
	void printLog (string const&) const;
	// 获取当前选词策略
	WordSelectStrategy* getWordSelectStrategy() const;
public:
	// 按默认路径加载DataBase和Config 初始化wordSelectStrategyList
	Kernel();
	// 通知dataBase保存数据到文件 析构 dataBase wordSelectStrategy
	~Kernel ();
	// 参数的获取与修改
	string 	getVersion () const;
	int 	getDefaultTestSize () const;
	void 	setDefaultTestSize (int v);
	string 	getDataFileName () const;
	void 	setDataFileName (string const&);
	vector<string> getTestModeList () const;
	string 	getDefaultTestMode () const;
	void 	setDefaultTestMode (string const& testModeName);
	// SubKernel
	WordKernel* 			getNewWordKernel (const WordInfo*) const;
	TextAnalyzeKernel* 		getNewTextAnalyzeKernel () const;
	TestKernel_SpellMode* 	getNewSpellTestKernel (int size) const;							// size == 0 则使用默认size
	TestKernel_RecallMode* 	getNewRecallTestKernel (int size) const;						// ...
	TestKernel_ChoiceMode* 	getNewChoiceTestKernel (int size, bool choiceEnglish) const;	// ...
	// 返回搜索历史
	vector<string> 			getSearchHistory (int size) const;
	// 模糊搜索(英文/中文)
	vector<const WordInfo*> fuzzySearchByEnglish (string const&);
	vector<const WordInfo*> fuzzySearchByChinese (string const&);
	// 严格搜索(英文)
	const WordInfo* 		strictSearchByEnglish (string const&);
};

#endif
