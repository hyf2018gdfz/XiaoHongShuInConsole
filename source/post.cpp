#include "post.h"

#include <fstream>

#include "color.h"

#include "comment.h"
#include "user.h"

namespace POST {
int postAmount;
Post post[N];
const string postDatabase = "posts.json";
} // namespace POST
using namespace POST;

// TODO: like & dislike

/// @brief 清空
void Post::clear() {
    ID = 0;
    ownerID = 0;
    date = 0;

    title = content = "";

    likeAmount = 0;
    likeID.clear();
    dislikeAmount = 0;
    dislikeID.clear();

    commentAmount = 0;
    commentID.clear();
}

/// @brief 创建一个临时帖子
Post::Post() {
    clear();
}

/// @brief 创建一个新帖子
Post::Post(const int &_ID, const int &_ownerID, const time_t &_date, const string &_title, const string &_content) {
    clear();

    ID = _ID;
    ownerID = _ownerID;
    date = _date;

    title = _title;
    content = _content;
}

/// @brief 基于数据库初始化一个帖子
/// @param _post 数据库格式的帖子数据
void Post::initPost(Json::Value &_post) {
    assert(_post.isMember("ID") && _post.isMember("ownerID") && _post.isMember("date"));
    this->ID = _post["ID"].asInt();
    this->ownerID = _post["ownerID"].asInt();
    this->date = _post["date"].asInt64();

    assert(_post.isMember("title") && _post.isMember("content"));
    this->title = _post["title"].asString();
    this->content = _post["content"].asString();

    assert(_post.isMember("likeAmount") && _post.isMember("likeID"));
    this->likeAmount = _post["likeAmount"].asInt();
    for (int j = 0; j < this->likeAmount; ++j) {
        this->likeID.push_back(_post["likeID"][j].asInt());
    }
    // TODO: dislike

    assert(_post.isMember("commentAmount") && _post.isMember("commentID"));
    this->commentAmount = _post["commentAmount"].asInt();
    for (int j = 0; j < this->commentAmount; ++j) {
        this->commentID.push_back(_post["commentID"][j].asInt());
    }
}

/// @brief 从数据库中读取所有帖子的数据
void initPosts() {
    ifstream in_file(postDatabase, std::ios::in);
    if (!in_file) {
        cerr << "no such file " << postDatabase << endl;
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

    assert(root.isMember("posts"));
    Json::Value posts = root["posts"];
    postAmount = posts.size();
    for (int i = 1; i <= postAmount; ++i) {
        post[i].initPost(posts[i - 1]);
    }
    in_file.close();
}

/// @brief 获取本帖子的数据库格式的数据
/// @return 一个指向帖子数据的指针
Json::Value *Post::getPostJson() {
    Json::Value *postJson = new Json::Value();
    (*postJson)["ID"] = Json::Value(this->ID);
    (*postJson)["ownerID"] = Json::Value(this->ownerID);
    (*postJson)["date"] = Json::Value(this->date);
    (*postJson)["title"] = Json::Value(this->title);
    (*postJson)["content"] = Json::Value(this->content);
    (*postJson)["likeAmount"] = Json::Value(this->likeAmount);
    (*postJson)["likeID"] = Json::arrayValue;
    for (auto userID : this->likeID) (*postJson)["likeID"].append(userID);
    (*postJson)["commentAmount"] = Json::Value(this->commentAmount);
    (*postJson)["commentID"] = Json::arrayValue;
    for (auto commentID : this->commentID) (*postJson)["commentID"].append(commentID);
    return postJson;
}

/// @brief 向数据库中写入所有帖子的数据
void overwritePosts() {
    ofstream out_file(postDatabase, std::ios::out);
    if (!out_file.is_open()) {
        cerr << "cannot open " << postDatabase << endl;
        exit(-1);
    }

    Json::StreamWriterBuilder writerBuilder;
    writerBuilder["emitUTF8"] = true;

    Json::Value root;
    root["posts"] = Json::arrayValue;
    for (int i = 1; i <= postAmount; ++i) {
        auto tmpptr = post[i].getPostJson();
        root["posts"].append(*tmpptr);
        delete tmpptr;
    }
    std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
    writer->write(root, &out_file);
    out_file.close();
}

/// @brief 获取本帖子的所有者的ID
int Post::getOwnerID() {
    return this->ownerID;
}

/// @brief 根据选择的模式展示本帖子的数据
/// @param mode 模式选择，0为简略模式，1为详细模式（但不显示评论）
void Post::display(bool mode) {
    outputTitle(this->title);
    cout << outputHighlight(USER::user[this->ownerID].getNickName()) << ": ";
    if (mode) {
        cout << endl;
        cout << this->content << endl;
        cout << "Published on " << getTimeString(this->date) << endl;
    } else {
        if (this->content.length() >= 100) {
            cout << this->content.substr(0, 100) << "..." << endl;
        } else {
            cout << this->content << endl;
        }
    }
    displayInteractions();
}

/// @brief 展示赞同数、反对数、评论数
void Post::displayInteractions() {
    cout << Color::Modifier(Color::RESET, Color::BG_DEFAULT, Color::FG_LIGHT_GREEN)
         << this->likeAmount
         << Color::Modifier()
         << " likes, "
         << Color::Modifier(Color::RESET, Color::BG_DEFAULT, Color::FG_LIGHT_RED)
         << this->dislikeAmount
         << Color::Modifier()
         << " dislikes, "
         << outputHighlight(this->commentAmount)
         << " comments." << endl;
}

/// @brief 输出评论内容
void Post::displayComment() {
    for (auto commentID : this->commentID) {
        displayAllComments(COMMENT::comment[commentID], 1);
    }
}

/// @brief 基于控制台的输入对帖子内容进行初始化
/// @param ownerID 帖子的所有者
void Post::initPostConsole(int ownerID) {
    clear();
    cout << "Please input your post's title." << endl;
    getline(cin, this->title);
    cout << "Please input your post's content." << endl;
    getline(cin, this->content);
    cout << "Your Post has been launched successfully!" << endl;
    this->ownerID = ownerID;
    this->date = getTime();
}

/// @brief 喜欢本帖子
/// @param likeID 点击喜欢的用户的ID
void Post::likeThisPost(int likeID) {
    this->likeAmount++;
    this->likeID.push_back(likeID);
}

/// @brief 撤销喜欢本帖子
/// @param likeID 点击撤销的用户的ID
void Post::undoLike(int likeID) {
    for (int i = 0; i < this->likeAmount; ++i) {
        if (this->likeID[i] == likeID) {
            this->likeID.erase(this->likeID.begin() + i);
            this->likeAmount--;
            break;
        }
    }
}

/// @brief 不喜欢本帖子
/// @param dislikeID 点击不喜欢的用户的ID
void Post::dislikeThisPost(int dislikeID) {
    this->dislikeAmount++;
    this->dislikeID.push_back(dislikeID);
}

/// @brief 撤销不喜欢本帖子
/// @param dislikeID 点击撤销的用户的ID
void Post::undoDislike(int dislikeID) {
    for (int i = 0; i < this->dislikeAmount; ++i) {
        if (this->dislikeID[i] == dislikeID) {
            this->dislikeID.erase(this->dislikeID.begin() + i);
            this->dislikeAmount--;
            break;
        }
    }
}

/// @brief 在本帖子下新增一条评论
/// @param userID 发表评论的用户的ID
void Post::addComment(int userID) {
    COMMENT::comment[++COMMENT::commentAmount].initCommentConsole(userID);
    this->commentAmount++;
    this->commentID.push_back(COMMENT::commentAmount);
}
