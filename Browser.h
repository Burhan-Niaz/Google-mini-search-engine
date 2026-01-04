#ifndef BROWSER_H
#define BROWSER_H

#include <stack>
#include <string>
using namespace std;

class Browser {
private:
    stack<string> backStack;
    stack<string> forwardStack;
    string currentUrl;
public:
    Browser();
    string getCurrentUrl();
    void visit(string url, string content);
    void goBack();
    void goForward();
};

#endif