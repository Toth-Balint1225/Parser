#include "xmlstring.h"

XmlString::XmlString() {
}

XmlString::XmlString(const std::u32string& _value): value(_value) {
}

XmlString::~XmlString() {
}

XmlResult XmlString::parse(std::u32string::iterator input) {
	// clear input
	input = Parser::yankWhitespace(input);
	// expects string
	// assumption: the parseString will stop at '<'
	StringResult temp = Parser::parseString(input); 
	// value check
	if (temp.has_value()) {
		input = temp.value().second;
		return std::make_pair(new XmlString(temp.value().first),input);
	} else {
		return std::nullopt;
	}
}
