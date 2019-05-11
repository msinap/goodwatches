#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

class BadRequestError {};
class NotFoundError {};
class PermissionDeniedError {};

string getAndPopBack(vector<string> &vec);


#endif
