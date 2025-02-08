#include "page.h"

#include "menu.h"
#include "color.h"

#include <conio.h>

// PageContent类

PageContent::PageContent(const string &content) {
    this->content = content;
}

void PageContent::display() {
    cout << content << endl;
}

// Page类

Page::Page(const shared_ptr<PageContent> &content, const shared_ptr<Menu> &menu) {
    this->content = content;
    this->menu = menu;
}

// PageNav类

#define UPKEY 72
#define DOWNKEY 80
#define ENTERKEY 13

PageNav::PageNav() {
}

void PageNav::display() {
    int curptr = 1;
    while (true) {
        clearScreen();
        curPage->content->display();
        curPage->menu->display();
        char cmd = _getch();
        if (cmd == UPKEY) {
            curptr--;
            if (curptr <= -1) {
                curptr = curPage->menu->getItemsAmt();
            }
            curPage->menu->lstOp = curptr;
        } else if (cmd == DOWNKEY) {
            curptr++;
            if (curptr >= curPage->menu->getItemsAmt()) {
                curptr = 0;
            }
            curPage->menu->lstOp = curptr;
        } else if (isdigit(cmd) && cmd - '0' <= curPage->menu->getItemsAmt()) {
            curptr = cmd - '0';
            curPage->menu->lstOp = curptr;
        } else if (cmd == ENTERKEY) {
            if (curptr == 0) {
                if (std::holds_alternative<shared_ptr<Menu>>(curPage->menu->parent)) {
                    curPage->menu = std::get<shared_ptr<Menu>>(curPage->menu->parent);
                } else {
                    curPage->menu->lstOp = 0;
                    curPage = std::get<shared_ptr<Page>>(curPage->menu->parent);
                }
            } else {
                if (std::holds_alternative<shared_ptr<Menu>>(curPage->menu->items[curptr]->getTarget())) {
                    curPage->menu = std::get<shared_ptr<Menu>>(curPage->menu->items[curptr]->getTarget());
                } else {
                    curPage->menu->lstOp = 0;
                    curPage = std::get<shared_ptr<Page>>(curPage->menu->items[curptr]->getTarget());
                }
            }
        }
    }
}