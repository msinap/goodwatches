#include "Comment.h"

Comment::Comment(string _message, int _id)
    : message(_message), id(_id), isShown(true) {
}

void Comment::reply(Map &parameters) {
	checkMustHave({"comment_id", "film_id", "content"}, parameters);
	checkMayHave({"comment_id", "film_id", "content"}, parameters);
    replies.push_back(parameters["content"]);
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
