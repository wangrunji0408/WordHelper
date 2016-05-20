// 以下作者：赵嘉霖

#include "shell.h"
#include <iomanip>

void Shell::Test_SpellMode (int size) const
{
	if(size == 0)
		size = kernel->getDefaultTestSize();
	clearScreen();
	out << "Test start. (Spell Mode)" << endl;
	TestKernel_SpellMode* spell = kernel -> getNewSpellTestKernel (size);
	for(int order = 1; !spell -> isEnd(); ++order)
	{
		const WordInfo* word = spell -> getWordInfoPtr();
		out << "----------" << order << '/' << spell->getSize() << "----------" << endl;
		for(int i = 0; i < word -> meaningList.size(); i ++) // 输出中文解释
		{
			if (i != 0)
			{
				out << ", ";
			}
			out << word -> meaningList[i].explain;
		}
		out << endl;

		out << "Spell: ";
		string pingxie;
		in >> pingxie;
		bool judge = spell -> returnUserAction (pingxie);
		if (judge)
		{
			out << "right √" << endl;
		}
		else
		{
			out << "wrong ×" << endl;
		}
		printWordFull(word);
		spell -> goNext();
	}
	out << "Test end." << endl;
}

void Shell::Test_RecallMode (int size) const
{
	if(size == 0)
		size = kernel->getDefaultTestSize();
	clearScreen();
	out << "Test start. (Recall Mode)" << endl;
	TestKernel_RecallMode* recall = kernel -> getNewRecallTestKernel (size);
	for(int order = 1; !recall -> isEnd(); ++order)
	{
		const WordInfo* word = recall -> getWordInfoPtr();
		out << "----------" << order << '/' << recall->getSize() << "----------" << endl;
		out << recall -> getWordString() << endl;
		string choice;
		while(true)
		{
			out << "Do you remember? (y/n) ";
			in >> choice;
			if(choice == "y")
			{
				recall -> returnUserAction(true);
				break;
			} 
			else if(choice == "n")
			{
				recall -> returnUserAction(false);
				break;
			}
			else
			{
				printError("Invaild input.");
			}
		}
		printWordFull(word);
		recall -> goNext();
	}
	out << "Test end." << endl;
}

// 以下作者：王润基
void Shell::Test_ChoiceMode (int size, bool choiceEnglish) const
{
	if(size == 0)
		size = kernel->getDefaultTestSize();
	TestKernel_ChoiceMode* testKernel = kernel -> getNewChoiceTestKernel (size, choiceEnglish);

	clearScreen();
	if(choiceEnglish)
		out << "Test start. (Choice English Mode)" << endl;
	else
		out << "Test start. (Choice Chinese Mode)" << endl;

	for(int order = 1; !testKernel -> isEnd(); ++order)
	{
		out << "----------" << order << '/' << testKernel->getSize() << "----------" << endl;
		out << testKernel->getQuestion() << endl;
		int i = 0;
		for(auto const& option: testKernel->getOptionList())
			out << (char)('A' + i++) << ' ' << option << endl;
		out << "Choice: ";
		char userChoice;
		in >> userChoice;
		bool judge = testKernel -> returnUserAction (userChoice - 'A');
		if (judge)
			out << "right √" << endl;
		else
			out << "wrong ×" << "  Answer: " << (char)('A' + testKernel->getAnswerId()) << endl;
		out << endl;
		printWordFull(testKernel -> getWordInfoPtr());
		testKernel -> goNext();
	}
	out << "Test end." << endl;
}