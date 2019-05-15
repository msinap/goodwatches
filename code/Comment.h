#ifndef COMMENT_H
#define COMMENT_H

#include "utility.h"

class Comment {
public:
    Comment(string _message, int _id);
    void reply(Map &parameters);
    void hide(Map &parameters);
    vector<string> getOutput();
	bool isShown();
private:
    int id;
    bool shown;
    string message;
    vector<string> replies;
};

#endif
