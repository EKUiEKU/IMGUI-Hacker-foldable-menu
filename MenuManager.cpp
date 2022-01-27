#include "MenuManager.h"
#include "imgui/imgui.h"
#include <vector>
#include <Windows.h>
#include "MenuList.h"


//菜单回调函数
void menuStatusChangedListener(int resultCode, bool isOpen, std::string title, std::string statusTitle) {


    switch (resultCode) {
    case 0:
        if (isOpen)
        {
            std::cout << "透视设置 打开" << std::endl;
        }
        else {
            std::cout << "透视设置 关闭" << std::endl;
        }
        break;


    case 9:

        if (isOpen)
        {
            std::cout << "自动瞄准 打开" << std::endl;
        }
        else {
            std::cout << "自动瞄准 关闭" << std::endl;
        }
        break;


        break;


    case 12:

        if (isOpen)
        {
            std::cout << "自动热键 打开 按键：" << statusTitle << std::endl;
        }
        else {
            std::cout << "自动热键 关闭" << std::endl;
        }
        break;


    case 13:

        if (isOpen)
        {
            std::cout << "自瞄范围 打开 范围："  << statusTitle << std::endl;
        }
        else {
            std::cout << "自瞄范围 关闭" << std::endl;
        }
        break;

    case 15:
        if (isOpen)
        {
            std::cout << "辅助准心 打开" << std::endl;
        }
        else {
            std::cout << "辅助准心 关闭" << std::endl;
        }
        break;
        break;
    }


}


MenuManager::MenuManager()
{
    menuList->setMenuStatusChangedListener(menuStatusChangedListener);
}

void MenuManager::renderMenu()
{
    int flag = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
    ImGui::Begin("分级菜单", NULL, flag);                          // Create a window called "Hello, world!" and append into it.

    ImGui::SetWindowSize({ 200,1000 });
   

    menuList->drawMenu();

    ImGui::End();
}

