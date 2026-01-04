#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <vector>
#include <queue>
#include <set>
#include "DataStructures.h"
#include "InvertedIndex.h"
#include "Browser.h"

class SearchEngine {
private:
    vector<WebPage> database;
    InvertedIndex index;
    Browser browser;
    int pageCounter;
    queue<string> urlQueue;
    set<string> visitedUrls;

public:
    SearchEngine();
    void startCrawling(string seedUrl, int maxPages = 3);
    int getValidInput();
    void handleMenu();
    void showPagesAndSearch();
    void displayKeywordIndex(string query);
};

#endif