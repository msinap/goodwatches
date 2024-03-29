#include "utility.h"

string getAndPopBack(vector<string> &vec) {
    if (vec.empty())
        throw BadRequestError();
    string ret = vec.back();
    vec.pop_back();
    return ret;
}

string hashFletcherCRC(string s) {
	int hash = 0, sum = 0;
	for (int i = 0; i < s.size(); i++) {
		hash += s[i];
		hash = (hash >> 1) | ((1 & hash) << 15);
		hash &= 0xffff;
		sum = (sum + hash) & 0xffff;
	}
	return intToString((sum << 15) + hash);
}

void print(const vector<string> &header, set<vector<string>> output, const string &title) {
    if (title != "")
        cout << title << endl;
    cout << "#. ";
    for (int i = 0; i < header.size(); i++) {
        cout << header[i];
        if (i != header.size()-1)
            cout << " | ";
    }
    cout << endl;
    int lineNumber = 1;
    for (vector<string> vec : output) {
        cout << lineNumber << ". ";
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i];
            if (i != vec.size()-1)
                cout << " | ";
        }
        cout << endl;
        lineNumber ++;
    }
}

void print(const vector<string> &header, vector<vector<string>> output, const string &title) {
    if (title != "")
        cout << title << endl;
    cout << "#. ";
    for (int i = 0; i < header.size(); i++) {
        cout << header[i];
        if (i != header.size()-1)
            cout << " | ";
    }
    cout << endl;
    int lineNumber = 1;
    for (vector<string> vec : output) {
        cout << lineNumber << ". ";
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i];
            if (i != vec.size()-1)
                cout << " | ";
        }
        cout << endl;
        lineNumber ++;
    }
}

void print(const vector<string> &vec) {
    for (string line : vec)
        cout << line << endl;
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

string intToString(int n) {
    string ret = "";
    while (n > 0) {
        ret += char(n % 10 + '0');
        n /= 10;
    }
    for (int i = 0; i < ret.size()/2; i++)
        swap(ret[i] , ret[ret.size()-i-1]);
    if (ret.size() == 0)
        ret += '0';
    return ret;
}

string makePrecisionTwo(string num) {
	string ret = "";
	int pointPlace;
	for (pointPlace = 0; pointPlace < num.size(); pointPlace ++)
		if (num[pointPlace] == '.')
			break;
	for (int i = 0; i < pointPlace; i++)
		ret += num[i];
	if (num[pointPlace + 1] == '0' && num[pointPlace + 2] == '0')
		return ret;
	ret += num[pointPlace];
	ret += num[pointPlace + 1];
	if (num[pointPlace + 2] == '0')
		return ret;
	ret += num[pointPlace + 2];
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

void checkEmail(string s) {
	int atSignPlace = -1;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '@') {
			if (atSignPlace != -1)
				throw BadRequestError();
			atSignPlace = i;
		}
	}
	if (atSignPlace == -1 || atSignPlace == 0)
		throw BadRequestError();
	int dotPlace = -1;
	for (int i = atSignPlace+1; i < s.size(); i++) {
		if (s[i] == '.') {
			if (dotPlace != -1)
				throw BadRequestError();
			if (i == atSignPlace+1 || i == s.size()-1)
				throw BadRequestError();
			dotPlace = i;
		}
	}
	if (dotPlace == -1)
		throw BadRequestError();
}

string addLeadingZeros(string num) {
    while (num.size() < 10)
        num = "0" + num;
    return num;
}
