// 作者：王润基

#include "kernel.h"
#include "../word/json/json.h"
#include <algorithm>	// min
#include <fstream>
#include <cstdlib>

Kernel::Kernel ()
{	
	
}
Kernel::~Kernel ()
{
	for(auto strategy: wordSelectStrategyList)
		delete strategy;
	if(userName != "")
		logout();
}

void Kernel::login (string const& _userName)
{
	if(userName != "")
	{
		printLog("Attempt to login a new user before logout. Auto logout.");
		logout();
	}
	system("mkdir user_data 2> /dev/null");
	system(((string)"mkdir user_data" + SLASH + _userName + " 2> /dev/null").c_str());
	userName = _userName;
	dataBase = new DataBaseImpl;
	loadConfig();
	loadDictionary();
	loadUserWord();
	printLog("Success to login: " + userName);
}
void Kernel::logout ()
{
	saveUserWord();
	saveConfig();
	delete dataBase;
	printLog("Success to logout: " + userName);
	userName = "";
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


