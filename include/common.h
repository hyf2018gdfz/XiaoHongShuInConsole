/// @brief: 本头文件包含了常用的一些头文件以及在std中的一些函数

#ifndef _COMMON_H
#define _COMMON_H

#include <time.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <variant>
#include "json.h"

namespace fromstd {
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::variant;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::move;
} // namespace fromstd
using namespace fromstd;

const int N = 10005;

int readInt(int rangeL, int rangeR);
time_t getTime();
string getTimeString(time_t &curtime);

void clearScreen();
void doingNone();

// TODO: 写入日志
// void writeLog();

#endif