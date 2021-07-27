#include "jsonbool.h"


JsonBool::JsonBool(): value(false) {}
JsonBool::JsonBool(bool _value): value(_value) {}

JsonResult JsonBool::parse(std::u32string::iterator input) {
	// clear whitespaces
	input = Parser::yankWhitespace(input);
	// checks for true
	StringResult res = Parser::parseString(input,U"true");
	if (res.has_value())
		return std::make_pair(new JsonBool(true),res.value().second);
	// otherwise: checks for false
	res = Parser::parseString(input,U"false");
	if (res.has_value())
		return std::make_pair(new JsonBool(false),res.value().second);
	return {};
}
