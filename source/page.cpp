// #include "page.h"

// #include "menu.h"
// #include "color.h"

// #include <conio.h>

// // PageContent类

// PageContent::PageContent(const string &content) {
//     this->content = content;
// }

// void PageContent::display() {
//     cout << content << endl;
// }

// // Page类

// Page::Page(const shared_ptr<PageContent> &content, const shared_ptr<Menu> &menu) {
//     this->content = content;
//     this->menu = menu;
// }

// // PageNav类

// #define UPKEY 72
// #define DOWNKEY 80
// #define ENTERKEY 13

// using pagePtr = shared_ptr<Page>;
// using menuPtr = shared_ptr<Menu>;

// PageNav::PageNav(pagePtr &rootPage) {
//     navStack.push(rootPage);
// }

// void PageNav::navigate(int opLine) {
//     assert(!navStack.empty());
//     auto curPage = navStack.top();
//     assert(0 <= opLine && opLine <= curPage->menu->getItemsAmt());
//     if (opLine == 0) {
//         if (std::holds_alternative<menuPtr>(curPage->menu->parent)) {
//             curPage->menu = std::get<menuPtr>(curPage->menu->parent);
//         } else {
//             navStack.pop();
//         }
//     } else {
//         auto target = curPage->menu->items[opLine]->getTarget();
//         if (std::holds_alternative<menuPtr>(target)) {
//             curPage->menu = std::get<menuPtr>(target);
//         } else {
//             navStack.push(std::get<pagePtr>(target));
//         }
//     }
// }

// void PageNav::display() {
//     int curptr = 1;
//     auto curPage = navStack.top();
//     while (true) {
//         clearScreen();
//         curPage->content->display();
//         curPage->menu->display();
//         char cmd = _getch();
//         if (cmd == UPKEY) {
//             curptr--;
//             if (curptr <= -1) {
//                 curptr = curPage->menu->getItemsAmt();
//             }
//             curPage->menu->lstOp = curptr;
//         } else if (cmd == DOWNKEY) {
//             curptr++;
//             if (curptr >= curPage->menu->getItemsAmt()) {
//                 curptr = 0;
//             }
//             curPage->menu->lstOp = curptr;
//         } else if (isdigit(cmd) && cmd - '0' <= curPage->menu->getItemsAmt()) {
//             curptr = cmd - '0';
//             curPage->menu->lstOp = curptr;
//         } else if (cmd == ENTERKEY) {
//             if (curptr == 0) {
//                 if (std::holds_alternative<menuPtr>(curPage->menu->parent)) {
//                     curPage->menu = std::get<menuPtr>(curPage->menu->parent);
//                 } else {
//                     curPage->menu->lstOp = 0;
//                     curPage = std::get<pagePtr>(curPage->menu->parent);
//                 }
//             } else {
//                 if (std::holds_alternative<menuPtr>(curPage->menu->items[curptr]->getTarget())) {
//                     curPage->menu = std::get<menuPtr>(curPage->menu->items[curptr]->getTarget());
//                 } else {
//                     curPage->menu->lstOp = 0;
//                     curPage = std::get<pagePtr>(curPage->menu->items[curptr]->getTarget());
//                 }
//             }
//         }
//     }
// }