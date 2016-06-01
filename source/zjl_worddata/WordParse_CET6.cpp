// 作者：赵嘉霖

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

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
	ifstream ifst("CET6.txt");
	ifstream fin("worddata_zjl.txt");
	ofstream failedOut ("failedWord.txt");
	dataBase -> loadFromIStream(fin);
	string s;
	int num = 0;
	while (getline(ifst, s))
	{

		if (s.size() < 2)
		{
			continue;
		}
		//failedOut << num ++ << endl;
		if (s.size() > 2)
		{

			WordInfo* word = new WordInfo;
			int sign = -1;
			int signal = 0;
			int pos = 0;
			int start = 0;
			bool hasfound = false;
			for (int i = 0; i < s.size() - 1; i ++)
			{
				if (isalpha(s[i]))
				{
					start = i;
					sign ++;
					//failedOut << i << endl;
					break;
				}
			}
			if (sign == -1)
			{
				continue;
			}

			for (int i = start; i < s.size() - 1; i ++)
			{
				if (s[i] == '/')
				{
					sign ++;
					signal = i;
					break;
				}
			}
			if (sign == 1)
			{
				word -> word = s.substr(start, signal - start);
				if (dataBase -> getWord(word -> word ))
				{
					word = dataBase -> getWord(word -> word );
					hasfound = true;
				}
			}
			else 
			{
				continue;
			}

			for (int i = signal + 1; i < s.size() - 1; i ++)
			{
				if (s[i] == '/')
				{
					sign ++;
					pos = i;
					break;
				}
			}
			if (sign == 2)
			{
				if (!hasfound)
				{
					word -> pronunciation = s.substr(signal + 1, pos - signal - 1); // 不加[]
				}
				
			}
			else
			{
				continue;
			}

			signal = 0;
			string part;
			while (pos < s.size())
			{
				if (s[pos] == '.')
				{
					pos ++;
					continue;
				}
				if (signal == 0)
				{
					for (int i = 0; i < sizeof(WORD_PART_OF_SPEECH) / sizeof(WORD_PART_OF_SPEECH[0]); i ++)
					{
						if (s.size() - pos > WORD_PART_OF_SPEECH[i].size())
						{
							if (s.substr(pos, WORD_PART_OF_SPEECH[i].size()) == WORD_PART_OF_SPEECH[i])
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
							if (s.substr(pos, WORD_PART_OF_SPEECH[i].size()) == WORD_PART_OF_SPEECH[i])
							{
								if (part.size() != 0)
								{
									Meaning* meaning = new Meaning;
									meaning -> partOfSpeech = part;
									meaning -> explain = s.substr(signal + 1, pos - signal - 1);
									bool has = false;
									for (auto mean : word -> meaningList)
									{
										if (mean.partOfSpeech == meaning -> partOfSpeech && mean.explain == meaning -> explain)
										{
											has = true;
										}
									}
									if (!has)
									{
										word -> meaningList.push_back(*meaning);
									}
									
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
							bool has = false;
							for (auto mean : word -> meaningList)
							{
								if (mean.partOfSpeech == meaning -> partOfSpeech && mean.explain == meaning -> explain)
								{
									has = true;
								}
							}
							if (!has)
							{
								word -> meaningList.push_back(*meaning);
							}
						}
					}
					if (s[pos] == ',' || s[pos] == ';')
					{
						if (part.size() != 0)
						{
							Meaning* meaning = new Meaning;
							meaning -> partOfSpeech = part;
							meaning -> explain = s.substr(signal + 1, pos - signal - 1);
							bool has = false;
							for (auto mean : word -> meaningList)
							{
								if (mean.partOfSpeech == meaning -> partOfSpeech && mean.explain == meaning -> explain)
								{
									has = true;
								}
							}
							if (!has)
							{
								word -> meaningList.push_back(*meaning);
							}
							signal = pos;
						}
					}
				}
				pos ++;
			}
			if (sign == 3)
			{

				word->word = delSpace(word->word);
				bool isEnglish = true;
				for (int i = 0; i < word -> word.size(); i ++)
				{
					if (!isalpha(word -> word[i]))
					{
						isEnglish = false;
					}
				}
				if (!isEnglish)
				{
					continue;
				}
				word -> pronunciation = delSpace(word -> pronunciation);
				for(auto& meaning: word->meaningList)
					meaning.explain = delSpace(meaning.explain);
				bool has = false;
				for (int i = 0; i < word -> tagList.size(); i ++)
				{
					if (word -> tagList[i] == WORD_TAG[3])
					{
						has = true;
					}
				}
				if (!has)
				{
					word->tagList.push_back(WORD_TAG[3]);
				}
				
				if (!hasfound)
				{
					dataBase -> addWord(word);
				}
				
			}
			else
			{
				failedOut << s << endl;
			}

		}
		else
		{

		}
		
	}
	fin.close();
	ofstream fout("worddata_zjl.txt");
	dataBase -> writeToOStream(fout);

}