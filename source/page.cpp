#include "page.h"

#include "menu.h"
#include "color.h"

// Page类

Page::Page(const string &content, const shared_ptr<Menu> &menu) {
    this->content = content;
    this->menu = menu;
}

void Page::setContent(const string &content) {
    this->content = content;
}

void Page::setMenu(const shared_ptr<Menu> &menu) {
    this->menu = menu;
}

void Page::display() {
    cout << content << endl;
    menu->display(menu->lstOp);
}

// PageNav类