#ifndef CMYUI_MENUITEM_H__
#define CMYUI_MENUITEM_H__

#include <string>
#include "Utils.h"

namespace cmyui {
	struct MenuItem {
		std::string name;
		void (*function)();

		MenuItem(std::string _name, void (*_function)())
			: name(_name), function(_function) {}

		void operator()() { function(); }
	};
}

#endif
