#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include "../word/json/json.h"


struct Config
{
	int defaultTestSize = 50;
	std::string dictFileName = "dictionary.txt";
	std::string userWordFileName = "user_data/admin/user_word.txt";
	std::string wordSelectStrategy = "random";
	std::string defaultTestModeName = "recall";

	void load (std::istream&);
	void save (std::ostream&) const;
	Config () = default;
	Config (std::string const& userName);
};

#endif //_CONFIG_H