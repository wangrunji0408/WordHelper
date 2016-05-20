#include "word.h"

// 作者：王润基
// Sentence Meaning WordInfo 三个类 与 Json::Value 的相互转化

Sentence::Sentence (Json::Value const& json)
{
	str = json["str"].asString();
	trans = json["trans"].asString();
}

Sentence::operator Json::Value () const
{
	Json::Value json;
	json["str"] = str;
	json["trans"] = trans;
	return json;
}

Meaning::Meaning (Json::Value const& json)
{
	partOfSpeech = json["POS"].asString();
	explain = json["explain"].asString();

	int const exampleSize = json["example"].size();
	exampleList.resize(exampleSize);
	for(int i = 0; i < exampleSize; ++i)
		exampleList[i] = Sentence( json["example"][i] );
}

Meaning::operator Json::Value () const
{
	Json::Value json;
	json["POS"] = partOfSpeech;
	json["explain"] = explain;
	for(Sentence const& sentence: exampleList)
		json["example"].append( (Json::Value)sentence );
	return json;
}

WordInfo::WordInfo (Json::Value const& json)
{
	word = json["word"].asString();
	pronunciation = json["pron"].asString();
	rememberLevel = json["level"].asInt();
	lastTestTime = json["lasttime"].asInt();

	int const meaningSize = json["mean"].size();
	meaningList.resize(meaningSize);
	for(int i=0; i<meaningSize; ++i)
		meaningList[i] = Meaning( json["mean"][i] );

	int const noteSize = json["note"].size();
	noteList.resize(noteSize);
	for(int i=0; i<noteSize; ++i)
		noteList[i] = json["note"][i].asString();

	int const tagSize = json["tag"].size();
	tagList.resize(tagSize);
	for(int i=0; i<tagSize; ++i)
		tagList[i] = json["tag"][i].asString();

	int const similarSize = json["similar"].size();
	similarWordList.resize(similarSize);
	for(int i=0; i<similarSize; ++i)
		similarWordList[i] = json["similar"][i].asString();
}

WordInfo::operator Json::Value () const
{
	Json::Value json;
	json["word"] = word;
	json["pron"] = pronunciation;
	json["level"] = rememberLevel;
	json["lasttime"] = (int)lastTestTime;
	for(Meaning const& meaning: meaningList)
		json["mean"].append( (Json::Value)meaning );
	for(string const& note: noteList)
		json["note"].append(note);
	for(string const& tag: tagList)
		json["tag"].append(tag);
	for(string const& similar: similarWordList)
		json["similar"].append(similar);
	return json;
}
