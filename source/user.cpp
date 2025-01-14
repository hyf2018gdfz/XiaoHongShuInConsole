#include "user.h"

#include <fstream>

#include "post.h"
#include "comment.h"
#include "color.h"

namespace USER {
int userAmount;
User user[N];
unordered_map<string, int> phoneNumberToID;
const string userDatabase = "users.json";
} // namespace USER
using namespace USER;

/// @brief 清空
void User::clear() {
    ID = 0;
    registerTime = 0;

    phoneNumber = "";
    passWord = "";
    nickName = "";

    personalDescription = "";

    postAmount = 0;
    postID.clear();

    followingPeopleAmount = 0;
    followingPeopleID.clear();

    followerAmount = 0;
    followerID.clear();
}

/// @brief 创建一个临时用户
User::User() {
    clear();
}

/// @brief 创建一个新用户
User::User(const int &_ID, const time_t &_registerTime, const string &_phoneNumber, const string &_passWord, const string &_nickName) {
    clear();

    ID = _ID;
    registerTime = _registerTime;

    phoneNumber = _phoneNumber;
    passWord = _passWord;
    nickName = _nickName;

    personalDescription = "This lazy guy hasn't written anything.";
}

/// @brief 基于数据库初始化一个用户
/// @param _user 数据库格式的用户数据
void User::initUser(Json::Value &_user) {
    clear();

    assert(_user.isMember("ID") && _user.isMember("registerTime"));
    this->ID = _user["ID"].asInt();
    this->registerTime = _user["registerTime"].asInt64();

    assert(_user.isMember("phoneNumber") && _user.isMember("passWord") && _user.isMember("nickName"));
    this->phoneNumber = _user["phoneNumber"].asString();
    this->passWord = _user["passWord"].asString();
    this->nickName = _user["nickName"].asString();

    assert(_user.isMember("personalDescription"));
    this->personalDescription = _user["personalDescription"].asString();

    assert(_user.isMember("postAmount") && _user.isMember("postID"));
    this->postAmount = _user["postAmount"].asInt();
    for (int j = 0; j < this->postAmount; ++j) {
        this->postID.push_back(_user["postID"][j].asInt());
    }

    assert(_user.isMember("followingPeopleAmount") && _user.isMember("followingPeopleID"));
    this->followingPeopleAmount = _user["followingPeopleAmount"].asInt();
    for (int j = 0; j < this->followingPeopleAmount; ++j) {
        this->followingPeopleID.push_back(_user["followingPeopleID"][j].asInt());
    }

    assert(_user.isMember("followerAmount") && _user.isMember("followerID"));
    this->followerAmount = _user["followerAmount"].asInt();
    for (int j = 0; j < this->followerAmount; ++j) {
        this->followerID.push_back(_user["followerID"][j].asInt());
    }

    phoneNumberToID[phoneNumber] = ID;
}

/// @brief 从数据库中读取所有用户的数据
void initUsers() {
    ifstream in_file(userDatabase, std::ios::in);
    if (!in_file) {
        cerr << "no such file " << userDatabase << endl;
        exit(-1);
    }

    Json::CharReaderBuilder readerBuilder;
    readerBuilder["emitUTF8"] = true;

    Json::Value root;

    string str;
    if (!Json::parseFromStream(readerBuilder, in_file, &root, &str)) {
        cerr << "parse error" << endl;
        exit(-1);
    }

    assert(root.isMember("users"));
    Json::Value users = root["users"];
    userAmount = users.size();

    for (int i = 1; i <= userAmount; ++i) {
        user[i].initUser(users[i - 1]);
    }
    in_file.close();
}

/// @brief 获取本用户的数据库格式的数据
/// @return 一个指向用户数据的指针
Json::Value *User::getUserJson() {
    Json::Value *userJson = new Json::Value();
    (*userJson)["ID"] = Json::Value(this->ID);
    (*userJson)["registerTime"] = Json::Value(this->registerTime);
    (*userJson)["phoneNumber"] = Json::Value(this->phoneNumber);
    (*userJson)["passWord"] = Json::Value(this->passWord);
    (*userJson)["nickName"] = Json::Value(this->nickName);
    (*userJson)["personalDescription"] = Json::Value(this->personalDescription);

    (*userJson)["postAmount"] = Json::Value(this->postAmount);
    (*userJson)["postID"] = Json::arrayValue;
    for (int j = 0; j < this->postAmount; ++j) {
        (*userJson)["postID"].append(this->postID[j]);
    }

    (*userJson)["followingPeopleAmount"] = Json::Value(this->followingPeopleAmount);
    (*userJson)["followingPeopleID"] = Json::arrayValue;
    for (int j = 0; j < this->followingPeopleAmount; ++j) {
        (*userJson)["followingPeopleID"].append(this->followingPeopleID[j]);
    }

    (*userJson)["followerAmount"] = Json::Value(this->followerAmount);
    (*userJson)["followerID"] = Json::arrayValue;
    for (int j = 0; j < this->followerAmount; ++j) {
        (*userJson)["followerID"].append(this->followerID[j]);
    }
    return userJson;
}

/// @brief 向数据库中写入所有用户的数据
void overwriteUsers() {
    ofstream out_file(userDatabase, std::ios::out);
    if (!out_file.is_open()) {
        cerr << "cannot open " << userDatabase << endl;
        exit(-1);
    }

    Json::StreamWriterBuilder writerBuilder;
    writerBuilder["emitUTF8"] = true;

    Json::Value root, tmpuser;
    root["users"] = Json::arrayValue;
    for (int i = 1; i <= userAmount; ++i) {
        auto tmpptr = user[i].getUserJson();
        root["users"].append(*tmpptr);
        delete tmpptr;
    }
    out_file << Json::writeString(writerBuilder, root);
    out_file.close();
}

/// @brief 根据选择的模式展示本用户的数据
/// @param mode 模式选择，0为旁观视角，1为自己视角，2为上帝视角
void User::display(int mode = 0) {
    assert(mode >= 0 && mode <= 2);
    // 基本信息
    outputTitle("User Profile---");

    outputFormat("User's nickname: ", this->nickName);
    outputFormat("User's personal description: ", this->personalDescription);
    if (mode >= 1) {
        outputFormat("User's phone number: ", this->phoneNumber);
        outputFormat("User's register time: ", this->registerTime);
    }
    if (mode == 2) {
        outputFormat("User's password: ", this->passWord);
    }
    outputTitle("---");

    // 帖子信息
    displayPostAmount(mode >= 1);
    displayPost();
    outputTitle("---");

    // 关注信息
    displayFollowingAmount(mode >= 1);
    displayFollowing();
    displayFollowerAmount(mode >= 1);
    displayFollower();

    outputTitle("User Profile End---");
}

/// @brief 让本用户发布一则新帖子
void User::launchPost() {
    POST::post[++POST::postAmount].initPostConsole(this->ID);
    this->postAmount++;
    this->postID.push_back(POST::postAmount);

    overwriteUsers();
    overwritePosts();
}

/// @brief 让本用户在当前帖子下发布一则评论
/// @param curPostID 当前帖子的ID
void User::launchComment(int curPostID) {
    POST::post[curPostID].addComment(this->ID);
    overwritePosts();
    overwriteComments();
}

/// @brief 判断本用户是否关注了目标用户
/// @param targetUserID 目标用户的ID
/// @return 返回是或否
bool User::isFollowing(int targetUserID) {
    for (auto followingID : this->followingPeopleID) {
        if (followingID == targetUserID) return true;
    }
    return false;
}

/// @brief 判断目标用户是否是本用户的粉丝
/// @param targetUserID 目标用户的ID
/// @return 返回是或否
bool User::isFollower(int targetUserID) {
    return user[targetUserID].isFollowing(this->ID);
}

/// @brief 让本用户关注目标用户
/// @param targetUserID 目标用户的ID
void User::followUser(int targetUserID) {
    this->followingPeopleID.push_back(targetUserID);
    this->followingPeopleAmount++;
    user[targetUserID].followerID.push_back(this->ID);
    user[targetUserID].followerAmount++;
    cout << "Follow successfully!" << endl;
    overwriteUsers();
}

/// @brief 让本用户取关目标用户
/// @param targetUserID 目标用户的ID
void User::unfollowUser(int targetUserID) {
    for (int i = 0; i < this->followingPeopleAmount; ++i) {
        if (this->followingPeopleID[i] == targetUserID) {
            this->followingPeopleID.erase(this->followingPeopleID.begin() + i);
            this->followingPeopleAmount--;
            break;
        }
    }
    for (int i = 0; i < user[targetUserID].followerAmount; ++i) {
        if (user[targetUserID].followerID[i] == this->ID) {
            user[targetUserID].followerID.erase(user[targetUserID].followerID.begin() + i);
            user[targetUserID].followerAmount--;
            break;
        }
    }
    cout << "Unfollow successfully!" << endl;
    overwriteUsers();
}

/// @brief 让本用户回复当前评论
/// @param curCommentID 当前评论的ID
void User::launchSubComment(int curCommentID) {
    COMMENT::comment[++COMMENT::commentAmount].initCommentConsole(this->ID);
    COMMENT::comment[curCommentID].addSubComment(COMMENT::commentAmount);
    overwriteComments();
}

/// @brief 获取本用户的昵称
string User::getNickName() {
    return this->nickName;
}

/// @warning TODO: 本函数并不安全，未来将使用哈希算法
/// @brief 获取本用户的密码
string User::getPassword() {
    return this->passWord;
}

/// @brief 展示本用户的帖子数
/// @param viewpoint 视角，true为自己视角，false为旁观视角
void User::displayPostAmount(bool viewpoint = false) {
    if (viewpoint) {
        cout << "I have posted " << outputHighlight(this->postAmount) << " posts." << endl;
    } else {
        cout << outputHighlight(this->nickName) << " has posted " << outputHighlight(this->postAmount) << " posts." << endl;
    }
}

// TODO: 如果待展示的内容行数很多，那么分批展示：按enter展示下面10行，按q结束展示

/// @brief 展示本用户的帖子
void User::displayPost() {
    for (int i = 0; i < this->postAmount; ++i) {
        cout << "## Post number " << outputHighlight(i + 1) << "." << endl;
        POST::post[this->postID[i]].display(1);
    }
}

/// @brief 展示本用户关注的人的人数
/// @param viewpoint 视角，true为自己视角，false为旁观视角
void User::displayFollowingAmount(bool viewpoint = false) {
    if (viewpoint) {
        cout << "I am following " << outputHighlight(this->followingPeopleAmount) << " people." << endl;
    } else {
        cout << outputHighlight(this->nickName) << " is following " << outputHighlight(this->followingPeopleAmount) << " people." << endl;
    }
}

/// @brief 展示本用户关注的人
void User::displayFollowing() {
    for (int i = 0; i < this->followingPeopleAmount; ++i) {
        cout << "Following " << outputHighlight(i + 1) << ": " << user[this->followingPeopleID[i]].nickName << endl;
    }
}

/// @brief 展示本用户的粉丝数
/// @param viewpoint 视角，true为自己视角，false为旁观视角
void User::displayFollowerAmount(bool viewpoint = false) {
    if (viewpoint) {
        cout << "I have " << outputHighlight(this->followerAmount) << " followers." << endl;
    } else {
        cout << outputHighlight(this->nickName) << " has " << outputHighlight(this->followerAmount) << " followers." << endl;
    }
}

/// @brief 展示本用户的粉丝
void User::displayFollower() {
    for (int i = 0; i < this->followerAmount; ++i) {
        cout << "Follower " << outputHighlight(i + 1) << ": " << user[this->followerID[i]].nickName << endl;
    }
}