// 作者：王润基

#include "kernel.h"
#include "../word/json/json.h"
#include <algorithm>	// min
#include <fstream>
#include <cstdlib>

Kernel::Kernel (string const& _userName, string const& _userPath):
	userName(_userName), userPath(_userPath)
{	
	dataBase = new DataBaseImpl;
	loadConfig();
	loadDictionary();
	loadUserWord();
	printLog("Success to login: " + userName);
}
Kernel::~Kernel ()
{
	for(auto strategy: wordSelectStrategyList)
		delete strategy;
	saveUserWord();
	saveConfig();
	writeWordList();
	delete dataBase;
	printLog("Success to logout: " + userName);
}

void Kernel::printLog (string const& str) const
{
	std::clog << "Kernel: " << str << endl;
}

WordSelectStrategy* Kernel::getWordSelectStrategyPtr() const
{
	string const& name = config.wordSelectStrategy;
	for(auto const& wss: wordSelectStrategyList)
		if(wss->getName() == name)
			return wss;
	throw std::runtime_error("Kernel: Attempt to get a not exist WordSelectStrategy. name = " + name);
	return nullptr;
}


