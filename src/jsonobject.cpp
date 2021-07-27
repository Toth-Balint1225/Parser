#include "jsonobject.h"

JsonObject::~JsonObject() {
	// NOTE important dynamic data
	for (auto& it : contents) {
		delete it.second;
	}
}

JsonResult JsonObject::parse(std::u32string::iterator input) {
	return {};
}
