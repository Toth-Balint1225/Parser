#include "xmlparser.h"

XmlParser::XmlParser() {
	setupParsers();
}

XmlParser::~XmlParser() {
	// NOTE: imortant dynamic data
	for (auto& p : parsers) {
		delete p;
	}
}

void XmlParser::setupParsers() {
	parsers.push_back(new XmlString);
}

XmlResult XmlParser::impl_parse(std::u32string::iterator input) {
	return std::nullopt;
}

XmlParser& XmlParser::getInstance() {
	static XmlParser instance;
	return instance;
}

XmlResult XmlParser::parse(std::u32string::iterator input) {
	return getInstance().impl_parse(input);
}
