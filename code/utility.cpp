#include "utility.h"

string getAndPopBack(vector<string> &vec) {
    if (vec.empty())
        throw NotFoundError();
    string ret = vec.back();
    vec.pop_back();
    return ret;
}
