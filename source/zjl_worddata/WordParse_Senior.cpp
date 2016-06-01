// 作者：赵嘉霖

#include <iostream>
#include <fstream>
#include <sstream>

#include "database.h"

using namespace std;

string delSpace (string const& s)
{
	int i=0, j=s.size() - 1;
	while(i < s.size() && s[i] == ' ')
		++i;
	while(j > 0 && (s[j] == ' ' || s[j] == '\r'))
		--j;
	return s.substr(i, j-i+1);
}

int main ()
{
	DataBaseImpl* dataBase = new DataBaseImpl;
	ifstream ifst("3500word.txt");
	ifstream fin("worddata_zjl.txt");
	ofstream failedOut ("failedWord.txt");
	dataBase -> loadFromIStream(fin);
	string s;
	while (getline(ifst, s) && s.size())
	{
		if (s.size() > 2)
		{
			WordInfo* word = new WordInfo;
			int sign = 0;
			int signal = 0;
			int pos = 0;
			for (int i = 1; i < s.size() - 1; i ++)
			{
				if (s[i] == ' ' && s[i + 1] == '[')
				{
					sign ++;
					signal = i;
				}
			}
			if (sign == 1)
			{
				word -> word = s.substr(0, signal);
			}
			else 
			{
				continue;
			}
			for (int i = signal; i < s.size() - 1; i ++)
			{
				if (s[i] == ']' && s[i + 1] == ' ')
				{
					sign ++;
					pos = i;
				}
			}
			if (sign == 2)
			{
				word -> pronunciation = s.substr(signal + 2, pos - signal - 2); // 不加[]
			}
			else
			{
				continue;
			}
			signal = 0;
			string part;
			while (pos < s.size())
			{
				if (signal == 0)
				{
					for (int i = 0; i < sizeof(WORD_PART_OF_SPEECH) / sizeof(WORD_PART_OF_SPEECH[0]); i ++)
					{
						if (s.size() - pos > WORD_PART_OF_SPEECH[i].size())
						{
							if (s.substr(pos, WORD_PART_OF_SPEECH[i].size()) == WORD_PART_OF_SPEECH[i] && s[pos + WORD_PART_OF_SPEECH[i].size()] == '.')
							{
								part = WORD_PART_OF_SPEECH[i];
								signal = pos + WORD_PART_OF_SPEECH[i].size();
								sign ++;
								break;
							}
						}
					}
				}
				else
				{
					for (int i = 0; i < sizeof(WORD_PART_OF_SPEECH) / sizeof(WORD_PART_OF_SPEECH[0]); i ++)
					{
						if (s.size() - pos > WORD_PART_OF_SPEECH[i].size())
						{
							if (s.substr(pos, WORD_PART_OF_SPEECH[i].size()) == WORD_PART_OF_SPEECH[i] && s[pos + WORD_PART_OF_SPEECH[i].size()] == '.')
							{
								if (part.size() != 0)
								{
									Meaning* meaning = new Meaning;
									meaning -> partOfSpeech = part;
									meaning -> explain = s.substr(signal + 1, pos - signal - 1);
									word -> meaningList.push_back(*meaning);
								}
								part = WORD_PART_OF_SPEECH[i];
								signal = pos + WORD_PART_OF_SPEECH[i].size();
								break;
							}
						}
					}
					if (pos == s.size() - 1)
					{
						if (part.size() != 0)
						{
							Meaning* meaning = new Meaning;
							meaning -> partOfSpeech = part;
							meaning -> explain = s.substr(signal + 1, pos - signal);
							word -> meaningList.push_back(*meaning);
						}
					}
					if (s[pos] == ',' || s[pos] == ';')
					{
						if (part.size() != 0)
						{
							Meaning* meaning = new Meaning;
							meaning -> partOfSpeech = part;
							meaning -> explain = s.substr(signal + 1, pos - signal - 1);
							word -> meaningList.push_back(*meaning);
							signal = pos;
						}
					}
				}
				pos ++;
			}
			if (sign == 3)
			{
				word->word = delSpace(word->word);
				for(auto& meaning: word->meaningList)
					meaning.explain = delSpace(meaning.explain);
				word->tagList.push_back(WORD_TAG[1]);
				dataBase -> addWord(word);
			}
			else
			{
				failedOut << s << endl;
			}
		}
		
	}
	fin.close();
	ofstream fout("worddata_zjl.txt");
	dataBase -> writeToOStream(fout);

}