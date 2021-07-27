#include "jsonint.h"


JsonInt::JsonInt(): value(0) {}
JsonInt::JsonInt(int _value): value(_value) {}

JsonResult JsonInt::parse(std::u32string::iterator input) {
	// clears whitespaces
	input = Parser::yankWhitespace(input);
	IntResult res = Parser::parseInt(input);
	if (res.has_value()) 
		return std::make_pair(new JsonInt(res.value().first),res.value().second);
	return {};
}
