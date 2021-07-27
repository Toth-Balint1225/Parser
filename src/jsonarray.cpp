#include "jsonarray.h"

JsonArray::JsonArray(const std::list<JsonSymbol*>& _contents) {
	for (auto s : _contents)
		contents.push_back(s);
}

JsonArray::~JsonArray() {
	// NOTE important dynamic data
	for (auto& it : contents) {
		delete it;
	}
}

JsonResult JsonArray::parse(std::u32string::iterator input) {
	// clear whitespaces
	input = Parser::yankWhitespace(input);
	
	// requires [ character
	CharResult openBracket = Parser::parseCharacter(input,'[');
	if (!openBracket.has_value()) {
		return {};
	}
	// step input stream
	input = openBracket.value().second;
	std::list<JsonSymbol*> buffer;
	JsonResult temp = JsonParser::parse(input);
	// reading in tokens
	while (temp.has_value()) {
		buffer.push_back(temp.value().first);
		input = temp.value().second;
		// clear whitespaces
		input = Parser::yankWhitespace(input);
		// requires separator
		CharResult separator = Parser::parseCharacter(input,',');
		if (!separator.has_value()) {
			break;
		}
		// step input stream
		input = separator.value().second;
		temp = JsonParser::parse(input);
	}
	input = Parser::yankWhitespace(input);
	// clear whitespaces
	CharResult closeBracket = Parser::parseCharacter(input,']');
	if (!closeBracket.has_value()) {
		return {};
	}
	// requires ] character
	input = closeBracket.value().second;

	// return conditions checking
	if (!buffer.empty())
		return std::make_pair(new JsonArray(buffer),input);
	return {};
}
