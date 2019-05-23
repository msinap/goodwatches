#include "Comment.h"

Comment::Comment(string _message, int _id, int _senderId)
    : message(_message), id(_id), shown(true), senderId(_senderId) {
}

void Comment::reply(Map &parameters) {
	checkMustHave({"comment_id", "film_id", "content"}, parameters);
	checkMayHave({"comment_id", "film_id", "content"}, parameters);
	if (!shown)
		throw NotFoundError();
    replies.push_back(parameters["content"]);
}

void Comment::hide(Map &parameters) {
    if (!shown)
        throw PermissionDeniedError();
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

int Comment::getSenderId() {
	return senderId;
}
