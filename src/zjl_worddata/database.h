#ifndef _DATABASE_H
#define _DATABASE_H

#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include "word.h"

using std::vector;
using std::function;
using std::istream;
using std::ostream;

// 单词数据库接口
class DataBase
{
public:
	// 从一个输入流构造类
	virtual void loadFromIStream (istream&) = 0;
	// 把信息保存到一个输出流
	virtual void writeToOStream (ostream&) const = 0;
	// 根据自定的filter函数，返回满足要求的单词列表
	virtual vector<WordInfo*> getWordList ( function<bool(WordInfo const&)> ) const = 0;
	// 根据字符串查找单词，要求字符串严格匹配
	virtual WordInfo* getWord (string const&) const = 0;
	// 向数据库中加入一个单词
	virtual void addWord (WordInfo*) = 0;
};

// 单词数据库实现类
class DataBaseImpl: public DataBase
{
protected:
	// 数据库，根据单词字符串索引WordInfo指针
	std::map<string, WordInfo*>	 stringToWordPtr;

public:
	// 析构函数，依次delete每个WordInfo*
	~DataBaseImpl ();
	// 实现接口
	virtual void loadFromIStream (istream&);
	virtual void writeToOStream (ostream&) const;
	virtual vector<WordInfo*> getWordList ( function<bool(WordInfo const&)> ) const;
	virtual WordInfo* getWord (string const&) const;
	virtual void addWord (WordInfo*);
};

#endif