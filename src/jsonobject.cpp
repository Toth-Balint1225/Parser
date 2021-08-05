#include "jsonobject.h"

#include <iostream>
JsonObject::JsonObject(const std::map<std::u32string,JsonSymbol*> _contents) {
	for (auto it : _contents) {
		contents.emplace(it);
	}
}

JsonObject::~JsonObject() {
	// NOTE important dynamic data
	for (auto& it : contents) {
		delete it.second;
	}
}	

StringResult JsonObject::parseKey(std::u32string::iterator input) {
	// clear whitespace
	input = Parser::yankWhitespace(input);
	// expects "
	CharResult openQuote = Parser::parseCharacter(input,U'\"');
	if (!openQuote.has_value()) {
		std::cout << "opening quote expected" << std::endl;
		return std::nullopt;
	}
	input = openQuote.value().second;
	// expects string
	StringResult buffer = Parser::parseString(input);
	if (!buffer.has_value()) {
		std::cout << "string expected" << std::endl;
		return std::nullopt;
	}
	input = buffer.value().second;
	// expects "
	CharResult closeQuote = Parser::parseCharacter(input,U'\"');
	if (!closeQuote.has_value()) {
		std::cout << "closing quote expected" << std::endl;
		return std::nullopt;
	}
	input = closeQuote.value().second;
	return std::make_pair(buffer.value().first,input);
}

PairResult JsonObject::parseKeyValue(std::u32string::iterator input) {
	// clear whitespace
	input = Parser::yankWhitespace(input);
	// expects key
	StringResult key = parseKey(input);
	if (!key.has_value()) {
		std::cout << "key expected" << std::endl;
		return std::nullopt;
	}
	input = key.value().second;
	// expects :
	input = Parser::yankWhitespace(input);
	CharResult colon = Parser::parseCharacter(input,U':');
	if (!colon.has_value()) {
		std::cout << "colon expected" << std::endl;
		return std::nullopt;
	}
	input = colon.value().second;
	// expects value
	JsonResult buffer = JsonParser::parse(input);
	if (!buffer.has_value()) {
		std::cout << "value expected" << std::endl;
		return std::nullopt;
	}
	input = buffer.value().second;
	return std::make_pair(std::make_pair(
				key.value().first,buffer.value().first)
			    ,input);
}

JsonResult JsonObject::parse(std::u32string::iterator input) {
	// clear whitespaces
	input = Parser::yankWhitespace(input);
	std::map<std::u32string,JsonSymbol*> buffer;
	// expects {
	CharResult openBrace = Parser::parseCharacter(input,U'{');
	if (!openBrace.has_value()) {
		std::cout << "open brace expected" << std::endl;
		return std::nullopt;
	}
	input = openBrace.value().second;

	// expects key : value
	PairResult temp = parseKeyValue(input);
	while (temp.has_value()) {
		buffer.emplace(temp.value().first);
		input = temp.value().second;
		// clear whitespaces
		input = Parser::yankWhitespace(input);

		// expects ,
		CharResult sep = Parser::parseCharacter(input,U',');
		if (!sep.has_value()) {
			break;
		}

		// step
		input = sep.value().second;
		temp = parseKeyValue(input);
	}
	
	// expects }
	input = Parser::yankWhitespace(input);
	CharResult closeBrace = Parser::parseCharacter(input,U'}');
	if (!closeBrace.has_value()) {
		std::cout << "closing brace expected" << std::endl;
		return std::nullopt;
	}
	input = closeBrace.value().second;
	if (!buffer.empty()) {
		return std::make_pair(new JsonObject(buffer),input);
	} else {
		return std::nullopt;
	}
}
