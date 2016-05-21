#ifndef _WORD_H
#define _WORD_H

//#pragma comment(lib, "libjsoncpp.a")

#include <string>
#include <vector>
#include <ctime>
#include "json/json.h"

using std::string;
using std::vector; 

// 句子 包含英文和中文
struct Sentence
{
	string str;		// 英文句子
	string trans;	// 中文翻译

	Sentence () {}
	Sentence (Json::Value const&);
	operator Json::Value () const;
};

// 某个单词的一个意思
struct Meaning
{
	string 				partOfSpeech;	// 词性
	string 				explain;		// 中文解释
	vector<Sentence> 	exampleList;	// 例句列表

	Meaning () {}
	Meaning (Json::Value const&);
	operator Json::Value () const;
};

// 一个单词
struct WordInfo
{
	string 				word;				// 英文单词或词组
	string 				pronunciation;		// 发音
	vector<Meaning> 	meaningList;		// 各种意思
	vector<string> 		noteList;			// 笔记
	vector<string>		similarWordList;	// 近义词列表
	vector<string>		tagList;			// 标签列表，用于分级：如“四级词”“3500词”
	int					rememberLevel;		// 记忆等级，值越大说明越熟练。
	clock_t				lastTestTime;		// 上一次测试这个单词的时间

	/* 从JsonValue构造这个类，写入上述变量，用于从文件读入单词
	 * 字符串格式【暂定】为JSON，样例见word.txt
	 */ 
	WordInfo () {}
	WordInfo (Json::Value const&);
	operator Json::Value () const;
};

string toLower (string const&);

// 一些规定
static const string WORD_PART_OF_SPEECH[] = {"n", "v", "a", "ad", "pron", "vi", "num", "vt", "int"};//pron
static const string WORD_TAG[] = {"1600", "3500", "CET4", "CET6", "TOEFL", "GRE"};
static const int WORD_LEVEL_MAX = 7;

#endif	//_WORD_H