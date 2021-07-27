#include "jsonarray.h"

JsonArray::JsonArray(const std::list<JsonSymbol*>& _contents): contents(_contents) {
}

JsonArray::~JsonArray() {
	// NOTE important dynamic data
	for (auto& it : contents) {
		delete it;
	}
}

#include <iostream>
JsonResult JsonArray::parse(std::u32string::iterator input) {
	input = Parser::yankWhitespace(input);
	CharResult openBracket = Parser::parseCharacter(input,'[');
	if (!openBracket.has_value()) {
		std::cout << "opening bracket expected" << std::endl;
		return {};
	}
	input = openBracket.value().second;
	std::list<JsonSymbol*> buffer;
	JsonResult temp = JsonParser::parse(input);
	while (temp.has_value()) {
		buffer.push_back(temp.value().first);
		input = temp.value().second;
		input = Parser::yankWhitespace(input);
		CharResult separator = Parser::parseCharacter(input,',');
		if (!separator.has_value()) {
			break;
		}
		input = separator.value().second;
		temp = JsonParser::parse(input);
	}
	input = Parser::yankWhitespace(input);
	CharResult closeBracket = Parser::parseCharacter(input,']');
	if (!closeBracket.has_value()) {
		std::cout << "closing bracket expected" << std::endl;
		return {};
	}
	input = closeBracket.value().second;
	if (!buffer.empty())
		return std::make_pair(new JsonArray(buffer),input);
	std::cout << "empty array" << std::endl;
	return {};
}
