#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
using namespace std;

typedef map<string, string> Map;

class BadRequestError {};
class NotFoundError {};
class PermissionDeniedError {};

string getAndPopBack(vector<string> &vec);

int stringToInt(string s);
string intToString(int n);
string makePrecisionTwo(string num);

void checkMustHave(const vector<string> &mayHaveList, map<string, string> &parameters);
void checkMayHave(const vector<string> &mayHaveList, map<string, string> &parameters);

void checkNumeric(string s);
string addLeadingZeros(string num);

void print(const vector<string> &header, set<vector<string>> output, const string &title);
void print(const vector<string> &vec);

#endif
