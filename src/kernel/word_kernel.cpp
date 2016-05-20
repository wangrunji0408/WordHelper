// 作者：彭炳辉

#include "word_kernel.h"

WordKernel::WordKernel(WordInfo* _word) {
	word = _word;
}
const WordInfo* WordKernel::getWordInfoPtr() const {
	return word;
}
 //以下是修改方法
void WordKernel::addNote (string const& noteContent) {
	word->noteList.push_back(noteContent);
}
void WordKernel::addTag (string const& tagContent) {
	word->tagList.push_back(tagContent);
}
void WordKernel::addMeaning(string const& partOfSpeech, string const& explain) {
	struct Meaning newMeaning;
	newMeaning.partOfSpeech = partOfSpeech;
	newMeaning.explain = explain;
	word->meaningList.push_back(newMeaning);
	//word->meaningList.push_back( Meaning{partOfSpeech, explain} );
}
 void WordKernel::addSentence (int meaningID, string const& str, string const& trans) {
 	struct Sentence sentenceToAdd;
 	sentenceToAdd.str = str;
 	sentenceToAdd.trans = trans;
 	word->meaningList[meaningID].exampleList.push_back(sentenceToAdd);
 	//word->meaningList.at(meaningID).exampleList.push_back( Sentence{str, trans} );
 }
 void WordKernel::delNote (int noteId) {
 	word->noteList.erase(word->noteList.begin() + noteId);
 }
 void WordKernel::delTag (string const& tagcontent) {
 	auto it = word->tagList.begin();
 	while(it != word->tagList.end()) {
 		if(*it == tagcontent)
 			it = word->tagList.erase(it);
 		else
 			it++;
 	} 
 }
 void WordKernel::delMeaning (int meaningId) {
 	word->meaningList.erase(word->meaningList.begin() + meaningId);
 }
 void WordKernel::delSentence(int meaningId, int sentenceId) {
 	auto& exampleList = word->meaningList.at(meaningId).exampleList;
 	exampleList.erase(exampleList.begin() + sentenceId);
 }

