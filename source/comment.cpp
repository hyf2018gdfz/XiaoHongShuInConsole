#include "comment.h"

#include <fstream>

#include "user.h"
#include "color.h"

namespace COMMENT {
int commentAmount;
Comment comment[N];
const string commentDatabase = "comments.json";
} // namespace COMMENT
using namespace COMMENT;

/// @brief 清空
void Comment::clear() {
    ID = 0;
    ownerID = 0;
    date = 0;

    content = "";

    likeAmount = 0;
    likeID.clear();
    dislikeAmount = 0;
    dislikeID.clear();

    subCommentAmount = 0;
    subCommentID.clear();
}

/// @brief 创建一个临时帖子
Comment::Comment() {
    clear();
}

/// @brief 创建一个新帖子
Comment::Comment(const int &_ID, const int &_ownerID, const time_t &_date, const string &_content) {
    clear();

    ID = _ID;
    ownerID = _ownerID;
    date = _date;

    content = _content;
}

/// @brief 基于数据库初始化一个评论
/// @param _post 数据库格式的评论数据
void Comment::initComment(Json::Value &_comment) {
    assert(_comment.isMember("ID") && _comment.isMember("ownerID") && _comment.isMember("date"));
    this->ID = _comment["ID"].asInt();
    this->ownerID = _comment["ownerID"].asInt();
    this->date = _comment["date"].asInt64();

    assert(_comment.isMember("content"));
    this->content = _comment["content"].asString();

    assert(_comment.isMember("likeAmount") && _comment.isMember("likeID"));
    this->likeAmount = _comment["likeAmount"].asInt();
    for (int j = 0; j < this->likeAmount; ++j) {
        this->likeID.push_back(_comment["likeID"][j].asInt());
    }

    assert(_comment.isMember("dislikeAmount") && _comment.isMember("dislikeID"));
    this->dislikeAmount = _comment["dislikeAmount"].asInt();
    for (int j = 0; j < this->dislikeAmount; ++j) {
        this->dislikeID.push_back(_comment["dislikeID"][j].asInt());
    }

    assert(_comment.isMember("subCommentAmount") && _comment.isMember("subCommentID"));
    this->subCommentAmount = _comment["subCommentAmount"].asInt();
    for (int j = 0; j < this->subCommentAmount; ++j) {
        this->subCommentID.push_back(_comment["subCommentID"][j].asInt());
    }
}

/// @brief 从数据库中读取所有评论的数据
void initComments() {
    ifstream in_file(commentDatabase, std::ios::in);
    if (!in_file) {
        std::cerr << "no such file " << commentDatabase << endl;
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

    assert(root.isMember("comments"));
    Json::Value comments = root["comments"];
    commentAmount = comments.size();

    for (int i = 1; i <= commentAmount; ++i) {
        comment[i].initComment(comments[i - 1]);
    }
    in_file.close();
}

/// @brief 获取本评论的数据库格式的数据
/// @return 一个指向评论数据的指针
Json::Value *Comment::getCommentJson() {
    Json::Value *commentJson = new Json::Value();
    (*commentJson)["ID"] = Json::Value(this->ID);
    (*commentJson)["ownerID"] = Json::Value(this->ownerID);
    (*commentJson)["date"] = Json::Value(this->date);

    (*commentJson)["content"] = Json::Value(this->content);

    (*commentJson)["likeAmount"] = Json::Value(this->likeAmount);
    (*commentJson)["likeID"] = Json::arrayValue;
    for (auto userID : this->likeID) {
        (*commentJson)["likeID"].append(userID);
    }
    (*commentJson)["dislikeAmount"] = Json::Value(this->dislikeAmount);
    (*commentJson)["dislikeID"] = Json::arrayValue;
    for (auto userID : this->dislikeID) {
        (*commentJson)["dislikeID"].append(userID);
    }

    (*commentJson)["subCommentAmount"] = Json::Value(this->subCommentAmount);
    (*commentJson)["subComment"] = Json::arrayValue;
    for (auto commentID : this->subCommentID) {
        (*commentJson)["subCommentID"].append(commentID);
    }
    return commentJson;
}

/// @brief 向数据库中写入所有评论的数据
void overwriteComments() {
    ofstream out_file(commentDatabase, std::ios::out);
    if (!out_file.is_open()) {
        cerr << "cannot open " << commentDatabase << endl;
        exit(-1);
    }

    Json::StreamWriterBuilder writerBuilder;
    writerBuilder["emitUTF8"] = true;

    Json::Value root;
    root["comments"] = Json::arrayValue;
    for (int i = 1; i <= commentAmount; ++i) {
        auto tmpptr = comment[i].getCommentJson();
        root["comments"].append(*tmpptr);
        delete tmpptr;
    }
    std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
    writer->write(root, &out_file);
    out_file.close();
}

/// @brief 获取本评论的用户的ID
int Comment::getOwnerID() {
    return this->ownerID;
}

/// @brief 按缩进层级展示评论
/// @param dep 缩进层级
void Comment::displayComment(int dep) {
    static const string prefix = "    ";
    auto proceedIndent = [dep]() {for (int i = 1; i <= dep; ++i) cout << prefix; };
    proceedIndent();
    outputFormat("Date: ", getTimeString(this->date));
    proceedIndent();
    outputFormat("Owner: ", USER::user[this->ownerID].getNickName());
    proceedIndent();
    outputFormat("Content: ", this->content);
}

/// @brief 获取本评论的子评论的ID
vector<int> &Comment::getSubCommentID() {
    return this->subCommentID;
}

/// @brief 用深度优先搜索展示所有的评论
/// @param curComment 当前评论
/// @param dep 缩进层数
void displayAllComments(Comment &curComment, int dep) {
    curComment.displayComment(dep);

    for (auto commentID : curComment.getSubCommentID()) {
        displayAllComments(comment[commentID], dep + 1);
    }
}

/// @brief 对本评论添加新的子评论
/// @param userID 子评论发布者的ID
void Comment::addSubComment(int userID) {
    comment[++commentAmount].initCommentConsole(userID);
    this->subCommentAmount++;
    this->subCommentID.push_back(commentAmount);
}

/// @brief 基于控制台的输入对评论内容进行初始化
/// @param ownerID 评论的所有者
void Comment::initCommentConsole(int ownerID) {
    clear();
    cout << "Please input your comment's content." << endl;
    getline(cin, this->content);
    cout << "Your comment has been launched successfully!" << endl;
    this->ownerID = ownerID;
    this->date = getTime();
}
