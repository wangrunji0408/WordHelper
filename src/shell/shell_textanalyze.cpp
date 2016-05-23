//作者：彭炳辉

#include "shell.h"
#include <fstream>
#include <iomanip>

void Shell::textAnalyze (string const& fileName) const {
	std::ifstream input_text(fileName);
	string _text;
	std::getline(input_text, _text, '\0');
	TextAnalyzeKernel* text_analyze_kernel = kernel -> getNewTextAnalyzeKernel ();
	text_analyze_kernel -> loadText(_text);

	printTitle("Text Content");
	int const TEXT_MAX_SIZE_SHOW = 1000;
	if(_text.size() > TEXT_MAX_SIZE_SHOW)
		out << _text.substr(0, TEXT_MAX_SIZE_SHOW) << endl << "(......)" << endl;
	else
		out << _text << endl;
	out << endl;

	printTitle("Word Frequency");
	int const WORD_FREQUENCY_SIZE_SHOW = 10; //预定个数
	vector<const WordInfo*> word_info = text_analyze_kernel -> getWordListByFrequency ();
	for(int i = 0; i < WORD_FREQUENCY_SIZE_SHOW && i < word_info.size(); i++) { 
		out << " *" << text_analyze_kernel -> countWord(word_info[i] -> word) << "\t";
		printWordSimple(word_info[i]);
		out << endl;
	}
	out << endl;

	printTitle("Remembering Word");
	auto filter = [] (const WordInfo* word) -> bool
	{
		return word->rememberLevel > 0 && word->rememberLevel < WORD_LEVEL_MAX;
	};
	auto rememberingWordList = text_analyze_kernel->getInDataBaseWordList(filter);
	{
		int const WORD_SIZE_MAX = 10;
		int i = 0;
		for(auto word: rememberingWordList)
		{
			if(i == WORD_SIZE_MAX)	break;
			out << "  Lv." << word->rememberLevel << "  ";
			printWordSimple(rememberingWordList[i]);
		}
		out << endl;
	}

	printTitle("Words Not In DataBase");
	int const MAX_LINE = 5;
	vector<string> NotInWordList = text_analyze_kernel -> getNotInDataBaseWordList ();
	{
		int const WORD_NUM_PRE_LINE = 8;
		int const WORD_WIDTH = CONSOLE_WIDTH / WORD_NUM_PRE_LINE;
		int i = 0, cnt = 0, line = 0;
		for(auto word : NotInWordList)
		{
			int const space = word.size() / WORD_WIDTH + 1;	// 所占单词格数
			cnt += space;
			if(cnt > WORD_NUM_PRE_LINE)
			{
				out << endl;
				cnt = space;
				++line;
				if(line == MAX_LINE)
				{
					out << "(......)\n";
					break;
				}
			}
			out <<  std::setw(space * WORD_WIDTH) << word;
		}
		out << endl;
	}

	input_text.close();
	delete text_analyze_kernel;
}