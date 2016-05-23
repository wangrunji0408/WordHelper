#include <iostream>
#include <fstream>
#include <sstream>

#include "kernel/kernel.h"
#include "shell/shell.h"

using namespace std;
/*
void dataBaseLoadTest ()
{
	ifstream fin("word.json");
	ofstream fout("word_test.json");
	DataBase* dataBase = new DataBaseImpl;
	dataBase->loadDictInfo(fin);
	dataBase->saveDictInfo(fout);
}
*/

int main ()
{
	Kernel kernel;
	Shell shell(&kernel, cin, cout);
	shell.run();
}