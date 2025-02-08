#ifndef _COMMENT_H
#define _COMMENT_H

#include "common.h"

class Comment {
private:
    int ID;
    int ownerID;
    time_t date;

    string content;

    int likeAmount;
    vector<int> likeID;
    int dislikeAmount;
    vector<int> dislikeID;

    int subCommentAmount;
    vector<int> subCommentID;

    void clear();

public:
    Comment();
    Comment(const int &_ID, const int &_ownerID, const time_t &_date, const string &_content);

    void initComment(Json::Value &_comment);
    Json::Value *getCommentJson();

    int getOwnerID();
    vector<int> &getSubCommentID();

    void initCommentConsole(int ownerID);
    void addSubComment(int userID);

    // void likeThisComment(int likeID);
    // void undoLike(int likeID);
    // void dislikeThisComment(int dislikeID);
    // void undoDislike(int dislikeID);

    void displayComment(int dep);
};

void initComments();
void overwriteComments();

void displayAllComments(Comment &curComment, int dep);

namespace COMMENT {
extern int commentAmount;
extern Comment comment[];
} // namespace COMMENT

#endif