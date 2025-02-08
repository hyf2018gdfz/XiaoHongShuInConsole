#ifndef _PAGE_H
#define _PAGE_H
#include "common.h"
class Menu;
class PageNav;

class PageContent {
    friend class PageNav;

private:
    string content;

public:
    PageContent(const string &content);
    void display();
};

struct Page {
    shared_ptr<PageContent> content;
    shared_ptr<Menu> menu;
    Page(const shared_ptr<PageContent> &content, const shared_ptr<Menu> &menu);
};

class PageNav {
private:
    std::stack<shared_ptr<Page>> navStack;
    shared_ptr<Page> curPage;

public:
    PageNav();
    void display();
};
#endif