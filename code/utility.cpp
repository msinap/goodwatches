#include "utility.h"

string getAndPopBack(vector<string> &vec) {
    if (vec.empty())
        throw BadRequestError();
    string ret = vec.back();
    vec.pop_back();
    return ret;
}

int stringToInt(string s) {
    int ret = 0;
    for (int i = 0; i < s.size(); i++) {
        ret *= 10;
        if (s[i] < '0' || s[i] > '9')
            throw BadRequestError();
        ret += s[i] - '0';
    }
    return ret;
}
