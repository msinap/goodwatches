#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class BadRequestError {};
class NotFoundError {};
class PermissionDeniedError {};

string getAndPopBack(vector<string> &vec);

#endif
