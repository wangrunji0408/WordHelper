#ifndef _WORD_H
#define _WORD_H

//#pragma comment(lib, "libjsoncpp.a")

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "json/json.h"

using std::string;
using std::vector; 
using std::istream;
using std::ostream;

// 句子 包含英文和中文
struct Sentence
{
	string str;		// 英文句子
	string trans;	// 中文翻译

	Sentence () = default;
	Sentence (Json::Value const&);
	operator Json::Value () const;
	friend istream& operator >> (istream&, Sentence&);
	friend ostream& operator << (ostream&, Sentence const&);
};

// 某个单词的一个意思
struct Meaning
{
	string 				partOfSpeech;	// 词性
	string 				explain;		// 中文解释
	vector<Sentence> 	exampleList;	// 例句列表

	Meaning () = default;
	Meaning (Json::Value const&);
	operator Json::Value () const;
	friend istream& operator >> (istream&, Meaning&);
	friend ostream& operator << (ostream&, Meaning const&);
};

// 一个单词
struct WordDictInfo
{
	string 				word;				// 英文单词或词组
	string 				pronunciation;		// 发音
	vector<Meaning> 	meaningList;		// 各种意思
	vector<string>		similarWordList;	// 近义词列表
	vector<string>		tagList;			// 标签列表，用于分级：如“四级词”“3500词”

	/* 从JsonValue构造这个类，写入上述变量，用于从文件读入单词
	 * 字符串格式【暂定】为JSON，样例见word.txt
	 */ 
	WordDictInfo () = default;
	WordDictInfo (Json::Value const&);
	operator Json::Value () const;
	friend istream& operator >> (istream&, WordDictInfo&);
	friend ostream& operator << (ostream&, WordDictInfo const&);
};

struct WordUserInfo
{
	string 				userWord;			// 英文单词
	vector<string> 		noteList;			// 用户笔记
	vector<string>		userTagList;		// 用户标签
	vector<Sentence>	userSentenceList;	// 用户例句
	int					rememberLevel;		// 记忆等级，值越大说明越熟练。
	clock_t				lastTestTime;		// 上一次测试这个单词的时间

	WordUserInfo ();
	WordUserInfo (Json::Value const&);
	operator Json::Value () const;
	friend istream& operator >> (istream&, WordUserInfo&);
	friend ostream& operator << (ostream&, WordUserInfo const&);
	bool empty() const;
};

struct WordInfo: public WordDictInfo, public WordUserInfo
{
	// 只能把两个拼起来构造
	WordInfo (WordDictInfo const& dictInfo, WordUserInfo const& userInfo):
		WordDictInfo(dictInfo), WordUserInfo(userInfo) {}
	// 为避免歧义，禁止在此使用empty()，必须先转换为WordUserInfo再使用
	bool empty() const = delete;
	void clearUserInfo ();
};

string toLower (string const&);

// 一些规定
static const string WORD_PART_OF_SPEECH[] = {"n", "v", "a", "ad", "pron", "vi", "num", "vt", "int", "prep", "conj", "phr"};//pron
static const string WORD_TAG[] = {"junior", "senior", "CET4", "CET6", "TOEFL", "GRE"};
static const int WORD_LEVEL_MAX = 7;

#endif	//_WORD_H