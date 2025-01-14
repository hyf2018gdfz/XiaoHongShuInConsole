#include <windows.h>
#include "user.h"
#include "login.h"
#include "bugreport.h"

extern int currentUser;

int loginAccount() {
    string phoneNumber = "", passWord = "";
    int userID = 0;

    cout << "Please enter your phonenumber: " << endl;
    while (true) {
        getline(cin, phoneNumber);
        if (!USER::phoneNumberToID.count(phoneNumber)) {
            cout << "Account does not exist. Please register your account." << endl;
        } else {
            userID = USER::phoneNumberToID[phoneNumber];
            break;
        }
    }

    cout << "Please enter your password: " << endl;
    int triedcnt = 0;
    while (true) {
        getline(cin, passWord);
        if (passWord != USER::user[userID].getPassword()) {
            triedcnt++;
            if (triedcnt == 3) {
                cout << "Wrong!!!!!!!11" << endl;
                return Bug::LoginFailed;
            }
            cout << "Password incorrect. Please try again. You still have " << 3 - triedcnt << " tries." << endl;
        } else
            break;
    }
    cout << "Login success." << endl;
    currentUser = userID;
    return Bug::Succeed;
}