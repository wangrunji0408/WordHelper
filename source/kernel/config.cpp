#include "config.h"
#include "../word/json/json.h"

void Config::load (std::istream& in)
{
	Json::Reader reader;
	Json::Value json;
	reader.parse(in, json);

	defaultTestSize = json["defaultTestSize"].asInt();
	dictFileName = json["dictFileName"].asString();
	userWordFileName = json["userWordFileName"].asString();
	wordSelectStrategy = json["wordSelectStrategy"].asString();
	defaultTestModeName = json["defaultTestModeName"].asString();
}

void Config::save (std::ostream& out) const
{
	Json::Value json;
	json["defaultTestSize"] = defaultTestSize;
	json["dictFileName"] = dictFileName;
	json["userWordFileName"] = userWordFileName;
	json["wordSelectStrategy"] = wordSelectStrategy;
	json["defaultTestModeName"] = defaultTestModeName;
	out << json;
}

Config::Config (std::string const& userName):
	Config()
{
	userWordFileName = "user_data/" + userName + "/user_word.txt";
}