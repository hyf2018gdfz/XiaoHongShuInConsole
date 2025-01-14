#include "register.h"
#include "bugreport.h"
#include "user.h"

extern int currentUser;

string generate_verifycode() {
    string code = "";
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 4; i++) {
        code += letters[rand() % 26];
    }
    return code;
}

int isPhoneNumberValid(const string &phoneNumber) {
    if (phoneNumber.length() != 11)
        return Bug::InvalidPhoneNumberLength;
    for (char c : phoneNumber) {
        if (!isdigit(c))
            return Bug::InvalidPhoneNumberDigit;
    }
    const string operators[] = {"134", "135", "136", "137", "138", "139", "147", "150", "151", "152", "157", "158", "159", "188", "130", "131", "132", "155", "156", "185", "186", "133", "149", "153", "173", "177", "180", "181", "189"};
    string prefix = phoneNumber.substr(0, 3);
    auto it = find(begin(operators), end(operators), prefix);
    if (it == end(operators)) return Bug::InvalidPhoneNumberPrefix;
    if (USER::phoneNumberToID.count(phoneNumber)) return Bug::PhoneNumberRegistered;
    return Bug::Succeed;
}

int isPassWordValid(const string &passWord) {
    if (passWord.length() < 8) {
        return Bug::InvalidPasswordTooShort;
    }
    if (passWord.find_first_of("abcdefghijklmnopqrstuvwxyz") == string::npos) {
        return Bug::InvalidPasswordNoLowerCaseLetter;
    }
    if (passWord.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos) {
        return Bug::InvalidPasswordNoUpperCaseLetter;
    }
    if (passWord.find_first_of("0123456789") == string::npos) {
        return Bug::InvalidPasswordNoDigit;
    }
    return Bug::Succeed;
}

void registerAccount() {
    string phoneNumber = "", passWord = "", nickName = "";

    cout << "Please enter your phonenumber:" << endl;
    while (true) {
        getline(cin, phoneNumber);
        int flg = isPhoneNumberValid(phoneNumber);
        if (flg == Bug::Succeed) break;
        if (flg == Bug::InvalidPhoneNumberLength) {
            cout << "Invalid phone number length. Try again." << endl;
        } else if (flg == Bug::InvalidPhoneNumberDigit) {
            cout << "Invalid phone number digit. Try again." << endl;
        } else if (flg == Bug::InvalidPhoneNumberPrefix) {
            cout << "Invalid phone number prefix. Try again." << endl;
        } else if (flg == Bug::PhoneNumberRegistered) {
            cout << "This mobile phone number has been registered." << endl;
        }
    }

    cout << "Please enter your password:" << endl;
    while (true) {
        getline(cin, passWord);
        int flg = isPassWordValid(passWord);
        if (flg == Bug::Succeed) break;
        if (flg == Bug::InvalidPasswordTooShort) {
            cout << "The password must contain at least 8 characters." << endl;
        } else if (flg == Bug::InvalidPasswordNoLowerCaseLetter) {
            cout << "The password must contain lower case letters." << endl;

        } else if (flg == Bug::InvalidPasswordNoUpperCaseLetter) {
            cout << "The password must contain upper case letters." << endl;

        } else if (flg == Bug::InvalidPasswordNoDigit) {
            cout << "The password must contain numbers." << endl;
        }
    }

    cout << "Please enter your nickname:" << endl;
    getline(cin, nickName);

    string checkCode = "", verifyCode = "";
    while (true) {
        checkCode = generate_verifycode();
        cout << "Your verifycode is: " << checkCode << ",please repeat it:" << endl;
        getline(cin, verifyCode);
        if (verifyCode != checkCode) {
            cout << "Wrong verifycode. Try again." << endl;
        } else {
            cout << "Register Success." << endl;
            break;
        }
    }

    User tmp(USER::userAmount + 1, getTime(), phoneNumber, passWord, nickName);

    USER::user[++USER::userAmount] = tmp;
    USER::phoneNumberToID[phoneNumber] = USER::userAmount;
    currentUser = USER::userAmount;

    overwriteUsers();
}