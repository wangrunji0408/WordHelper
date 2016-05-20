// 作者：彭炳辉

#include "text_analyze_kernel.h"
#include <algorithm>
#include <cctype>

TextAnalyzeKernel::TextAnalyzeKernel (DataBase * wordInfoDataBase) {
	dataBase = wordInfoDataBase;
}

vector<string> TextAnalyzeKernelImpl::textParser (string const& _text) {
	vector<string> textWord;
	string tmpWord;
	struct {
		size_t textPosition = 0;
		bool status = 0;
	} pos;

	while(pos.textPosition < text.size()) {
		if(pos.status == 0) {
			if(isalpha(text[pos.textPosition]))
				pos.status = 1;
				tmpWord = text[pos.textPosition];
		}
		else {
			if(isalpha(text[pos.textPosition])) {
				tmpWord += text[pos.textPosition];
			}
			else {
				textWord.push_back(tmpWord);
				tmpWord = "";
				pos.status = 0;
			}
		}
		pos.textPosition++;
	}
	return textWord;
}

void TextAnalyzeKernelImpl::loadText(string const& _text) {
	text = _text;
	//统计词频
	wordCount.clear();
	for(string const& textWord: textParser(text))
		++wordCount[textWord];
}

int TextAnalyzeKernelImpl::countWord (string const& word) const {
	auto it = wordCount.find(word);
	return it != wordCount.end()? it->second: 0;
}

vector<string> TextAnalyzeKernelImpl::getNotInDataBaseWordList () const {
	vector<string> undetectableWordList;
	for(auto const& pair: wordCount)
		if(dataBase -> getWord(pair.first) != nullptr)
			undetectableWordList.push_back(pair.first);
	return undetectableWordList;
}

vector<const WordInfo*> TextAnalyzeKernelImpl::getInDataBaseWordList(function<bool(const WordInfo*)> filter) const {
	vector<const WordInfo*> word_info;
	for(auto const& pair: wordCount) {
		WordInfo* ptr = dataBase->getWord(pair.first);
		if(ptr != nullptr && filter(ptr))
			word_info.push_back(ptr);
	}
	return word_info;
}

vector<const WordInfo*> TextAnalyzeKernelImpl::getWordListByFrequency () const {
	vector<std::pair<string, int> > word_list;
	auto cmp = [] (std::pair<string, int> x, std::pair<string, int> y) -> bool { return x.second > y.second; };
	for(auto iter = wordCount.begin(); iter != wordCount.end(); iter ++) {
		word_list.push_back(make_pair(iter -> first, iter -> second));
	}
	sort(word_list.begin(), word_list.end(), cmp);
	vector<const WordInfo*> word_info;
	for(auto iter : word_list) {
		if(dataBase -> getWord(iter.first) != nullptr) {
			word_info.push_back(dataBase -> getWord(iter.first));
		}
	}
	return word_info;
}