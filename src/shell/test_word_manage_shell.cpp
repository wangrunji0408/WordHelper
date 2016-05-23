#include "shell.h"
#include "sstream"

void Shell::test_word_manage(WordInfo* const word, const TestKernel* spell, bool& isEnd) const {
	clearScreen();
	printTitle("What to do next");
	printLn("[c]: Continue");
	printLn("[a]: Show the correst answer.");
	printLn("[s]: Show the detail information about this word");
	printLn("[m]: Enter into word manage interface");
	printLn("[i]: Do not want to have this word tested anymore");
	printLn("[h]: Get help information");
	printLn("[e]: Exit");
	auto parserCommand = [&] (string const& _command) -> bool {
		string cmd;
		std::stringstream stm;
		stm << _command;
		stm >> cmd; //如果不这样会怎么样
		if(cmd == "c") {
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
			word -> rememberLevel = 7;
			return true;
		}
		if(cmd == "e") {
			isEnd = true; 
			return false;
		}
		if(cmd == "h") {
			printLn("[c]: Continue");
			printLn("[a]: Show the correst answer.");
			printLn("[s]: Show the detail information about this word");
			printLn("[m]: Enter into word manage interface");
			printLn("[i]: Do not want to have this word tested anymore");
			printLn("[h]: Get help information");
			printLn("[e]: Exit");
			return true;
		}
		else {
			printError("Invalid command");
			return true;
		}
	};
	string command;
	do {
		out << "$";
		//std::getline(in, command);
		in >> command;
	}
	while(parserCommand(command));
}