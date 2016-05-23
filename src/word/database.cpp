#include "database.h"

// 以下作者：王润基

DataBaseImpl::~DataBaseImpl ()
{
	for(auto const& pair: stringToWordPtr)
		delete pair.second;
}

void DataBaseImpl::loadUserInfo (istream& in)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(in, root);

	clearUserInfo();

	int const wordSize = root.size();
	for(int i = 0; i < wordSize; ++i)
	{
		string const wordString = root[i]["word"].asString();
		if(stringToWordPtr[wordString] == nullptr)
			std::cerr << "DataBase: No this word in dictionary: " << wordString << std::endl;
		else
		{
			WordUserInfo& userInfo = *stringToWordPtr[wordString];
			userInfo = WordUserInfo(root[i]);
		}
	}
}
void DataBaseImpl::saveUserInfo (ostream& out) const
{
	Json::Value root;
	for(auto const& pair: stringToWordPtr)
	{
		WordUserInfo const& userInfo = *pair.second;
		if(!userInfo.empty())
			root.append( (Json::Value)userInfo );
	}
	out << root;
}
void DataBaseImpl::clearUserInfo ()
{
	for(auto const& pair: stringToWordPtr)
		pair.second->clearUserInfo();
}

void DataBaseImpl::loadDictInfo (istream& in)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(in, root);

	stringToWordPtr.clear();

	int const wordSize = root.size();
	for(int i = 0; i < wordSize; ++i)
	{
		WordInfo* ptr = new WordInfo( WordDictInfo(root[i]), WordUserInfo() );
		stringToWordPtr[ptr->word] = ptr;
	}
}
void DataBaseImpl::saveDictInfo (ostream& out) const
{
	//Json::FastWriter writer;
	Json::Value root;
	for(auto const& pair: stringToWordPtr)
		root.append( (Json::Value)(WordDictInfo const&)(*(pair.second)) );
	out << root;
}

vector<const WordInfo*> DataBaseImpl::getWordListConst ( function<bool(WordInfo const&)> f ) const
{
	vector<const WordInfo*> words;
	for(auto iter = stringToWordPtr.begin(); iter != stringToWordPtr.end(); iter ++)
	{
		if (f(*(iter -> second)))
		{
			words.push_back(iter -> second);
		}
	}
	return words;
}

// 以下作者：赵嘉霖

vector<WordInfo*> DataBaseImpl::getWordList ( function<bool(WordInfo const&)> f ) const
{
	vector<WordInfo*> words;
	for(auto iter = stringToWordPtr.begin(); iter != stringToWordPtr.end(); iter ++)
	{
		if (f(*(iter -> second)))
		{
			words.push_back(iter -> second);
		}
	}
	return words;
}
WordInfo* DataBaseImpl::getWord (string const& str) const
{
	auto it = stringToWordPtr.find(str);
	return it == stringToWordPtr.end()? nullptr: it->second;
}
void DataBaseImpl::addWord (WordInfo* word)
{
	stringToWordPtr.insert(std::make_pair(word -> word, word));
}