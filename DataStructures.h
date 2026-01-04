#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <string>
using namespace std;

struct PageNode {
    int pageId;
    int frequency;
    PageNode* next;
    PageNode(int id, int freq) : pageId(id), frequency(freq), next(nullptr) {}
};

struct KeywordNode {
    string keyword;
    PageNode* pageHead; 
    KeywordNode* next;
    KeywordNode(string k) : keyword(k), pageHead(nullptr), next(nullptr) {}
};

struct WebPage {
    int id;
    string url;
    string cleanContent;
};

#endif