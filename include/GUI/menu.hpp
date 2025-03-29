#ifndef MENU_HPP
#define MENU_HPP

#include "button.h"
#include "appMenu.h"

namespace Menu {
    extern const Vector2 lowerLeft;
    extern Button showMenu;
    extern std::vector<std::pair<Button*, std::vector<GUIObject*> > > menuItems;
    void update();
    void render();
};

#endif // MENU_HPP