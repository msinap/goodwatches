#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

typedef map<string, string> Map;

class BadRequestError {};
class NotFoundError {};
class PermissionDeniedError {};

string getAndPopBack(vector<string> &vec);

int stringToInt(string s);

void checkMustHave(const vector<string> &mayHaveList, map<string, string> &parameters);
void checkMayHave(const vector<string> &mayHaveList, map<string, string> &parameters);

void checkNumeric(string s);
void addLeadingZeros(string &num);

#endif
