#include "CrawlerUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

string cleanHtml(string rawHtml) {
    string text = "";
    bool insideTag = false;
    for (size_t i = 0; i < rawHtml.length(); i++) {
        if (rawHtml[i] == '<') { insideTag = true; continue; }// when the tagg < found stop adding txt
        if (rawHtml[i] == '>') { insideTag = false; text += ' '; continue; }// when the tagg > found start adding txt
        if (!insideTag) text += rawHtml[i];// if we are not inside the taggs then add the text
    }
    return text;
}

vector<string> extractLinks(string html) {
    vector<string> links;
    string searchStr = "href=\"http";  // beacuse in the html tags are of this type so the <a href="http://google.com">Link</a> 
    size_t pos = 0;// pos==position for search of link in txt
    while ((pos = html.find(searchStr, pos)) != string::npos) {// npos means end of the string
        size_t startQuote = pos + 6; // to remove h, r, e, f, =, " it we started from 6 postion from where url started
        size_t endQuote = html.find("\"", startQuote);// "\" it's mean that " "boundary of link beacuse if we put " " " the compiler will show the error , in double quotes "\" means boundary of link
        if (endQuote != string::npos) {
            links.push_back(html.substr(startQuote, endQuote - startQuote));
        }
        pos = endQuote;
    }
    return links;
}

string downloadUrl(string url) {
    cout << "   -> Downloading: " << url << "..." << endl;
    remove("temp_crawl.txt"); // if there is already temp_crawl.txt so delete it first
    //curl.exe is lib execution file to download the web page from internet
    string command = "curl.exe -s -L -m 5 \"" + url + "\" -o temp_crawl.txt";// -s for silent mode, -L to follow redirected url and go to that page, -m 5 to set max time 5 seconds
    int result = system(command.c_str());//coomand to sys. to execute the curl command
    if (result != 0) return "ERROR";//if the internet is not conneected or url is invalid
    
    ifstream file("temp_crawl.txt");
    if (!file.is_open()) return "ERROR";// if the file  not open return error
    
    stringstream buffer;
    buffer<<file.rdbuf();
    file.close(); 
    return buffer.str();
}