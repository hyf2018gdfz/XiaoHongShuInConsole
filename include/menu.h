#ifndef _MENU_H
#define _MENU_H
#include "common.h"

class Page;
class Menu;
class PageNav;

class MenuItem {
private:
    string content;
    variant<shared_ptr<Menu>, shared_ptr<Page>> target;

private:
    void setTarget(const variant<shared_ptr<Menu>, shared_ptr<Page>> &target);

public:
    MenuItem(const string &content, const variant<shared_ptr<Menu>, shared_ptr<Page>> &target);
    string getContent();
    variant<shared_ptr<Menu>, shared_ptr<Page>> getTarget() const;
};

class Menu {
    friend class PageNav;

private:
    string title;
    vector<shared_ptr<MenuItem>> items;                 // 子菜单项
    variant<shared_ptr<Menu>, shared_ptr<Page>> parent; // 父菜单或父界面项

private:
    void setTitle(const string &title);
    void setParent(const variant<shared_ptr<Menu>, shared_ptr<Page>> &parent);

public:
    int lstOp = 0;

public:
    Menu(const string &title, const variant<shared_ptr<Menu>, shared_ptr<Page>> &parent);
    void addItem(const shared_ptr<MenuItem> &item);
    void display(int opLine = -1); // 显示菜单

    variant<shared_ptr<Menu>, shared_ptr<Page>> getItemTarget(int opLine);
    int getItemsAmt();
};
#endif