#ifndef _SHELL_H
#define _SHELL_H

#include "../kernel/kernel.h"

// 命令交互UI
// 依附于一个Kernel。每次从流in输入命令，调用Kernel接口，向流out输出结果
class Shell_Base
{
protected:
	Kernel* 	kernel;
	istream& 	in;
	ostream& 	out;
public:
	Shell_Base (Kernel* _kernel, istream& _in, ostream& _out);
};

class Shell: public Shell_Base
{
	int const DEFAULT_HISTORY_COUNT = 10;
	int const CONSOLE_WIDTH = 80;
	vector<string> commandHistoryList;
protected:
	// 功能
	// 显示单词
	void printWordSimple (const WordInfo*) const;
	void printWordFull (const WordInfo*) const;
	void printWordInJson (const WordInfo*) const;
	// 单词测试
	void Test_SpellMode (int size) const;
	void Test_RecallMode (int size) const;
	void Test_ChoiceMode (int size, bool choiceEnglish) const;
	bool Test (string const& modeName) const;			// 返回是否成功
	// 文本分析
	void textAnalyze (string const& fileName) const;
	// 查询单词（自动检测中文/英文）
	void searchWord (string const& word) const;
	// 单词管理
	void wordManage (const WordInfo*) const;
	// 显示变量名
	void printVariables () const;
	// print
	void printLn (string const&) const;					// 输出一行
	void printTitle (string const&) const;				// 输出标题
	void printDividingLine () const;					// 输出分割线
	void printHello () const;							// 输出欢迎信息
	void printHelpInfo () const;						// 输出帮助
	void printHistory (int count) const;				// 输出查询历史
	void printError (string const& errorInfo) const;	// 输出错误信息
	void clearScreen () const;							// 清屏
	// 解析命令字符串并调用相应功能函数，若命令为exit返回false，否则返回true
	bool parseCommand (string const&);
	bool parseCommandInWordKernel(string const& command, WordKernel* word_kernel, const WordInfo* word) const;
	void test_word_manage(WordInfo* const, const TestKernel*, bool&)const;
public:
	using Shell_Base::Shell_Base;
	void run ();
};

#endif //_SHELL_H