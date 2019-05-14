#include "Comment.h"

Comment::Comment(string _message, int _id)
    : message(_message), id(_id), isShown(true) {
}

void Comment::reply(string message) {
    replies.push_back(message);
}

void Comment::stopShowing() {
    if (!isShown)
        throw BadRequestError();
    isShown = false;
}

vector<string> Comment::getOutput() {
    vector<string> output;
    if (!isShown)
        return output;
    output.push_back(message);
    for (string reply : replies)
        output.push_back(reply);
    return output;
}
