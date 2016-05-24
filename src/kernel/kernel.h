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

#ifdef _WIN32
#define SLASH "\\"
#else
#define SLASH "/"
#endif

using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::endl;

class Kernel
{
protected:
	// 常量
	vector<string> const TEST_MODE_NAME = {"recall", "spell", "choiceE", "choiceC"};
	// 全局参数
	string userName;
	string version = "0.98";
    Config config;
	// 重要成员
	DataBase* 							dataBase;
	vector<WordSelectStrategy*> const	wordSelectStrategyList = 
		{new WordSelectStrategy_Random("random")};
	vector<string> 						searchHistoryList;
protected:
	// 错误反馈
	void printLog (string const&) const;
	//==========信息的读取与保存=====kernel_load_save.cpp========
	void loadConfig ();
	void saveConfig();
	void loadDictionary ();
	void saveDictionary ();
	void loadUserWord ();
	void saveUserWord ();
	//=========================================================
	// 获取当前选词策略
	WordSelectStrategy* getWordSelectStrategyPtr() const;
public:
	Kernel();
	~Kernel ();
	void login (string const& userName);
	void logout ();

	//==========参数的获取与修改=====kernel_set_get.cpp==========
	string 	getUserName () const;
	string 	getVersion () const;
	int 	getDefaultTestSize () const;
	bool 	setDefaultTestSize (int v);
	string 	getDataFileName () const;
	bool 	setDataFileName (string const&);
	vector<string> getTestModeList () const;
	vector<string> getWordSelectStrategyList () const;
	string 	getDefaultTestMode () const;
	bool 	setDefaultTestMode (string const& testModeName);
	string 	getWordSelectStrategy () const;
	bool 	setWordSelectStrategy (string const&);
	// 返回搜索历史
	vector<string> 			getSearchHistory (int size) const;
	// SubKernel
	WordKernel* 			getNewWordKernel (const WordInfo*) const;
	TextAnalyzeKernel* 		getNewTextAnalyzeKernel () const;
	TestKernel_SpellMode* 	getNewSpellTestKernel (int size) const;							// size == 0 则使用默认size
	TestKernel_RecallMode* 	getNewRecallTestKernel (int size) const;						// ...
	TestKernel_ChoiceMode* 	getNewChoiceTestKernel (int size, bool choiceEnglish) const;	// ...
	//==========================================================

	//==========搜索（数据库对接）====kernel_search.cpp===========
	// 单词搜索，默认不加log参数表示记录搜索内容
	//   模糊搜索(英文/中文)
	vector<const WordInfo*> fuzzySearchByEnglish (string const&, bool log = true);
	vector<const WordInfo*> fuzzySearchByChinese (string const&, bool log = true);
	//   严格搜索(英文)
	const WordInfo* 		strictSearchByEnglish (string const&, bool log = true);
	//   自定义搜索(延伸DataBase的接口)
	vector<const WordInfo*> customSearch ( function<bool(WordInfo const&)> );
	//==========================================================
};

#endif
