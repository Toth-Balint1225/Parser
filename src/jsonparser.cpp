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
	parsers.push_back(new JsonString);
	parsers.push_back(new JsonArray);
	parsers.push_back(new JsonObject);
}

JsonParser::~JsonParser() {
	// NOTE important dynamic data
	for (auto& it : parsers) {
		delete it;
	}
}

template <typename T>
bool JsonParser::impl_accept() {
	if (typeid(T) == typeid(*next)) {
		step();
		return true;
	} else {
		return false;
	}
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

template <typename T>
bool JsonParser::impl_expect() {
	return false;
}

JsonResult JsonParser::impl_parse(std::u32string::iterator input) {
	for (auto p : parsers) {
		JsonResult temp = p->parse(input);
		if (temp.has_value())
			return temp;
	}
	return std::nullopt;
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

template <typename T>
bool JsonParser::accept() {
	return getInstance().impl_accept<T>();
}

void JsonParser::step() {
	return getInstance().impl_step();
}

template <typename T>
bool JsonParser::expect() {
	return getInstance().impl_expect<T>();
}

JsonResult JsonParser::parse(std::u32string::iterator input) {
	return getInstance().impl_parse(input);
}

void JsonParser::setSource(const std::u32string& _source) {
	getInstance().impl_setSource(_source);
}
