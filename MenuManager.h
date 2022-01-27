#pragma once

#include <iostream>

class MenuManager
{
public:
    MenuManager();
    void renderMenu();
};

inline std::unique_ptr<MenuManager> menuManager;
