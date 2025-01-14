#include "color.h"

/// @brief 输出标题
/// @param str 标题文字
void outputTitle(string str)
{
    cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_CYAN)
         << str
         << Color::Modifier() << endl;
}