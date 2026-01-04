#include "InvertedIndex.h"
#include <algorithm>

InvertedIndex::InvertedIndex() : head(nullptr) {}

void InvertedIndex::addWord(string keyword, int pageId) {
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
    KeywordNode* kNode = findKeyword(keyword);
    
    if (!kNode) {
        kNode = new KeywordNode(keyword);
        kNode->next = head;
        head = kNode;
    }

    PageNode* pNode = kNode->pageHead;
    if (!pNode) {
        kNode->pageHead = new PageNode(pageId, 1);
    } else {
        while (pNode != nullptr) {
            if (pNode->pageId == pageId) {
                pNode->frequency++;
                return;
            }
            if (pNode->next == nullptr) break;
            pNode = pNode->next;
        }
        pNode->next = new PageNode(pageId, 1);
    }
}

KeywordNode* InvertedIndex::findKeyword(string keyword) {
    KeywordNode* current = head;
    while (current != nullptr) {
        if (current->keyword == keyword) return current;
        current = current->next;
    }
    return nullptr;
}

PageNode* InvertedIndex::getSearchResults(string keyword) {
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
    KeywordNode* node = findKeyword(keyword);
    return (node) ? node->pageHead : nullptr;
}