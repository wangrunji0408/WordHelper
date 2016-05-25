#include "kernel.h"

#include <fstream>

void Kernel::loadConfig ()
{
	string configFileName = userPath + SLASH + "config.txt";
	std::ifstream configFileIn(configFileName);
	if(!configFileIn.is_open())
	{
		printLog("Failed to open config file. Use default.");
		config = Config(userName);
		return;
	}
	config.load(configFileIn);
	printLog("Success to load config.");
}
void Kernel::saveConfig()
{
	string configFileName = userPath + SLASH + "config.txt";
	std::ofstream configFileOut(configFileName);
	config.save(configFileOut);
	printLog("Success to save config.");
}
void Kernel::loadDictionary ()
{
	std::ifstream wordFileIn(config.dictFileName);
	if(!wordFileIn.is_open())
	{
		string errorString = "Failed to open dictionary file: " + config.dictFileName;
		printLog(errorString);
		throw std::runtime_error(errorString);
	}
	dataBase->loadDictInfo(wordFileIn);
	printLog("Success to load dictionary.");
}
void Kernel::saveDictionary ()
{
	std::ofstream wordFileOut(config.dictFileName);
	dataBase->saveDictInfo(wordFileOut);
	printLog("Success to save dictionary.");
}

void Kernel::loadUserWord ()
{
	std::ifstream file (config.userWordFileName);
	if(!file.is_open())
	{
		printLog("Failed to open user word file. Ignore!");
		return;
	}
	dataBase->loadUserInfo(file);
	printLog("Success to load user word.");
}

void Kernel::saveUserWord ()
{
	std::ofstream file (config.userWordFileName);
	dataBase->saveUserInfo(file);
	printLog("Success to save user word.");
}