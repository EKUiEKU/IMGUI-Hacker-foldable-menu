#pragma once

#include <iostream>
#include <string>
#include <vector>

class LinkItem {
public:
	int index;

	//������
	//0b100��ʾMenuTitle
	//0b010��ʾFirstItem
	//0b001��ʾSecondItem
	int locate;
	//����
	std::string title;
	//״̬
	std::vector<std::string> status;
	//�ص���
	int resultCode;

	int statusCode = 0;
	bool selected = false;
};