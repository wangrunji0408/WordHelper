// 以下作者：赵嘉霖

#include "test_kernel.h"

TestKernel::TestKernel (DataBase* _database, WordSelectStrategy* wordselectstrategy, int _wordNum):
	dataBase(_database), wordNum(_wordNum)
{
	list = wordselectstrategy -> getWordList(_wordNum);
}
int TestKernel::getSize () const
{
	return wordNum;
}
const WordInfo* TestKernel::getWordInfoPtr () const
{
	return list[present];
}
string TestKernel_RecallMode::getWordString () const
{
	return list[present] -> word;
}
void TestKernel_RecallMode::returnUserAction (bool remember)
{
	if(remember)
		list[present] -> rememberLevel ++;
}
void TestKernel::goNext ()
{
	list[present]->lastTestTime = time(0);
	present ++;
}
bool TestKernel::isEnd() const
{
	if (present == list.size())
	{
		return true;
	}
	else 
	{
		return false;
	}
}
bool TestKernel_SpellMode::returnUserAction (string const& userSpell) const
{
	if (userSpell == list[present] -> word)
	{
		list[present] -> rememberLevel ++;
		return true;
	}
	else
	{
		return false;
	}
}

// 以下作者：王润基

TestKernel_ChoiceMode::TestKernel_ChoiceMode (DataBase* _dataBase,
											  WordSelectStrategy* _wordSelectStrategy,
											  int _wordNum,
											  int _optionSize):
	TestKernel(_dataBase, _wordSelectStrategy, _wordNum), optionSize(_optionSize),
	allWordList(_dataBase->getWordListConst()) {}

bool TestKernel_ChoiceMode::returnUserAction (int choiceId) const
{
	bool const right = choiceId == rightAnswerId;
	if(right)
		list[present]->rememberLevel ++;
	return right;
}
int TestKernel_ChoiceMode::getAnswerId () const
{
	return rightAnswerId;
}

string TestKernel_ChoiceChinese::getQuestion () const
{
	return list[present]->word;
}
vector<string> TestKernel_ChoiceChinese::getOptionList ()
{
	const WordInfo* const word = list[present];
	vector<string> optionList(optionSize);
	for(int i=0; i<optionSize; ++i)
	{
		// 随机找一个有中文的单词
		const WordInfo* word1 = nullptr;
		while(word1 == nullptr || word1->meaningList.empty())
			word1 = allWordList[rand() % allWordList.size()];

		optionList[i] = word1->meaningList[0].explain;
	}
	rightAnswerId = rand() % optionSize;
	optionList[rightAnswerId] = word->meaningList[0].explain;
	return optionList;
}
string TestKernel_ChoiceEnglish::getQuestion () const
{
	string str;
	for(auto const& meaning: list[present]->meaningList)
		str += meaning.partOfSpeech + ". " + meaning.explain + "  ";
	return str;
}
vector<string> TestKernel_ChoiceEnglish::getOptionList ()
{
	const WordInfo* const word = list[present];
	vector<string> optionList(optionSize);
	for(int i=0; i<optionSize; ++i)
	{
		const WordInfo* word1 = allWordList[rand() % allWordList.size()];
		optionList[i] = word1->word;
	}
	rightAnswerId = rand() % optionSize;
	optionList[rightAnswerId] = word->word;
	return optionList;
}