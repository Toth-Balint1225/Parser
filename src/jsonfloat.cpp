#include "jsonfloat.h"

JsonFloat::JsonFloat(): value(0) {}
JsonFloat::JsonFloat(float _value): value(_value) {}

JsonResult JsonFloat::parse(std::u32string::iterator input) {
	input = Parser::yankWhitespace(input);
	FloatResult res = Parser::parseFloat(input);
	if (res.has_value())
		return std::make_pair(new JsonFloat(res.value().first),res.value().second);
	return {};
}
