#include "Comment.h"

Comment::Comment(string _message, int _id)
    : message(_message), id(_id), shown(true) {
}

void Comment::reply(Map &parameters) {
	checkMustHave({"comment_id", "film_id", "content"}, parameters);
	checkMayHave({"comment_id", "film_id", "content"}, parameters);
    replies.push_back(parameters["content"]);
}

void Comment::hide(Map &parameters) {
    if (!shown)
        throw BadRequestError();
    shown = false;
}

vector<string> Comment::getOutput() {
    vector<string> output;
    output.push_back(message);
    for (string reply : replies)
        output.push_back(reply);
    return output;
}

bool Comment::isShown() {
	return shown;
}
