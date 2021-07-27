#include "jsonparser.h"

JsonParser::JsonParser(): source(U""), next(nullptr) {
	setupParsers();
}

JsonParser::JsonParser(const std::u32string& _source): 
		source(_source), next(nullptr) {
	setupParsers();
	position = source.begin();
}

void JsonParser::setupParsers() {
	/* PARSER PROTOTYPES */
	parsers.push_back(new JsonNull);
	parsers.push_back(new JsonBool);
	parsers.push_back(new JsonFloat);
	parsers.push_back(new JsonInt);
	parsers.push_back(new JsonArray);
}

JsonParser::~JsonParser() {
	// NOTE important dynamic data
	for (auto& it : parsers) {
		delete it;
	}
}

bool JsonParser::impl_accept(JsonSymbol* s) {
	return false;
}

void JsonParser::impl_step() {
	for (auto p : parsers) {
		JsonResult temp = p->parse(position);
		if (temp.has_value()) {
			next = temp.value().first;
			position = temp.value().second;
			return;
		}
	}
}

JsonResult JsonParser::impl_parse(std::u32string::iterator input) {
	for (auto p : parsers) {
		JsonResult temp = p->parse(input);
		if (temp.has_value())
			return temp;
	}
	return {};
}
void JsonParser::impl_setSource(const std::u32string& _source) {
	source = _source;
	position = source.begin();
}

JsonParser& JsonParser::getInstance() {
	// creation of one static instance for the whole global namespace
	static JsonParser instance;
	return instance;
}

bool JsonParser::accept(JsonSymbol* s) {
	return getInstance().impl_accept(s);
}

void JsonParser::step() {
	return getInstance().impl_step();
}

JsonResult JsonParser::parse(std::u32string::iterator input) {
	return getInstance().impl_parse(input);
}

void JsonParser::setSource(const std::u32string& _source) {
	getInstance().impl_setSource(_source);
}
