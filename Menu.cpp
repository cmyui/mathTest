#include <iostream>

#include <cstring>
#include <iomanip>
#include "Menu.h"

namespace cmyui {
	void Menu::addItem(std::string name) {
		_items.push_back(name);
	}

	/*
	void Menu::addItem(MenuItem& item) {
		_items.push_back(item);
	}*/

	void Menu::display() {
		std::cout << _name << std::endl;
		for (int i = 0; i < _items.size(); i++)
			std::cout << i + 1 << ". " << _items[i] << std::endl;
		std::cout << "0. Exit" << std::endl;
	}

	std::string Menu::operator[](int i) {
		return _items[i];
	}

	int Menu::run() {
		return (display(), std::cout << "> ", getIntInRange(0, _items.size()));
	}
}