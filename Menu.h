#ifndef CMYUI_MENU_H__
#define CMYUI_MENU_H__

#include "MenuItem.h"
#include "Utils.h"

namespace cmyui {
	class Menu {
		std::string _name;
		std::vector<std::string> _items;

	public:
		Menu(std::string name) : _name(name) {}

		void addItem(std::string name);

		//void addItem(MenuItem& item);
		void display();

		int run();


		std::string operator[](int i);
	};
}

#endif
