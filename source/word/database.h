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

static const auto alwaysTrue = [](WordInfo const&) {return true;};

// 单词数据库接口
class DataBase
{
public:
	virtual ~DataBase() {}
	// （从一个输入流）读取用户信息
	virtual void loadUserInfo (istream&) = 0;
	// （向一个输出流）保存用户信息
	virtual void saveUserInfo (ostream&) const = 0;
	// 清除用户信息
	virtual void clearUserInfo () = 0;
	// （从一个输入流）读取词典信息
	virtual void loadDictInfo (istream&) = 0;
	// （向一个输出流）写入词典信息 由于对词典只读，一般不可调用
	virtual void saveDictInfo (ostream&) const = 0;
	// 根据自定的filter函数，返回满足要求的单词列表
	virtual vector<WordInfo*> getWordList ( function<bool(WordInfo const&)> = alwaysTrue ) const = 0;
	virtual vector<const WordInfo*> getWordListConst ( function<bool(WordInfo const&)> = alwaysTrue ) const = 0;
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
	virtual void loadUserInfo (istream&);
	virtual void saveUserInfo (ostream&) const;
	virtual void clearUserInfo ();
	virtual void loadDictInfo (istream&);
	virtual void saveDictInfo (ostream&) const;
	virtual vector<WordInfo*> getWordList ( function<bool(WordInfo const&)> ) const;
	virtual vector<const WordInfo*> getWordListConst ( function<bool(WordInfo const&)> ) const;
	virtual WordInfo* getWord (string const&) const;
	virtual void addWord (WordInfo*);
};

#endif