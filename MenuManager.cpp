#include "MenuManager.h"
#include "imgui/imgui.h"
#include <vector>
#include <Windows.h>
#include "MenuList.h"


//�˵��ص�����
void menuStatusChangedListener(int resultCode, bool isOpen, std::string title, std::string statusTitle) {


    switch (resultCode) {
    case 0:
        if (isOpen)
        {
            std::cout << "͸������ ��" << std::endl;
        }
        else {
            std::cout << "͸������ �ر�" << std::endl;
        }
        break;


    case 9:

        if (isOpen)
        {
            std::cout << "�Զ���׼ ��" << std::endl;
        }
        else {
            std::cout << "�Զ���׼ �ر�" << std::endl;
        }
        break;


        break;


    case 12:

        if (isOpen)
        {
            std::cout << "�Զ��ȼ� �� ������" << statusTitle << std::endl;
        }
        else {
            std::cout << "�Զ��ȼ� �ر�" << std::endl;
        }
        break;


    case 13:

        if (isOpen)
        {
            std::cout << "���鷶Χ �� ��Χ��"  << statusTitle << std::endl;
        }
        else {
            std::cout << "���鷶Χ �ر�" << std::endl;
        }
        break;

    case 15:
        if (isOpen)
        {
            std::cout << "����׼�� ��" << std::endl;
        }
        else {
            std::cout << "����׼�� �ر�" << std::endl;
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
    ImGui::Begin("�ּ��˵�", NULL, flag);                          // Create a window called "Hello, world!" and append into it.

    ImGui::SetWindowSize({ 200,1000 });
   

    menuList->drawMenu();

    ImGui::End();
}

