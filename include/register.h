#ifndef _REGISTER_H
#define _REGISTER_H
#include <bits/stdc++.h>
#include "common.h"
using namespace std;

string generate_verifycode();
int isPassWordValid(const string &passWord);
int isPhoneNumberValid(const string &phoneNumber);
void registerAccount();

#endif