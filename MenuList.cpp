#include "MenuList.h"

#include <Windows.h>

#include "MenuParser.h"
#include "imgui/imgui.h"
#include "resource1.h"


LinkItem* moveToNextFirstItem(std::vector<LinkItem*> list, LinkItem* current);
LinkItem* moveToBeforeFirstItem(std::vector<LinkItem*> list, LinkItem* current);
LinkItem* moveToNextItem(std::vector<LinkItem*> list, LinkItem* current);
LinkItem* moveToBeforeItem(std::vector<LinkItem*> list, LinkItem* current);


//加载资源
std::string UseCustomResource(int rcId)
{
	//定位自定义资源，如果是从本模块定位资源，也可将句柄简单地置为NULL即可
	//HMODULE phexmodule = GetModuleHandle(L"PCommServerHandler.dll");
	HMODULE phexmodule = LoadLibrary("PCommServerHandler.dll");
	HRSRC hRsrc = FindResource(phexmodule, MAKEINTRESOURCE(rcId), TEXT("json"));

	if (NULL == hRsrc)
		return "rcError1";
	//获取资源的大小
	DWORD dwSize = SizeofResource(phexmodule, hRsrc);
	if (0 == dwSize)
		return "rcError2";
	//加载资源
	HGLOBAL hGlobal = LoadResource(phexmodule, hRsrc);
	if (NULL == hGlobal)
		return "rcError3";
	//锁定资源
	LPVOID pBuffer = LockResource(hGlobal);
	if (NULL == pBuffer)
		return "rcError4";

	std::string  s = (char*&)pBuffer;// LPVOID  ---> String        
	s = s.substr(0, dwSize); //去除各种文件的附加信息。
	return s;
}

MenuList::MenuList()
{
	
	menu = menParser->parse(UseCustomResource(IDR_JSON1));

	initList();
}

MenuList::~MenuList()
{
	for (auto item : list) {
		delete(item);
	}
}

void MenuList::initList()
{

	int index = 0;
	//Menu标题
	if (!menu.title.empty())
	{
		LinkItem* menuTitle = new LinkItem();
		menuTitle->index = index;
		menuTitle->locate = 0b100;
		menuTitle->resultCode = -1;
		menuTitle->title = menu.title;

		list.push_back(menuTitle);
	}

	auto firstItems = menu.items;

	for (auto firstItem : firstItems) {
		LinkItem* first = new LinkItem();

		list.push_back(first);

		first->index = ++index;
		first->locate = 0b010;
		first->resultCode = firstItem.resultCode;
		first->title = firstItem.title;

		auto secondItems = firstItem.secondItems;
		for (auto secondItem : secondItems) {
			LinkItem* second = new LinkItem();

			second->index = ++index;
			second->locate = 0b001;
			second->resultCode = secondItem.resultCode;
			second->title = secondItem.title;
			second->status = secondItem.status;

			list.push_back(second);

		}
	}


	currentSelected = NULL;
	//初始化默认选择第一行Item
	if (list.size() > 1)
	{
		list[1]->selected = true;
		currentSelected = list[1];

	}
}


void MenuList::drawMenu()
{
	std::string firstMenuStatus = u8"[+]";
	std::string secondMenuStatus = u8"[关闭]";
	int  statusCode = 0;
	LinkItem* currentFirstItem = NULL;

	for (auto item : list) {
		firstMenuStatus = u8"[+]";
		secondMenuStatus = u8"[关闭]";

		switch (item->locate)
		{
		case 0b100:

			ImGui::Title(item->title.c_str());

			break;
		case 0b010:


			if (item->statusCode != 0)
			{
				firstMenuStatus = u8"[-]";
			}
			currentFirstItem = item;

			ImGui::FirstItem(item->title.c_str(), firstMenuStatus.c_str(), item->selected);

			break;
		case 0b001:

			if (currentFirstItem != NULL && currentFirstItem->statusCode == 0) {
				//一级菜单处于缩进状态
				continue;
			}

			statusCode = item->statusCode;

			if (item->status.size() > 0)
			{
				secondMenuStatus = u8"[" + item->status[statusCode] + u8"]";
				ImGui::SecondItem(item->title.c_str(), secondMenuStatus.c_str(), true, item->selected);
				continue;
			}

			if (statusCode != 0) {
				secondMenuStatus = u8"[开启]";
			}

			ImGui::SecondItem(item->title.c_str(), secondMenuStatus.c_str(), statusCode != 0, item->selected);

			break;
		default:
			break;
		}
	}

	vkListener();
}

void MenuList::setMenuStatusChangedListener(onMenuStatusChangedListener listener)
{
	mListenr = listener;
}


void MenuList::vkListener()
{

	if (currentSelected == NULL)
	{
		return;
	}

	if (ImGui::IsKeyReleased(VK_RIGHT)) {

		int statusSize = currentSelected->status.size();
		if (statusSize == 0)
		{
			currentSelected->statusCode = (currentSelected->statusCode + 1) % 2;

		}
		else {
			currentSelected->statusCode = (currentSelected->statusCode +1) % (currentSelected->status.size());

			
		}

		int resultCode = currentSelected->resultCode;
		std::string statusTitle;

		if (statusSize != 0)
		{
			int tt = currentSelected->statusCode - 1;

			if (tt >= 0)
			{
				statusTitle = currentSelected->status[tt];
			}
		}
		callBackListener(resultCode, currentSelected->statusCode != 0, currentSelected->title, statusTitle);
	}


	if (ImGui::IsKeyReleased(VK_LEFT)) {

		int statusSize = currentSelected->status.size();
		if (statusSize == 0)
		{
			int t = --currentSelected->statusCode % 2;

			if (t < 0) {
				t = currentSelected->status.size()  - 1;
			}

			currentSelected->statusCode = t;
		}
		else {
			int t = currentSelected->statusCode - 1;

			if (t < 0) {
				t = currentSelected->status.size() - 1;
			}

			currentSelected->statusCode = t % (currentSelected->status.size());
		}


		int resultCode = currentSelected->resultCode;
		std::string statusTitle;

		if (statusSize != 0)
		{
			int tt = currentSelected->statusCode - 1;

			if (tt >= 0)
			{
				statusTitle = currentSelected->status[tt];
			}
		}
		callBackListener(resultCode, currentSelected->statusCode != 0, currentSelected->title, statusTitle);
	}

	if (ImGui::IsKeyReleased(VK_DOWN)) {

		currentSelected->selected = false;;

		if (currentSelected->locate == 0b010 && currentSelected->statusCode == 0) {
			//关闭二级菜单
			currentSelected = moveToNextFirstItem(list, currentSelected);
		}
		else {
			//打开二级菜单
			currentSelected = moveToNextItem(list, currentSelected);
		}

		currentSelected->selected = true;
	}

	if (ImGui::IsKeyReleased(VK_UP)) {
		currentSelected->selected = false;;

		auto t = moveToBeforeFirstItem(list, currentSelected);

		if (currentSelected->locate == 0b010 && t->statusCode == 0) {
			//关闭二级菜单
			currentSelected = t;
		}
		else {
			//打开二级菜单
			currentSelected = moveToBeforeItem(list, currentSelected);
		}


		currentSelected->selected = true;
	}

}


LinkItem* moveToNextFirstItem(std::vector<LinkItem*> list, LinkItem* current) {
	
	if (list.size() <= 1) {
		return NULL;
	}

	if (list.size() == 2) {
		return current;
	}

	LinkItem* next;
	int currentIndex = current->index;

	while (true) {
		next = list[++currentIndex % list.size()];

		if (next->locate == 0b010)
		{
			return next;
		}
	}

}



LinkItem* moveToBeforeFirstItem(std::vector<LinkItem*> list, LinkItem* current) {

	if (list.size() <= 1) {
		return NULL;
	}

	if (list.size() == 2) {
		return current;
	}

	LinkItem* next;
	int currentIndex = current->index;

	while (true) {
		int t = --currentIndex % list.size();

		if (t <= 0) {
			t = list.size() - 1;
		}

		next = list[t];

		if (next->locate == 0b010)
		{
			return next;
		}

		currentIndex = next->index;
	}

}


LinkItem* moveToNextItem(std::vector<LinkItem*> list, LinkItem* current) {
	if (list.size() <= 1) {
		return NULL;
	}

	if (list.size() == 2) {
		return current;
	}

	LinkItem* next;
	int currentIndex = current->index;

	while (true) {
		next = list[++currentIndex % list.size()];

		if (next->locate != 0b100)
		{
			return next;
		}
	}
}


LinkItem* moveToBeforeItem(std::vector<LinkItem*> list, LinkItem* current) {
	if (list.size() <= 1) {
		return NULL;
	}

	if (list.size() == 2) {
		return current;
	}

	LinkItem* next;
	int currentIndex = current->index;

	while (true) {
		int t = --currentIndex % list.size();

		if (t <= 0) {
			t = list.size() - 1;
		}

		next = list[t];

		if (next->locate != 0b100)
		{
			return next;
		}

		currentIndex = next->index;
	}
}


void MenuList::callBackListener(int resultCode, bool isOpen, std::string title, std::string statusTitle)
{
	if (mListenr != NULL) {
		mListenr(resultCode,isOpen,title,statusTitle);
	}
}