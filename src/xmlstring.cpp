#include "xmlstring.h"

XmlString::XmlString() {

}

XmlString::~XmlString() {
}

XmlResult XmlString::parse(std::u32string::iterator input) {
	input = Parser::yankWhitespace(input);
	StringResult temp = Parser::parseString(input);
	return {};
}
