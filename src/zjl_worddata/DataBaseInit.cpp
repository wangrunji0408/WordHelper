#include <iostream>
#include <fstream>
#include <string>
#include "database.h"
using namespace std;

int main (int argc, char** argv)
{
	if(argc != 3)
	{
		cout << "usage: " + string(argv[0]) + " <input_file> <output_file>" << endl;
		return 0;
	}
	string const input = argv[1];
	string const output = argv[2];
	ifstream fin(input);
	ofstream fout(output);
	if(!fin.is_open())
	{
		cout << "Failed to open: " << input << endl;
		return 0;
	}
	if(!fout.is_open())
	{
		cout << "Failed to open: " << output << endl;
		return 0;
	}
	DataBase* dataBase = new DataBaseImpl;
	dataBase->loadFromIStream(fin);

	for(auto word: dataBase->getWordList())
	{
		word->lastTestTime = 0;
		word->rememberLevel = 0;
		for(auto it = word->meaningList.begin(); it != word->meaningList.end(); )
			if(it->explain[it->explain.size()-1] == '&')
				it = word->meaningList.erase(it);
			else
				++it;
	}

	dataBase->writeToOStream(fout);
}