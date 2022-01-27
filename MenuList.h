#pragma once

#include "LinkItem.h"
#include "Menu.h"
#include <vector>
#include <iostream>

class MenuList
{
private:
	std::vector<LinkItem*> list;
	Menu::Menu menu;
	LinkItem* currentSelected;

	//回调函定义
	typedef void (*onMenuStatusChangedListener)(int resultCode,bool isOpen,std::string title,std::string statusTitle);

	onMenuStatusChangedListener mListenr;

	void initList();
	void vkListener();
	void callBackListener(int resultCode, bool isOpen, std::string title, std::string statusTitle);
public:
	MenuList();
	~MenuList();

	void drawMenu();

	void setMenuStatusChangedListener(onMenuStatusChangedListener listener);
};


inline std::unique_ptr<MenuList> menuList;
