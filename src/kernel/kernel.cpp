// 作者：王润基

#include "kernel.h"
#include "../word/json/json.h"
#include <algorithm>	// min
#include <fstream>

#ifdef _WIN32
#define SLASH "\\"
#else
#define SLASH "/"
#endif

Kernel::Kernel ()
{
	dataBase = new DataBaseImpl;
	loadConfig();
	loadDictionary();
	loadUserWord();
	wordSelectStrategyList.push_back(new WordSelectStrategy_Random(dataBase));
	/*
	auto wordList = dataBase->getWordList([](const WordInfo&){return true;});
	for(auto word: wordList)
		std::cerr << (Json::Value)*word;
	*/
}
Kernel::~Kernel ()
{
	saveUserWord();
	saveConfig();
	for(auto strategy: wordSelectStrategyList)
		delete strategy;
	delete dataBase;
}

void Kernel::printLog (string const& str) const
{
	std::clog << "Kernel: " << str << endl;
}
void Kernel::loadConfig ()
{
	string configFileName = (string)"user_data" + SLASH + userName + SLASH + "config.txt";
	std::ifstream configFileIn(configFileName);
	if(!configFileIn.is_open())
	{
		printLog("Failed to open config file.");
		throw std::runtime_error("Failed to open config file.");
	}
	config.load(configFileIn);
	printLog("Success to load config.");
}
void Kernel::saveConfig()
{
	string configFileName = (string)"user_data" + SLASH + userName + SLASH + "config.txt";
	std::ofstream configFileOut(configFileName);
	if(!configFileOut.is_open())
	{
		printLog("Failed to open config file. Saving config failed.");
		throw std::runtime_error("Failed to open config file. Saving config failed.");
	}
	config.save(configFileOut);
	printLog("Success to save config.");
}
void Kernel::loadDictionary ()
{
	std::ifstream wordFileIn(config.dictFileName);
	if(!wordFileIn.is_open())
	{
		string errorString = "Failed to open dictionary file: " + config.dictFileName;
		printLog(errorString);
		throw std::runtime_error(errorString);
	}
	dataBase->loadDictInfo(wordFileIn);
	printLog("Success to load dictionary.");
}
void Kernel::saveDictionary ()
{
	std::ofstream wordFileOut(config.dictFileName);
	if(!wordFileOut.is_open())
	{
		string errorString = "Failed to open dictionary file: " + config.dictFileName;
		printLog(errorString);
		throw std::runtime_error(errorString);
	}
	dataBase->saveDictInfo(wordFileOut);
	printLog("Success to save dictionary.");
}

void Kernel::loadUserWord ()
{
	std::ifstream file (config.userWordFileName);
	if(!file.is_open())
	{
		printLog("Failed to open user word file. Ignore!");
		return;
	}
	dataBase->loadUserInfo(file);
	printLog("Success to load user word.");
}

void Kernel::saveUserWord ()
{
	std::ofstream file (config.userWordFileName);
	if(!file.is_open())
	{
		string errorString = "Failed to open user word file: " + config.userWordFileName;
		printLog(errorString);
		throw std::runtime_error(errorString);
	}
	dataBase->saveUserInfo(file);
	printLog("Success to save user word.");
}

string Kernel::getVersion () const
{
	return version;
}
int Kernel::getDefaultTestSize () const
{
	return config.defaultTestSize;
}
void Kernel::setDefaultTestSize (int v)
{
	if(v <= 0)
	{
		printLog("Failed to set default test size. It must be >0.");
		return;
	}
	config.defaultTestSize = v;
}

vector<string> Kernel::getTestModeList () const
{
	return TEST_MODE_NAME;
}
string Kernel::getDefaultTestMode () const
{
	return config.defaultTestModeName;
}
void Kernel::setDefaultTestMode (string const& testModeName)
{
	if(std::find(TEST_MODE_NAME.begin(), TEST_MODE_NAME.end(), testModeName) == TEST_MODE_NAME.end())
		printLog("Failed to set default test mode.  No such name: " + testModeName);
	else
		config.defaultTestModeName = testModeName;
}
WordSelectStrategy* Kernel::getWordSelectStrategy() const
{
	return wordSelectStrategyList.at(config.wordSelectStrategyId);
}
WordKernel* Kernel::getNewWordKernel (const WordInfo* word) const
{
	return new WordKernel(const_cast<WordInfo*>(word));
}

#define TEST_KERNEL_PARAMETER (dataBase, getWordSelectStrategy(), size == 0? config.defaultTestSize: size)
TestKernel_SpellMode* Kernel::getNewSpellTestKernel (int size) const
{
	return new TestKernel_SpellMode TEST_KERNEL_PARAMETER;
}
TestKernel_RecallMode* Kernel::getNewRecallTestKernel (int size) const
{
	return new TestKernel_RecallMode TEST_KERNEL_PARAMETER;
}
TestKernel_ChoiceMode* Kernel::getNewChoiceTestKernel (int size, bool choiceEnglish) const
{
	if(choiceEnglish)
		return new TestKernel_ChoiceEnglish TEST_KERNEL_PARAMETER;
	else
		return new TestKernel_ChoiceChinese TEST_KERNEL_PARAMETER;
}
TextAnalyzeKernel* Kernel::getNewTextAnalyzeKernel () const
{
	return new TextAnalyzeKernelImpl(dataBase);
}

vector<string> Kernel::getSearchHistory (int size) const
{
	vector<string> list(searchHistoryList.end() - std::min((int)searchHistoryList.size(), size), searchHistoryList.end());
	std::reverse(list.begin(), list.end());
	return list;
}

vector<const WordInfo*> Kernel::fuzzySearchByEnglish (string const& str) 
{
	searchHistoryList.push_back(str);
	auto filter = [&](WordInfo const& word) -> bool
	{
		return word.word.substr(0, str.length()) == str;
	};
	return dataBase->getWordListConst(filter);
}
vector<const WordInfo*> Kernel::fuzzySearchByChinese (string const& str) 
{
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
const WordInfo* Kernel::strictSearchByEnglish (string const& word) 
{
	searchHistoryList.push_back(word);
	return dataBase->getWord(word);
}