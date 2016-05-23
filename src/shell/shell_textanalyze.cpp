//作者：彭炳辉

#include "shell.h"
#include <fstream>
#include <iomanip>

void Shell::textAnalyze (string const& fileName) const {
	std::ifstream input_text(fileName);
	string _text((std::istreambuf_iterator<char>(input_text)), std::istreambuf_iterator<char>());
	//std::getline(input_text, _text, '\0');

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

void Shell::wordManage (const WordInfo* word) const {
	WordKernel* word_kernel = kernel -> getNewWordKernel(word);
	string command;
	printTitle("Manage your own word in WordHelper0.1");
	printWordFull(word);
	printLn("Please enter \"help\" to get command list");
	do {
		out << word->word << " $ ";
		std::getline(in, command);
	}
	while(parseCommandInWordKernel(command, word_kernel, word));
	delete word_kernel;
}
bool Shell::parseCommandInWordKernel(string const& command, WordKernel* word_kernel, const WordInfo* word) const {
	string cmd;
	std::stringstream stm;
	stm << command;
	stm >> cmd;
	if(cmd == "help"){
		printLn("-------------------------------------");
		printLn("            Command list             ");
		printLn("  help");
		printLn("  exit");
		printLn("  addNote");
		printLn("  addTag");
		printLn("  addMeaning");
		printLn("  addSentence");
		printLn("  delNote");
		printLn("  delTag");
		printLn("  delMeaning");
		printLn("  delSentence");
		printLn("-------------------------------------");
		return true;
	}
	if(cmd == "exit") {
		return false;
	}
	if(cmd == "") {
		return true;
	}
	if(cmd == "addNote") {
		out << "Please add some note here: " << endl;
		string note;
		in >> note;
		if(in.fail()) 
			printError("Failed to add note.");
		else 
			word_kernel -> addNote(note);
		return true;
	}
	if(cmd == "addTag") {
		out << "Please add a tag : " << endl;
		string tag;
		in >> tag;
		if(in.fail())
			printError("Failed to add tag.");
		else 
			word_kernel -> addTag(tag);
		return true;
	}
	if(cmd == "addMeaning") {
		string part0fspeech;
		printLn("Please enter the part0fspeech here: ");
		in >> part0fspeech; //是否需要判断格式
		if(in.fail()) {
			printError("Failed to add a part0fspeech");
			return true;
		}
		string explain;
		printLn("Please add an explaniation here: ");
		in >> explain;
		if(in.fail()) {
			printError("Failed to add a explaination");
			return  true;
		}
		word_kernel -> addMeaning(part0fspeech, explain);
		return true;
	}
	if(cmd == "addSentence") {
		int meaningID = -1;
		printLn("Please enter the meaning id: ");
		in >> meaningID;
		if(in.fail()) {
			printError("Failed to enter a meaning id");
			return true;
		}
		if(meaningID < 0 || meaningID >= word -> meaningList.size()) {
			printError("Invalid id number.");
			return true;
		}
		string str;
		printLn("Please add a sentence: ");
		in >> str;
		if(in.fail()) {
			printError("Failed to add a sentence");
			return true;
		}
		string tran;
		printLn("Please enter a translation for the sentence: ");
		if(in.fail()) {
			printError("Failed to add a translation. ");
			return true;
		}
		word_kernel -> addSentence(meaningID, str, tran);
		return true;
	}
	if(cmd == "delNote") {
		int noteId = -1;
		out << "Note: " << endl;
		int i = 0;
		for(auto const& note: word->noteList)
			out << std::setw(2) << i++ << ". " << note << endl;
		printLn("Please enter the note id you want to delete: ");
		in >> noteId;
		if(in.fail()) {
			printError("Failed to read the id number.");
			return true;
		}
		if(noteId < 0 || noteId >= word -> noteList.size()) {
			printError("Invalid note id.");
			return true;
		}
		word_kernel -> delNote(noteId); 
		return true;
	}
	if(cmd == "delTag") {
		string tag;
		printLn("Please enter the tag you want to delete: ");
		in >> tag;
		if(in.fail()) {
			printError("Failed to read the tag.");
			return true;
		}
		word_kernel -> delTag(tag);
		return true;
	}
	if(cmd == "delMeaning") {
		int meaningId = -1;

		out << "Meaning: " << endl;
		int i = 0;
		for(auto const& meaning: word->meaningList)
			out << std::setw(2) << i++ << ". " << meaning.partOfSpeech << ". " << meaning.explain << endl;

		printLn("Please enter the meaning id you want to delete: ");
		in >> meaningId;
		if(in.fail()) {
			printError("Failed to read the id number.");
			return true;
		}
		if(meaningId < 0 || meaningId >= word -> meaningList.size()) {
			printError("Invalid meaning id.");
			return true;
		}
		word_kernel -> delMeaning(meaningId);
		return true;
	}
	if(cmd == "delSentence") {
		out << "Meaning: " << endl;
		int i = 0;
		for(auto const& meaning: word->meaningList)
			out << std::setw(2) << i++ << ". " << meaning.partOfSpeech << ". " << meaning.explain << endl;

		int meaningId = -1;
		printLn("Please enter the meaning id you want to delete: ");
		in >> meaningId;
		if(in.fail()) {
			printError("Failed to read the id number.");
			return true;
		}
		if(meaningId < 0 || meaningId >= word -> meaningList.size()) {
			printError("Invalid meaning id.");
			return true;
		}

		out << "Sentence: " << endl;
		i = 0;
		for(auto const& sentence: word->meaningList[meaningId].exampleList)
			out << std::setw(2) << i++ << ". " << sentence.str << endl << "    " << sentence.trans << endl;

		int sentenceId = - 1;
		printLn("Please enter the sentence id you want to delete: ");
		in >> sentenceId;
		if(in.fail()) {
			printLn("Please enter the sentence id you want to delete: ");
			return true;
		}
		if(sentenceId < 0 || sentenceId >= word -> meaningList[meaningId].exampleList.size()) {
			printError("Invalid sentence id.");
			return true;
		}
		word_kernel -> delSentence(meaningId, sentenceId);
		return true;
	}
	else {
		printError("Invalid commmand.");
		return true;
	}
}