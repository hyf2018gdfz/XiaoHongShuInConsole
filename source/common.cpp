#include <limits>
#include "common.h"

extern bool backToMainPage;

int readInt(int rangeL, int rangeR) { // 读取一个范围内的整数
    int n;
    while (true) {
        cin >> n;
        if (!cin) {
            if (cin.eof()) return 0;
            cin.clear();
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            cout << "You should input an integer. Please try again." << endl;
        } else if (n > rangeR || n < rangeL) {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            cout << "Out of range! You should input an integer in range [" << rangeL << "," << rangeR << "]." << endl;
        } else {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return n;
        }
    }
}

time_t getTime() {
    time_t curtime;
    time(&curtime);
    return curtime;
}

string getTimeString(time_t &curtime) {
    tm *nowtime = localtime(&curtime);
    using std::to_string;
    string Time = to_string(1900 + nowtime->tm_year) + "-" + to_string(1 + nowtime->tm_mon) + "-" + to_string(nowtime->tm_mday) + " " + to_string(nowtime->tm_hour) + ":" + to_string(nowtime->tm_min) + ":" + to_string(nowtime->tm_sec);
    return Time;
}

// #define _MAIN_DEBUG

void clearScreen() { // 清屏
#ifndef _MAIN_DEBUG
    system("cls");
#else
    ;
#endif
}

void doingNone() { // 无法前进到下一个界面时的提示
    cout << "MENU---" << endl;
    cout << "Enter 0 to return." << endl;
    cout << "Enter -1 to return to the main page." << endl;
    cout << "---" << endl;
    int cmd = readInt(-1, 0);
    if (cmd == -1) backToMainPage = false;
    return;
}