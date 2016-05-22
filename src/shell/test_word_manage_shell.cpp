#include "shell.h"
#include "sstream"

void Shell::test_word_manage(const WordInfo* word, const TestKernel_SpellMode* spell) {
	printLn("------------------What to do next------------------");
	printLn("cont: Continue");
	printLn("answer: Show the correst answer.")
	printLn("show: Show the detail information about this word");
	printLn("manage: Enter into word manage interface");
	printLn("ign: Do not want to have this word tested anymore")
	printLn("exit: Exit");
	string command;
	auto parserCommand = [] (string const& command) -> bool {
		string cmd;
		std::stringstream stm;
		command >> stm;
		stm >> cmd; //如果不这样会怎么样
		if(cmd == "cont") {
			spell -> goNext();
			return false
		}

		if(cmd == "answer") {
			out << WordInfo -> word << endl;  //暂时只使用一种mode
			return true；
		}
		if(cmd == "show") {
			printWordSimple(word);
			return true;
		}
		if(cmd == "manage") {
			wordManage(word);
			return true;
		}
		if(cmd == "ign") {
			word -> rememberLevel = 7;
			return true;
		}
		if(cmd == "exit") {
			//退出
		}
		else {
			printError("Invalid command");
		}
	}
	do {
		out << "$" << endl;
		std::getline(in, command);
	}
	while(parserCommand(command));
}