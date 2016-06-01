#ifndef _LOGGER_H
#define _LOGGER_H

#include "kernel.h"
#include <string>

enum LOGIN_RESULT
{
	LOGIN_SUCCESS,
	LOGIN_NO_USER,
	LOGIN_WRONG_PASSWORD
};

class Logger
{
protected:
	bool logSuccess = false;
	bool haveGotKernel = false;
	string userName;
	string userPath;
protected:
	bool makeUserPath ();
public:
	LOGIN_RESULT login (string const& user, string const& passward);
	Kernel* getNewKernel ();
};

#endif // _LOGGER_H