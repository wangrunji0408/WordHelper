#include "logger.h"
#include <cstdlib>

bool Logger::makeUserPath ()
{
	userPath = (string)"user_data" + SLASH + userName;
	#ifdef _WIN32
	system("mkdir user_data");
	system(("mkdir " + userPath).c_str());
	#else
	system("mkdir user_data 2> /dev/null");
	system(("mkdir " + userPath + " 2> /dev/null").c_str());
	#endif
	return true;
}

LOGIN_RESULT Logger::login (string const& user, string const& passward)
{
	userName = user;
	makeUserPath();
	logSuccess = true;
	haveGotKernel = false;
	return LOGIN_SUCCESS;
}

Kernel* Logger::getNewKernel ()
{
	if(!logSuccess)
		throw std::runtime_error("Attempt to get kernel when login failed.");
	if(haveGotKernel)
		throw std::runtime_error("Attempt to get kernel again.");
	haveGotKernel = true;
	return new Kernel (userName, userPath);
}