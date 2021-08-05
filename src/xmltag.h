#ifndef XMLTAG_H
#define XMLTAG_H

#include <list>

#include "parser.h"
#include "xmlsymbol.h"

class XmlTag : public XmlSymbol {
private:
	std::u32string identifier;
	std::list<XmlSymbol*> contents;
public:
	XmlTag();
	~XmlTag();
	virtual XmlResult parse(std::u32string::iterator input) override;
};

#endif //XMLTAG_H
