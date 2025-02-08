#include "scene.h"

#include "user.h"
#include "post.h"
#include "comment.h"
#include "color.h"

extern int currentUser;

bool backToMainPage;

// void viewPostDetail(int viewingUser, int viewingPost) { // 详细查看一个帖子的内容
//     while (backToMainPage) {
//         clearScreen();
//         displayPost(POST::post[viewingPost], true);
//         cout << "MENU---" << endl;
//         cout << "Enter 1 to comment this post." << endl;
//         cout << "Enter 2 to reply a comment." << endl;
//         cout << "Enter 3 to open the post owner's profile." << endl;
//         cout << "Enter 0 to return." << endl;
//         cout << "Enter -1 to return to the main page." << endl;
//         cout << "---" << endl;
//         int cmd = readInt(-1, 3);
//         if (cmd == -1) {
//             backToMainPage = false;
//             return;
//         }
//         if (cmd == 0) return;
//         if (cmd == 1) {
//             launchComment(USER::user[currentUser], POST::post[viewingPost]);
//         } else if (cmd == 2) {
//         } else if (cmd == 3) {
//             viewUserProfile(viewingUser);
//         }
//     }
// }

// void viewPostBrief(int viewingUser) { // 简略展示某人的所有帖子
//     while (backToMainPage) {
//         // 输出界面信息以及交互指南
//         clearScreen();
//         if (viewingUser == currentUser) {
//             cout << "I have posted " << USER::user[currentUser].postAmount << " posts." << endl;
//             for (int i = 0; i < USER::user[currentUser].postAmount; ++i) {
//                 cout << "## Post number " << i + 1 << "." << endl;
//                 displayPost(POST::post[USER::user[currentUser].postID[i]], false);
//             }
//             if (USER::user[currentUser].postAmount == 0) {
//                 cout << "MENU---" << endl;
//                 cout << "Enter 1 to launch a post." << endl;
//                 cout << "Enter 0 to return." << endl;
//                 cout << "Enter -1 to return to the main page." << endl;
//                 cout << "---" << endl;

//                 // 用户（我）没有帖子，可以选择发帖或返回
//                 int cmd = readInt(-1, 1);
//                 if (cmd == -1) {
//                     backToMainPage = false;
//                     return;
//                 }
//                 if (cmd == 0)
//                     return;
//                 else if (cmd == 1) {
//                     launchPost(USER::user[currentUser]);
//                 }
//             } else {
//                 cout << "MENU---" << endl;
//                 cout << "Enter 1 to select a post you want to take a closer look at." << endl;
//                 cout << "Enter 2 to launch a post." << endl;
//                 cout << "Enter 0 to return." << endl;
//                 cout << "Enter -1 to return to the main page." << endl;
//                 cout << "---" << endl;

//                 // 用户（我）有帖子，可以选择详细查看某个帖子、发帖以及返回
//                 int cmd = readInt(-1, 2);
//                 if (cmd == -1) {
//                     backToMainPage = false;
//                     return;
//                 }
//                 if (cmd == 0)
//                     return;
//                 else if (cmd == 1) {
//                     cout << "Please enter the post number you want to view." << endl;
//                     int postNumber = readInt(1, USER::user[currentUser].postAmount) - 1;
//                     viewPostDetail(currentUser, USER::user[currentUser].postID[postNumber]);
//                 } else if (cmd == 2) {
//                     launchPost(USER::user[currentUser]);
//                 }
//             }
//         } else {
//             cout << USER::user[viewingUser].nickName << " has posted " << USER::user[viewingUser].postAmount << " posts." << endl;
//             if (USER::user[viewingUser].postAmount == 0) { // 没有帖子，只能返回
//                 return doingNone();
//             }
//             for (int i = 0; i < USER::user[viewingUser].postAmount; ++i) {
//                 cout << "## Post number " << i + 1 << "." << endl;
//                 displayPost(POST::post[USER::user[viewingUser].postID[i]], false);
//             }
//             cout << "MENU---" << endl;
//             cout << "Do you want to view " << USER::user[viewingUser].nickName << "'s posts in detail?" << endl;
//             cout << "Enter 1 to choose a post to view in detail" << endl;
//             cout << "Enter 0 to return." << endl;
//             cout << "Enter -1 to return to the main page." << endl;
//             cout << "---" << endl;

//             // 粗略查看别人的帖子，可以选择是否详细查看某个帖子以及返回
//             int cmd = readInt(-1, 1);
//             if (cmd == -1) {
//                 backToMainPage = false;
//                 return;
//             }
//             if (cmd == 0)
//                 return;
//             else if (cmd == 1) {
//                 cout << "Please enter the post number you want to view." << endl;
//                 int postNumber = readInt(1, USER::user[viewingUser].postAmount) - 1;
//                 viewPostDetail(viewingUser, USER::user[viewingUser].postID[postNumber]);
//             }
//         }
//     }
// }

// void viewFollowingPeople(int viewingUser) { // 查看某人的关注列表
//     while (backToMainPage) {
//         // 输出界面信息以及交互指南
//         clearScreen();
//         if (viewingUser == currentUser) {
//             cout << "I am following " << USER::user[currentUser].followingPeopleAmount << " people." << endl;
//         } else {
//             cout << USER::user[viewingUser].nickName << " is following " << USER::user[viewingUser].followingPeopleAmount << " people." << endl;
//         }
//         if (USER::user[viewingUser].followingPeopleAmount == 0) { // 没有关注的人，只能返回
//             return doingNone();
//         }
//         for (int i = 0; i < USER::user[viewingUser].followingPeopleAmount; ++i) {
//             cout << "Following " << i + 1 << ": " << USER::user[USER::user[viewingUser].followingPeopleID[i]].nickName << endl;
//         }
//         cout << "MENU---" << endl;
//         cout << "Enter 1 to view the profile of the following people." << endl;
//         cout << "Enter 0 to return." << endl;
//         cout << "Enter -1 to return to the main page." << endl;
//         cout << "---" << endl;

//         // 输入交互指令，然后按照交互指令跳转到关注的用户的界面
//         int cmd = readInt(-1, 1);
//         if (cmd == -1) {
//             backToMainPage = false;
//             return;
//         }
//         if (cmd == 0)
//             return;
//         else if (cmd == 1) {
//             cout << "Please enter the number of the following people you want to view." << endl;
//             int followingNumber = readInt(1, USER::user[viewingUser].followingPeopleAmount) - 1;
//             viewUserProfile(USER::user[viewingUser].followingPeopleID[followingNumber]);
//         }
//     }
// }

// void viewFollowers(int viewingUser) { // 查看某人的粉丝列表
//     while (backToMainPage) {
//         // 输出界面信息以及交互指南
//         clearScreen();
//         if (viewingUser == currentUser) {
//             cout << "I have " << USER::user[currentUser].followerAmount << " followers." << endl;
//         } else {
//             cout << USER::user[viewingUser].nickName << " has " << USER::user[viewingUser].followerAmount << " followers." << endl;
//         }
//         if (USER::user[viewingUser].followerAmount == 0) { // 没有粉丝，只能返回
//             return doingNone();
//         }
//         for (int i = 0; i < USER::user[viewingUser].followerAmount; ++i) {
//             cout << "Follower " << i + 1 << ": " << USER::user[USER::user[viewingUser].followerID[i]].nickName << endl;
//         }
//         cout << "MENU---" << endl;
//         cout << "Enter 1 to view the profile of a follower." << endl;
//         cout << "Enter 0 to return." << endl;
//         cout << "Enter -1 to return to the main page." << endl;
//         cout << "---" << endl;

//         // 输入交互指令，然后按照交互指令跳转到粉丝的界面
//         int cmd = readInt(-1, 1);
//         if (cmd == -1) {
//             backToMainPage = false;
//             return;
//         }
//         if (cmd == 0)
//             return;
//         else if (cmd == 1) {
//             cout << "Please enter the number of the follower you want to view." << endl;
//             int followerNumber = readInt(1, USER::user[viewingUser].followerAmount) - 1;
//             viewUserProfile(USER::user[viewingUser].followerID[followerNumber]);
//         }
//     }
// }

// void viewUserProfile(int viewingUser) { // 查看某人的主页
//     while (backToMainPage) {
//         // 输出界面信息以及交互指南
//         clearScreen();
//         USER::user[viewingUser].displayUser(0);
//         cout << "MENU---" << endl;
//         if (viewingUser == currentUser) {
//             cout << "Enter 1 to view all posts by me." << endl;
//             cout << "Enter 2 to view users I am following." << endl;
//             cout << "Enter 3 to view my followers." << endl;
//             cout << "Enter 0 to return." << endl;
//             cout << "Enter -1 to return to the main page." << endl;
//             cout << "---" << endl;

//             // 输入交互指令，然后按照交互指令跳转到其他的界面
//             int cmd = readInt(-1, 3);
//             if (cmd == -1) {
//                 backToMainPage = false;
//                 return;
//             }
//             if (cmd == 0)
//                 return;
//             else if (cmd == 1) {
//                 viewPostBrief(currentUser);
//             } else if (cmd == 2) {
//                 viewFollowingPeople(currentUser);
//             } else if (cmd == 3) {
//                 viewFollowers(currentUser);
//             }
//         } else {
//             cout << "Enter 1 to view all posts by " << USER::user[viewingUser].getNickName() << "." << endl;
//             cout << "Enter 2 to view users " << USER::user[viewingUser].getNickName() << " is following." << endl;
//             cout << "Enter 3 to view " << USER::user[viewingUser].getNickName() << "'s followers." << endl;
//             bool isFollowingViewingUser = USER::user[currentUser].isFollowing(viewingUser);
//             if (isFollowingViewingUser == false) {
//                 cout << "Enter 4 to follow " << USER::user[viewingUser].getNickName() << "." << endl;
//             } else {
//                 cout << "Enter 4 to unfollow " << USER::user[viewingUser].getNickName() << "." << endl;
//             }
//             cout << "Enter 0 to return." << endl;
//             cout << "Enter -1 to return to the main page." << endl;
//             cout << "---" << endl;

//             // 输入交互指令，然后按照交互指令跳转到其他的界面
//             int cmd = readInt(-1, 4);
//             if (cmd == -1) {
//                 backToMainPage = false;
//                 return;
//             }
//             if (cmd == 0) return;
//             if (cmd == 1) {
//                 viewPostBrief(viewingUser);
//             } else if (cmd == 2) {
//                 viewFollowingPeople(viewingUser);
//             } else if (cmd == 3) {
//                 viewFollowers(viewingUser);
//             } else if (cmd == 4) {
//                 if (isFollowingViewingUser == false) {
//                     USER::user[currentUser].followUser(viewingUser);
//                 } else {
//                     USER::user[currentUser].unfollowUser(viewingUser);
//                 }
//             }
//         }
//     }
// }

void viewPostSquare() // 查看帖子广场
{
    while (backToMainPage) {
        // 输出界面信息以及交互指南
        clearScreen();
        cout << "Welcome to the Post Square!" << endl;
        cout << "There are " << POST::postAmount << " posts in total." << endl;
        for (int i = 1; i <= POST::postAmount; ++i) {
            cout << "## Post number " << i << "." << endl;
            POST::post[i].display(false);
        }
        cout << "MENU---" << endl;
        cout << "Enter 1 to view a post in detail." << endl;
        cout << "Enter 2 to launch a post." << endl;
        cout << "Enter 0 to return." << endl;
        cout << "Enter -1 to return to the main page." << endl;
        cout << "---" << endl;

        // 输入交互指令，然后按照交互指令跳转到其他的界面
        int cmd = readInt(-1, 2);
        if (cmd == -1) {
            backToMainPage = false;
            return;
        }
        if (cmd == 0)
            return;
        else if (cmd == 1) {
            if (POST::postAmount == 0) {
                cout << "There is no post to view." << endl;
                return doingNone();
            }
            cout << "Please enter the post number you want to view." << endl;
            int postNumber = readInt(1, POST::postAmount);
            // viewPostDetail(POST::post[postNumber].getOwnerID(), postNumber);
        } else if (cmd == 2) {
            USER::user[currentUser].launchPost();
        }
    }
}

void viewMainPage() {
    while (true) {
        clearScreen();
        backToMainPage = true;
        cout << "Welcome to the main page!" << endl;
        cout << "MENU---" << endl;
        cout << "Press 0 to logout." << endl;
        cout << "Press 1 to view my Profile." << endl;
        cout << "Press 2 to open the Post Square." << endl;
        cout << "---" << endl;
        int cmd = readInt(0, 2);
        if (cmd == 0) {
            cout << "Bye!" << endl;
            return;
        } else if (cmd == 1) {
            // viewUserProfile(currentUser);
        } else if (cmd == 2) {
            viewPostSquare();
        }
    }
}

Page::Page() {
    content = "Default content.";
    // menu = nullptr;
}

// void Page::display() {
//     cout << content << endl;
//     menu->display(1);
// }

// Menu::Menu() {
//     title = "Please choose the options by up and down key or entering the number of the option.";
//     itemTitle = "Default";
//     parent = nullptr;
//     itemResult = nullptr;
// }

// string Menu::getItemTitle() {
//     return itemTitle;
// }

// void Menu::addItem(Menu *item) {
//     items.push_back(item);
// }

// int Menu::display(int opLine) {
//     if (opLine == 0) return;
//     outputTitle(title);
//     assert(1 <= opLine && opLine <= items.size());
//     for (int i = 1; i <= items.size(); ++i) {
//         if (i == opLine) {
//             cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED) << "-> " << Color::Modifier();
//         } else {
//             cout << "   ";
//         }
//         cout << Color::Modifier(Color::RESET, Color::BG_DEFAULT, Color::FG_LIGHT_YELLOW) << i << "). " << Color::Modifier();
//         cout << items[i - 1]->getItemTitle() << endl;
//     }
// }