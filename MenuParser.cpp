#include "MenuParser.h"
#include <fstream>
#include <iostream>

Menu::Menu MenuParser::parse(std::string json)
{

	Json::Reader reader;
	Json::Value jsonObject;
	Menu::Menu menu;



	if (reader.parse(json, jsonObject)) {
		auto menuTitle = jsonObject["title"];

		if (menuTitle.isString())
		{
			menu.title = menuTitle.asString();
		}

		auto items = jsonObject["items"];

		if (items.isArray()) {
			for (auto one : items) {
				Menu::Item item;
				auto itemTitle = one["title"];
				auto itemRC = one["resultCode"];
				auto seconds = one["secondItems"];

				if (itemTitle.isString())
				{
					item.title = itemTitle.asString();
				}

				if (itemRC.isInt()) {
					item.resultCode = itemRC.asInt();
				}

				if (seconds.isArray())
				{
					for (auto second : seconds) {
						Menu::SecondItem secondItem;
						auto secondItemTitle = second["title"];
						auto secondItemRC = second["resultCode"];
						auto secondItemStatus = second["status"];

						if (secondItemTitle.isString())
						{
							secondItem.title = secondItemTitle.asString();
						}

						if (secondItemRC.isInt()) {
							secondItem.resultCode = secondItemRC.asInt();
						}


						if (secondItemStatus.isArray())
						{
							for (auto s : secondItemStatus) {
								if (s.isString()) {
									secondItem.status.push_back(s.asString());
								}
							}
						}

						item.secondItems.push_back(secondItem);
					}
				}

				menu.items.push_back(item);
			}
		}
	}
	return menu;
}
