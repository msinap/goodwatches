#ifndef COMMENT_H
#define COMMENT_H

#include "utility.h"

class Comment {
public:
    Comment(string _message, int _id);
    void reply(Map &parameters);
    void hide(Map &parameters);
    vector<string> getOutput();
private:
    int id;
    bool isShown;
    string message;
    vector<string> replies;
};

#endif
