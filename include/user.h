#ifndef _USER
#define _USER

#include <unordered_map>

#include "common.h"

using std::unordered_map;

// 用户类
class User {
private:
    int ID;
    time_t registerTime;
    string phoneNumber;
    string passWord;
    string nickName;

    string personalDescription;

    int postAmount;
    vector<int> postID;

    int followingPeopleAmount;
    vector<int> followingPeopleID;

    int followerAmount;
    vector<int> followerID;

    void clear();

public:
    User();
    User(const int &_ID, const time_t &_registerTime, const string &_phoneNumber, const string &_passWord, const string &_nickName);

    void initUser(Json::Value &_user);
    Json::Value* getUserJson();

    string getPassword();
    string getNickName();

    void displayPostAmount(bool viewpoint);
    void displayPost();
    void displayFollowingAmount(bool viewpoint);
    void displayFollowing();
    void displayFollowerAmount(bool viewpoint);
    void displayFollower();

    bool isFollowing(int targetUserID);
    bool isFollower(int targetUserID);
    void followUser(int targetUserID);
    void unfollowUser(int targetUserID);

    void display(int mode);
    void launchPost();
    void launchComment(int curPostID);
    void launchSubComment(int curCommentID);
};

void initUsers();
void overwriteUsers();

namespace USER {
extern int userAmount;
extern User user[];
extern unordered_map<string, int> phoneNumberToID;
} // namespace USER

#endif