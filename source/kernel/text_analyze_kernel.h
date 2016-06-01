#ifndef _TEXT_ANALYZE_KERNEL_H
#define _TEXT_ANALYZE_KERNEL_H

#include <map>
#include "../word/database.h"

using std::map;

// 文本分析器接口
// 依附于某个单词数据库，可以加载一篇文章，之后通过一些接口获取该文章的各种单词信息
class TextAnalyzeKernel
{
protected:
	DataBase* 	dataBase;
public:
	TextAnalyzeKernel (DataBase*);
	virtual ~TextAnalyzeKernel () {}
	// 加载一篇文章
	virtual void loadText (string const& text) = 0;
	// 统计某个词出现次数
	virtual int countWord (string const& word) const = 0;
	// 获取不在单词数据库中的单词列表
	virtual vector<string> getNotInDataBaseWordList () const = 0;
	// 根据自定的filter函数，返回满足要求的在单词数据库中的单词列表
	virtual vector<const WordInfo*> getInDataBaseWordList (function<bool(const WordInfo*)> filter) const = 0;
	// 获取按出现频率降序排列的单词列表
	virtual vector<const WordInfo*> getWordListByFrequency () const = 0;
};

class TextAnalyzeKernelImpl: public TextAnalyzeKernel
{
protected:
	string 				text;		// 把text加载到这里
	map<string, int> 	wordCount;	// 用于统计词频，在loadText时先clear再修改
protected:
	vector<string> 		textParser (string const& _text);  //新增函数，用于解析文章
public:
	using TextAnalyzeKernel::TextAnalyzeKernel;
	// 实现接口
	virtual void loadText (string const& _text);
	virtual int countWord (string const& word) const;
	virtual vector<string> getNotInDataBaseWordList () const;
	virtual vector<const WordInfo*> getInDataBaseWordList (function<bool(const WordInfo*)> filter) const;
	virtual vector<const WordInfo*> getWordListByFrequency () const;
};

#endif //_TEXT_ANALYZE_KERNEL_H