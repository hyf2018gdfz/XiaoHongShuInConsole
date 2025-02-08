#include "menu.h"

#include "page.h"
#include "color.h"

// MenuItem类的实现

MenuItem::MenuItem(const string &content, const std::variant<std::shared_ptr<Menu>, std::shared_ptr<Page>> &target) {
    this->content = content;
    this->target = target;
}

string MenuItem::getContent() {
    return content;
}

void MenuItem::setTarget(const std::variant<std::shared_ptr<Menu>, std::shared_ptr<Page>> &target) {
    this->target = target;
}

std::variant<std::shared_ptr<Menu>, std::shared_ptr<Page>> MenuItem::getTarget() const {
    return target;
}

// Menu类的实现

Menu::Menu(const string &title = "Please choose the options by up and down key or entering the number of the option.", const variant<shared_ptr<Menu>, shared_ptr<Page>> &parent) {
    this->title = title;
    this->parent = parent;
}

void Menu::setTitle(const string &title) {
    this->title = title;
}

void Menu::addItem(const shared_ptr<MenuItem> &item) {
    items.push_back(item);
}

void Menu::display(int opLine) {
    outputTitle(title);
    assert(0 <= opLine && opLine <= items.size());
    for (int i = 0; i <= items.size(); ++i) {
        if (i == opLine) {
            cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED) << "-> " << Color::Modifier();
        } else {
            cout << "   ";
        }
        cout << Color::Modifier(Color::RESET, Color::BG_DEFAULT, Color::FG_LIGHT_YELLOW) << i << "). " << Color::Modifier();
        if (i == 0) {
            if (std::holds_alternative<shared_ptr<Menu>>(parent)) {
                cout << "Back to the last menu" << endl;
            } else {
                cout << "Back to the last page" << endl;
            }
        } else {
            cout << items[i - 1]->getContent() << endl;
        }
    }
}

variant<shared_ptr<Menu>, shared_ptr<Page>> Menu::getItemTarget(int opLine) {
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

void Menu::setParent(const variant<shared_ptr<Menu>, shared_ptr<Page>> &parent) {
    this->parent = parent;
}