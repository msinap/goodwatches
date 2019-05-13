#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

typedef map<string, string> Map;

class BadRequestError {};
class NotFoundError {};
class PermissionDeniedError {};

string getAndPopBack(vector<string> &vec);

int stringToInt(string s);
string intToString(int n);

void checkMustHave(const vector<string> &mayHaveList, map<string, string> &parameters);
void checkMayHave(const vector<string> &mayHaveList, map<string, string> &parameters);

void checkNumeric(string s);
void addLeadingZeros(string &num);

void print(const vector<string> &header, set<vector<string>> output, const string &title);

#endif
