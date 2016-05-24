#include "kernel.h"

string Kernel::getVersion () const
{
	return version;
}
string Kernel::getUserName () const
{
	return userName;
}
int Kernel::getDefaultTestSize () const
{
	return config.defaultTestSize;
}
bool Kernel::setDefaultTestSize (int v)
{
	if(v <= 0)
	{
		printLog("Failed to set default test size. It must be >0.");
		return false;
	}
	else
	{
		config.defaultTestSize = v;
		return true;
	}
	
}

vector<string> Kernel::getTestModeList () const
{
	return TEST_MODE_NAME;
}
vector<string> Kernel::getWordSelectStrategyList () const
{
	vector<string> list;
	for(auto const& wss: wordSelectStrategyList)
		list.push_back(wss->getName());
	return list;
}
string Kernel::getDefaultTestMode () const
{
	return config.defaultTestModeName;
}
bool Kernel::setDefaultTestMode (string const& testModeName)
{
	if(std::find(TEST_MODE_NAME.begin(), TEST_MODE_NAME.end(), testModeName) == TEST_MODE_NAME.end())
	{
		printLog("Failed to set default test mode.  No such name: " + testModeName);
		return false;
	}
	else
	{
		config.defaultTestModeName = testModeName;
		return true;
	}
}
string Kernel::getWordSelectStrategy () const
{
	return config.wordSelectStrategy;
}
bool Kernel::setWordSelectStrategy (string const& name)
{
	for(auto const& wss: wordSelectStrategyList)
		if(wss->getName() == name)
		{
			config.wordSelectStrategy = name;
			return true;
		}
	printLog("Failed to set WordSelectStrategy.  No strategy named: " + name);
	return false;
}

WordKernel* Kernel::getNewWordKernel (const WordInfo* word) const
{
	return new WordKernel(const_cast<WordInfo*>(word));
}
#define TEST_KERNEL_PARAMETER (dataBase, getWordSelectStrategyPtr(), size == 0? config.defaultTestSize: size)
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