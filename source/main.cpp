#include <bits/stdc++.h>
#include <windows.h>
#include "common.h"
#include "login.h"
#include "register.h"
#include "bugreport.h"
#include "user.h"
#include "post.h"
#include "comment.h"
#include "scene.h"
#include "json.h"
using namespace std;

void init() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand(time(0));
    initUsers();
    initPosts();
    initComments();
}

int currentUser = 1; // 当前登录的用户

/*
在每个界面里，都遵循如下的顺序：
1. 输出界面信息以及交互指南
2. 输入交互指令，然后按照交互指令跳转到其他的界面

界面的排布逻辑如下：
1. 小红书的欢迎界面
    1.1 登录
    1.2 注册
2. 我的欢迎界面
    2.0 登出
    2.1 “某人”的主页
        2.1.-1 回到我的欢迎界面
        2.1.0 返回上一界面，即“某人”的主页（后文略去-1和0这两个选项）
        2.1.1 查看“某人”的所有帖子（粗略展示）
            2.1.1.1 选择并查看“某人”的某个帖子（详细展示）
                2.1.1.1.1 评论该帖子
                2.1.1.1.2 回复该帖子下的某条评论（暂未实现）
                2.1.1.1.3 查看“某人”的个人主页（见2.1）
                2.1.1.1.？ 赞同、反对帖子；赞同、反对评论、回复；删帖，要求“某人”==我（暂未实现）
            2.1.1.2 发布帖子，要求“某人”==我
        2.1.2 查看“某人”的关注列表
            2.1.2.1 选择并查看“某人”的关注列表中的某个人的主页（见2.1）
        2.1.3 查看“某人”的粉丝列表
            2.1.3.1 选择并查看“某人”的粉丝列表中的某个人的主页（见2.1）
        2.1.4 关注或取关“某人”，要求“某人”!=我
    2.2 帖子广场（粗略展示帖子）
        2.2.1 选择并查看某个帖子（详细展示，见2.1.1.1）
        2.2.2 发布帖子，要求“某人”==我（见2.1.1.2）

在每个界面里，都会有一个backToMainPage的bool变量，当其为false时，表示需要返回到上一级界面。
TODO：排序等功能
*/
int main() {
    init();

    cout << "Welcome to Little Red Book!" << endl;
    cout << "Enter 1 to login." << endl;
    cout << "Enter 2 to register." << endl;
    int cmd = readInt(1, 2);
    if (cmd == 1) {
        if (loginAccount() != Bug::Succeed) return 0;
    } else if (cmd == 2) {
        registerAccount();
    }
    // 无论是登录还是注册，都会在成功后将currentUser赋值为当前用户的编号
    clearScreen();

    cout << "Welcome, " << USER::user[currentUser].getNickName() << "!" << endl;

    viewMainPage();
    int a;
    cin >> a;
    return 0;
}