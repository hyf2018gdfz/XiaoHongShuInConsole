#ifndef _BUGREPORT_H
#define _BUGREPORT_H
enum Bug {
    Succeed,

    InvalidPhoneNumberLength,
    InvalidPhoneNumberDigit,
    InvalidPhoneNumberPrefix,

    PhoneNumberRegistered,

    InvalidPasswordTooShort,
    InvalidPasswordNoLowerCaseLetter,
    InvalidPasswordNoUpperCaseLetter,
    InvalidPasswordNoDigit,

    RegisterFailed,

    LoginFailed,
};

#endif