#pragma once

#include <iostream>
#include <string>
#include <vector>

class LinkItem {
public:
	int index;

	//二进制
	//0b100表示MenuTitle
	//0b010表示FirstItem
	//0b001表示SecondItem
	int locate;
	//标题
	std::string title;
	//状态
	std::vector<std::string> status;
	//回调码
	int resultCode;

	int statusCode = 0;
	bool selected = false;
};