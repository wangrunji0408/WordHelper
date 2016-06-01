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
	word->userTagList.push_back(tagContent);
}
/*
void WordKernel::addMeaning(string const& partOfSpeech, string const& explain) {
	struct Meaning newMeaning;
	newMeaning.partOfSpeech = partOfSpeech;
	newMeaning.explain = explain;
	word->meaningList.push_back(newMeaning);
	//word->meaningList.push_back( Meaning{partOfSpeech, explain} );
}
*/
 void WordKernel::addSentence (string const& str, string const& trans) {
 	struct Sentence sentenceToAdd;
 	sentenceToAdd.str = str;
 	sentenceToAdd.trans = trans;
 	word->userSentenceList.push_back(sentenceToAdd);
 }
 void WordKernel::delNote (int noteId) {
 	word->noteList.erase(word->noteList.begin() + noteId);
 }
 void WordKernel::delTag (string const& tagcontent) {
 	auto it = word->userTagList.begin();
 	while(it != word->userTagList.end()) {
 		if(*it == tagcontent)
 			it = word->userTagList.erase(it);
 		else
 			it++;
 	} 
 }
 /*
 void WordKernel::delMeaning (int meaningId) {
 	word->meaningList.erase(word->meaningList.begin() + meaningId);
 }
 */
 void WordKernel::delSentence(int sentenceId) {
 	word->userSentenceList.erase(word->userSentenceList.begin() + sentenceId);
 }

