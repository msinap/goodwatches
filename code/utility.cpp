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

void checkMustHave(const vector<string> &mustHaveList, Map &parameters) {
    for (string str : mustHaveList)
        if (parameters.find(str) == parameters.end())
            throw BadRequestError();
}

void checkMayHave(const vector<string> &mayHaveList, Map &parameters) {
    for (auto x : parameters) {
        string str = x.first;
        bool found = false;
        for (string mayHave : mayHaveList) {
            if (str == mayHave) {
                found = true;
                break;
            }
        }
        if (!found)
            throw BadRequestError();
    }
}

void checkNumeric(string s) {
    for (int i = 0; i < s.size(); i++)
        if (s[i] > '9' || s[i] < '0')
            throw BadRequestError();
}

void addLeadingZeros(string &s) {
    while (s.size() < 10)
        s = "0" + s;
}
