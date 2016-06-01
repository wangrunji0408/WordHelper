#include "word.h"

// 作者：王润基

// Sentence Meaning Word 三个类 的 输入输出

istream& operator >> (istream& in, Sentence& s)
{
	std::getline(in, s.str, '|');
	std::getline(in, s.trans, '|');
	return in;
}
ostream& operator << (ostream& out, Sentence const& s)
{
	return out << s.str << '|' << s.trans << '|';
}

istream& operator >> (istream& in, Meaning& m)
{
	std::getline(in, m.partOfSpeech, '|');
	std::getline(in, m.explain, '|');
	int n; char c; // c == '|'
	in >> n >> c;
	m.exampleList.resize(n);
	for(int i=0; i<n; ++i)
		in >> m.exampleList[i];
	return in;
}
ostream& operator << (ostream& out, Meaning const& m)
{
	out << m.partOfSpeech << '|';
	out << m.explain << '|';
	out << m.exampleList.size() << '|';
	for(auto const& s: m.exampleList)
		out << s;
	return out;
}