// 作者：彭炳辉

#include "shell.h"
#include <iomanip>

void Shell::wordManage (const WordInfo* word) const {
	WordKernel* word_kernel = kernel -> getNewWordKernel(word);
	string command;
	printTitle("Manage your own word: " + word->word);
	printWordFull(word);
	printLn("Please enter \"help\" or \"?\" to get command list.");
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
	if(cmd == "help" || cmd == "?"){
		printTitle("Command List");
		printLn("  [ ?] help");
		printLn("  [ x] exit");
		printLn("  [an] addNote");
		printLn("  [at] addTag");
		//printLn("  addMeaning");
		printLn("  [as] addSentence");
		printLn("  [dn] delNote");
		printLn("  [dt] delTag");
		//printLn("  delMeaning");
		printLn("  [ds] delSentence");
		printDividingLine();
		return true;
	}
	if(cmd == "exit" || cmd == "x") {
		return false;
	}
	if(cmd == "") {
		return true;
	}
	if(cmd == "addNote" || cmd == "an") {
		out << "Please add some note here: " << endl;
		string note;
		std::getline(in, note);
		if(in.fail()) 
			printError("Failed to add note.");
		else 
			word_kernel -> addNote(note);
		return true;
	}
	if(cmd == "addTag" || cmd == "at") {
		out << "Please add a tag : " << endl;
		string tag;
		in >> tag;
		if(in.fail())
			printError("Failed to add tag.");
		else 
			word_kernel -> addTag(tag);
		return true;
	}
	/*
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
	*/
	if(cmd == "addSentence" || cmd == "as") {
		string str;
		printLn("Please add a sentence: ");
		getline(in, str);
		if(in.fail()) {
			printError("Failed to read a sentence.");
			return true;
		}
		string tran;
		printLn("Please enter a translation for the sentence: ");
		std::getline(in, tran);
		if(in.fail()) {
			printError("Failed to read a translation.");
			return true;
		}
		word_kernel -> addSentence(str, tran);
		return true;
	}
	if(cmd == "delNote" || cmd == "dn") {
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
	if(cmd == "delTag" || cmd == "dt") {
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
	/*
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
	*/
	if(cmd == "delSentence" || cmd == "ds") {
		out << "Sentence: " << endl;
		int i = 0;
		for(auto const& sentence: word->userSentenceList)
			out << std::setw(2) << i++ << ". " << sentence.str << endl << "    " << sentence.trans << endl;

		int sentenceId = - 1;
		printLn("Please enter the sentence id you want to delete: ");
		in >> sentenceId;
		if(in.fail()) {
			printLn("Please enter the sentence id you want to delete: ");
			return true;
		}
		if(sentenceId < 0 || sentenceId >= word -> userSentenceList.size()) {
			printError("Invalid sentence id.");
			return true;
		}
		word_kernel -> delSentence(sentenceId);
		return true;
	}
	else {
		printError("Invalid commmand.");
		return true;
	}
}