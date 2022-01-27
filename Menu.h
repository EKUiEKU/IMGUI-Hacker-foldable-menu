#pragma once

#include <string>
#include <list>
#include <vector>


namespace Menu {
	class SecondItem {
	public:
		std::string title;
		int resultCode;
		std::vector<std::string> status;
	};


	class Item {
	public:
		std::string title;
		int resultCode;
		std::list<SecondItem> secondItems;
	};

	class Menu {
	public:
		std::string title;
		std::list<Item> items;
	};
}