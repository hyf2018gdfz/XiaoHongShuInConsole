#include "menu.h"

// #include "page.h"
#include "color.h"

// MenuItem类的实现

MenuItem::MenuItem() {
    this->content = "Default Menu Item";
    this->target = std::make_shared<Menu>(nullptr);
}

MenuItem::MenuItem(const string &content, const variant<ptrMenu, ptrPage> &target) {
    this->content = content;
    this->target = target;
}

string MenuItem::getContent() {
    return content;
}

void MenuItem::setTarget(const variant<ptrMenu, ptrPage> &target) {
    this->target = target;
}

variant<ptrMenu, ptrPage> MenuItem::getTarget() const {
    return target;
}

// Menu类的实现

Menu::Menu(const string &title, const variant<ptrMenu, ptrPage> &parent) {
    this->title = title;
}

void Menu::setTitle(const string &title) {
    this->title = title;
}

void Menu::addItem(const shared_ptr<MenuItem> &item) {
    items.push_back(item);
}

void Menu::display(int opLine = -1) {
    outputTitle(title);
    if (opLine == -1) opLine = lstOp;
    assert(0 <= opLine && opLine <= items.size());
    for (int i = 0; i <= items.size(); ++i) {
        if (i == opLine) {
            cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED) << "-> " << Color::Modifier();
        } else {
            cout << "   ";
        }
        cout << Color::Modifier(Color::RESET, Color::BG_DEFAULT, Color::FG_LIGHT_YELLOW) << i << "). " << Color::Modifier();
        if (i == 0) {
            if (holds_alternative<ptrMenu>(parent)) {
                cout << "Back to the last menu" << endl;
            } else {
                cout << "Back to the last page" << endl;
            }
        } else {
            cout << items[i - 1]->getContent() << endl;
        }
    }
}

variant<ptrMenu, ptrPage> Menu::getItemTarget(int opLine) {
    assert(0 <= opLine && opLine <= items.size());
    if (opLine == 0) {
        return parent;
    } else {
        return items[opLine - 1]->getTarget();
    }
}

int Menu::getItemsAmt() {
    return items.size();
}

void Menu::setParent(const variant<ptrMenu, ptrPage> &parent) {
    this->parent = parent;
}