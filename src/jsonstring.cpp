#include "jsonstring.h"

JsonString::JsonString(const std::u32string& _value):
	value(_value) {}

JsonResult JsonString::parse(std::u32string::iterator input) {
	// consume whitespaces
	input = Parser::yankWhitespace(input);
	// require "
	CharResult quote = Parser::parseCharacter(input,U'\"');
	if (!quote.has_value()) {
		return std::nullopt;
	}
	input = quote.value().second;
	// string literal
	StringResult content = Parser::parseString(input);
	if (!content.has_value()) {
		return std::nullopt;
	}
	input = content.value().second;
	// require "
	CharResult endQuote = Parser::parseCharacter(input,U'\"');
	if (!endQuote.has_value()) {
		return std::nullopt;
	}
	input = endQuote.value().second;
	return std::make_pair(new JsonString(content.value().first),input);
}
