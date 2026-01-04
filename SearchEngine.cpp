#include "SearchEngine.h"
#include "CrawlerUtils.h"
#include "GUIHelper.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <windows.h>

SearchEngine::SearchEngine() : pageCounter(1) {}

void SearchEngine::startCrawling(string seedUrl, int maxPages) {
    while(!urlQueue.empty()) urlQueue.pop();
    visitedUrls.clear();

    urlQueue.push(seedUrl);
    visitedUrls.insert(seedUrl);

    int pagesCrawled = 0;
    
    drawHeader("SYSTEM CRAWLING");
    cout << "Seed: " << seedUrl << endl;
    drawLine();

    while (!urlQueue.empty() && pagesCrawled < maxPages) {
        string currentUrl = urlQueue.front();
        urlQueue.pop();

        string rawHtml = downloadUrl(currentUrl);
        if (rawHtml == "ERROR" || rawHtml.empty()) continue;

        string cleanText = cleanHtml(rawHtml);
        WebPage newPage = {pageCounter, currentUrl, cleanText};
        database.push_back(newPage);

        stringstream ss(cleanText);
        string word;
        while (ss >> word) {
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
            if (word.length() > 2) index.addWord(word, pageCounter);
        }
        setColor(10); 
        cout << "   [+] Indexed Page ID: " << pageCounter << endl;
        setColor(7); 
        pageCounter++;
        pagesCrawled++;

        vector<string> newLinks = extractLinks(rawHtml);
        for (string link : newLinks) {
            if (visitedUrls.find(link) == visitedUrls.end()) {
                visitedUrls.insert(link);
                urlQueue.push(link);
            }
        }
    }
    cout << "\n[BFS] Crawling Complete. Press Enter.";
    cin.get(); 
}

int SearchEngine::getValidInput() {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            setColor(12); cout << "Invalid input! Enter a number: "; setColor(7);
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return choice; 
        }
    }
}

void SearchEngine::handleMenu() {
    int choice;
    do {
        drawHeader("MINI-GOOGLE DASHBOARD");
        cout << "Current: "; setColor(11); cout << browser.getCurrentUrl() << endl; setColor(7);
        drawLine();
        
        cout << " [1] View Pages & Search" << endl; 
        cout << " [2] Crawl New Website" << endl;
        cout << " [3] Go Back" << endl;
        cout << " [4] Go Forward" << endl;
        cout << " [5] Exit" << endl;
        drawLine();
        cout << "Enter selection >> ";
        
        choice = getValidInput(); 

        switch (choice) {
            case 1: showPagesAndSearch(); break;
            case 2: {
                string url;
                cout << "Enter URL to Crawl: ";
                getline(cin, url);
                startCrawling(url);
                break;
            }
            case 3: browser.goBack(); break;
            case 4: browser.goForward(); break;
            case 5: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice." << endl; Sleep(1000);
        }
    } while (choice != 5);
}

void SearchEngine::showPagesAndSearch() {
    if (database.empty()) {
        cout << "\n[!] Database empty. Use Option 2 first!" << endl;
        Sleep(2000);
        return;
    }

    drawHeader("AVAILABLE PAGES");
    for (size_t i = 0; i < database.size(); i++) {
        cout << " [" << (i + 1) << "] " << database[i].url << endl;
    }
    drawLine();
    cout << "Select page # to visit (0 to cancel) >> ";
    
    int pageChoice = getValidInput();

    if (pageChoice > 0 && pageChoice <= database.size()) {
        WebPage& wp = database[pageChoice - 1];
        browser.visit(wp.url, wp.cleanContent);

        drawHeader("GOOGLE SEARCH");
        cout << "Searching inside: " << wp.url << endl;
        cout << "Enter Keyword >> ";
        string query;
        getline(cin, query);

        displayKeywordIndex(query);
        cout << "\nPress Enter to return...";
        cin.get();

    } else if (pageChoice == 0) {
        return;
    } else {
        cout << "Invalid Page." << endl;
        Sleep(1000);
    }
}

void SearchEngine::displayKeywordIndex(string query) {
    cout << "\nResults for '"; setColor(14); cout << query; setColor(7); cout << "':" << endl;
    PageNode* results = index.getSearchResults(query);

    if (!results) {
        setColor(12); cout << "X No matches found in index." << endl; setColor(7);
        return;
    }

    while (results != nullptr) {
        string url = "Unknown";
        for (const auto& page : database) {
            if (page.id == results->pageId) {
                url = page.url;
                break;
            }
        }
        cout << " > Found in: " << url << " (Freq: " << results->frequency << ")" << endl;
        results = results->next;
    }
}