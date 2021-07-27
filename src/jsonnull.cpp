#include "jsonnull.h"

JsonResult JsonNull::parse(std::u32string::iterator input) {
	input = Parser::yankWhitespace(input);
	StringResult res = Parser::parseString(input,U"null");
	if (res.has_value()) {
		return std::make_pair(new JsonNull,res.value().second);
	}
	return {};
}
