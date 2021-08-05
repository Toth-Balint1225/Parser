#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <list>

#include "xmlsymbol.h"
#include "xmlstring.h"

/**
 * XmlParser: parses xml objects
 * uses prototype factory and singleton design patterns
 * */
class XmlParser {
private:
	std::list<XmlSymbol*> parsers;
private:
	/* initialize prototypes */
	void setupParsers();
	XmlParser();
	
	/* implementation of the parse static method */
	XmlResult impl_parse(std::u32string::iterator input);
public:
	/* deleted public constructor */
	XmlParser(const XmlParser&) = delete;
	~XmlParser();

	/* singlethon pattern's function */
	static XmlParser& getInstance();

	/* multifunctional parsing function, uses the prototypes */
	static XmlResult parse(std::u32string::iterator input);
};

#endif //XMLPARSER_H
