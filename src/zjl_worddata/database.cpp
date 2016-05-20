#include "database.h"

// 以下作者：王润基

DataBaseImpl::~DataBaseImpl ()
{
	for(auto const& pair: stringToWordPtr)
		delete pair.second;
}

void DataBaseImpl::loadFromIStream (istream& in)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(in, root);

	stringToWordPtr.clear();

	int const wordSize = root.size();
	for(int i = 0; i < wordSize; ++i)
	{
		WordInfo* ptr = new WordInfo(root[i]);
		stringToWordPtr[ptr->word] = ptr;
	}
}
void DataBaseImpl::writeToOStream (ostream& out) const
{
	Json::FastWriter writer;
	Json::Value root;
	for(auto const& pair: stringToWordPtr)
		root.append( (Json::Value)(*(pair.second)) );
	out << writer.write(root);
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