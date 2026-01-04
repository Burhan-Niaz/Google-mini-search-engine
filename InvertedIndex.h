#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include "DataStructures.h"

class InvertedIndex {
private:
    KeywordNode* head;
public:
    InvertedIndex();
    void addWord(string keyword, int pageId);
    KeywordNode* findKeyword(string keyword);
    PageNode* getSearchResults(string keyword);
};

#endif