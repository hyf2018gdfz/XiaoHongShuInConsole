#ifndef _POST
#define _POST

#include "common.h"

class Post {
private:
    int ID;
    int ownerID;
    time_t date;

    string title;
    string content;

    int likeAmount;
    vector<int> likeID;
    int dislikeAmount;
    vector<int> dislikeID;

    int commentAmount;
    vector<int> commentID;

    void clear();

public:
    Post();
    Post(const int &_ID, const int &_ownerID, const time_t &_date, const string &_title, const string &_content);
    
    void initPost(Json::Value &_post);
    Json::Value *getPostJson();

    void initPostConsole(int ownerID);
    //TODO: void editPostConsole(int ownerID);
    void addComment(int userID);

    int getOwnerID();

    void likeThisPost(int likeID);
    void undoLike(int likeID);
    void dislikeThisPost(int dislikeID);
    void undoDislike(int dislikeID);

    void displayPost(int mode);
};

void initPosts();
void overwritePosts();

namespace POST {
extern int postAmount;
extern Post post[];
} // namespace POST

#endif