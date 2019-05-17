#ifndef COMMENTREPOSITORY_H
#define COMMENTREPOSITORY_H

#include "utility.h"
#include "Comment.h"

class CommentRepository {
public:
    CommentRepository();
    void addComment(string message, int senderId);
    void outputAllComments();
    Comment* getCommentWithId(int id);
private:
    vector<Comment*> comments;
};

#endif
