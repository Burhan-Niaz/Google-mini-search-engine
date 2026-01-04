#include "Browser.h"
#include "GUIHelper.h"
#include <iostream>

Browser::Browser() : currentUrl("Home") {}

string Browser::getCurrentUrl() { return currentUrl; }

void Browser::visit(string url, string content) {
    if (currentUrl != url) {
        if (currentUrl != "Home") {
            backStack.push(currentUrl);
        }
        currentUrl = url;
        while (!forwardStack.empty()) forwardStack.pop(); 
    }

    drawHeader("BROWSER VIEW");
    setColor(14); 
    cout << " ADDRESS: " << url << endl;
    drawLine();
    setColor(7); 
    
    if (content.length() > 600) {
        cout << content.substr(0, 600) << "..." << endl;
        setColor(8);
        cout << "\n[...Content truncated for readability...]" << endl;
    } else if (!content.empty()) {
        cout << content << endl;
    } else {
        cout << "(Web Page Loaded / No Text Content)" << endl;
    }
    drawLine();
    cout << "\nPress Enter to return to menu...";
    cin.get(); 
}

void Browser::goBack() {
    if (backStack.empty()) {
        cout << "   [Browser] No history to go back to." << endl;
        return;
    }
    forwardStack.push(currentUrl);
    currentUrl = backStack.top();
    backStack.pop();
    cout << "\n   [Browser] Went Back to: " << currentUrl << endl;
}

void Browser::goForward() {
    if (forwardStack.empty()) {
        cout << "   [Browser] No forward history." << endl;
        return;
    }
    backStack.push(currentUrl);
    currentUrl = forwardStack.top();
    forwardStack.pop();
    cout << "\n   [Browser] Went Forward to: " << currentUrl << endl;
}