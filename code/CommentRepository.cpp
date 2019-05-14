#include "CommentRepository.h"

CommentRepository::CommentRepository() {
    comments.push_back(NULL);
}

void CommentRepository::addComment(string message) {
    comments.push_back(new Comment(message, comments.size()));
}

Comment* CommentRepository::getCommentWithId(int id) {
    if (id < 0 || id >= comments.size())
        throw BadRequestError();
    return comments[id];
}

void CommentRepository::outputAllComments() {
    vector<string> output;
    output.push_back("Comments");
    for (int id = 1; id < comments.size(); id++) {
        Comment* comment = getCommentWithId(id);
        vector<string> commentOutput = comment->getOutput();
        int lineNumber = 0;
        for (string message : commentOutput) {
            string line = intToString(id) + ".";
            if (lineNumber > 0)
                line += intToString(lineNumber) + ".";
            line += " " + message;
            output.push_back(line);
			lineNumber ++;
        }
    }
    print(output);
}
