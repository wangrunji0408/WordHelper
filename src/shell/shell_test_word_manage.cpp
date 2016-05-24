// 作者：彭炳辉

#include "shell.h"
#include "sstream"

bool Shell::test_word_manage(const WordInfo* word, const TestKernel* testKernel) const {
	string const helpInfo = 
		//"[ ]: Continue\n"
		"[c]: Continue\n"
		"[a]: Show the correst answer.\n"
		"[s]: Show the detail information about this word.\n"
		"[m]: Enter into word manage interface.\n"
		"[i]: Do not want to have this word tested anymore.\n"
		"[?]: Get help information.\n"
		"[x]: Exit test.\n";

	//clearScreen();
	printTitle("What to do next");
	out << helpInfo;
	printDividingLine();
	
	bool isEnd = false;
	auto parserCommand = [&] (string const& _command) -> bool {
		string cmd;
		std::stringstream stm;
		stm << _command;
		stm >> cmd; //如果不这样会怎么样
		if(cmd == "c" || cmd == "") {
			return false;
		}
		if(cmd == "a") {
			printWordSimple(word);  
			out << endl;
			return true;
		}
		if(cmd == "s") {
			printWordFull(word);
			out << endl;
			return true;
		}
		if(cmd == "m") {
			wordManage(word);
			return true;
		}
		if(cmd == "i") {
			testKernel->setCurrectWordLevelMax();
			return true;
		}
		if(cmd == "x") {
			isEnd = true; 
			return false;
		}
		if(cmd == "?") {
			out << helpInfo;
			return true;
		}
		else {
			printError("Invalid command");
			return true;
		}
	};
	string command;
	do {
		out << "Test (" << testKernel->getNowOrder() << "/" << testKernel->getSize() << ") $ ";
		in >> command;
		//std::getline(in, command);
	}
	while(parserCommand(command));
	return isEnd;
}