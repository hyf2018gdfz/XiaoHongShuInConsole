#ifndef _BUGREPORT
#define _BUGREPORT
enum Bug
{
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