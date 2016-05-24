#include <iostream>
#include <fstream>
#include <sstream>

#include "kernel/kernel.h"
#include "shell/shell.h"

using namespace std;

int main (int argc, char** argv)
{
	Kernel kernel;
	while(true)
	{
		string userName;
		cout << "Please enter user name. \"admin\" as default. Enter \"exit\" to exit." << endl;
		cout << "User Name: ";
		std::getline(cin, userName);
		if(userName == "exit")
			return 0;
		if(userName == "")
		{
			userName = "admin";
			cout << "Login defalut user: " << userName << endl;
		}
		kernel.login(userName);
		Shell shell(&kernel, cin, cout);
		shell.run();
		kernel.logout();
		return 0;
	}
}