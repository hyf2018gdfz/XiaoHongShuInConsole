#ifndef _PAGE_H
#define _PAGE_H
#include "common.h"
class Menu;
class Page {
private:
    string content;
    shared_ptr<Menu> menu;

private:
    void setContent(const string &content);
    void setMenu(const shared_ptr<Menu> &menu);

public:
    Page(const string &content, const shared_ptr<Menu> &menu);
    void display();
};

class PageNav {
private:
    std::stack<std::pair<shared_ptr<Menu>, shared_ptr<Page>>> navStack;
    shared_ptr<Menu> curMenu;
    shared_ptr<Page> curPage;

public:
    PageNav();
};
#endif