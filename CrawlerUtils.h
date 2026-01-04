#ifndef CRAWLERUTILS_H
#define CRAWLERUTILS_H

#include <string>
#include <vector>
using namespace std;

string cleanHtml(string rawHtml);
vector<string> extractLinks(string html);
string downloadUrl(string url);

#endif