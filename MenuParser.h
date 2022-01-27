#pragma once

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif


#include "Menu.h"
#include "json/json.h"


class MenuParser
{
public:
	Menu::Menu parse(std::string path);
};


inline std::unique_ptr<MenuParser> menParser;
