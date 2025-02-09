#ifndef _MENU_H
#define _MENU_H
#include "common.h"

class Page;
class Menu;
// class PageNav;

using ptrMenu = shared_ptr<Menu>;
using ptrPage = shared_ptr<Page>;

class MenuItem {
private:
    string content;
    variant<ptrMenu, ptrPage> target;

private:
    void setTarget(const variant<ptrMenu, ptrPage> &target);

public:
    MenuItem();
    MenuItem(const string &content, const variant<ptrMenu, ptrPage> &target);
    string getContent();
    variant<ptrMenu, ptrPage> getTarget() const;
};

class Menu {
    // friend class PageNav;

private:
    string title = "Please choose the options by up and down key or entering the number of the option.";
    vector<shared_ptr<MenuItem>> items; // 子菜单项

private:
    void setTitle(const string &title);
    void setParent(const variant<ptrMenu, ptrPage> &parent);

public:
    int lstOp = 0; // 用户上一次停留在该目录时的选项

public:
    Menu(const string &title, const variant<ptrMenu, ptrPage> &parent);
    void addItem(const shared_ptr<MenuItem> &item);
    void display(int opLine); // 显示菜单

    variant<ptrMenu, ptrPage> getItemTarget(int opLine);
    int getItemsAmt();
};

// testing

class Page {
};
#endif