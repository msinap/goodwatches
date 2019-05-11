#include "utility.h"

string getAndPopBack(vector<string> &vec) {
    if (vec.empty())
        throw BadRequestError();
    string ret = vec.back();
    vec.pop_back();
    return ret;
}
