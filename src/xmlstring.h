#ifndef XMLSTRING_H
#define XMLSTRING_H

#include "parser.h"
#include "xmlsymbol.h"

class XmlString : public XmlSymbol {
private:
	std::string value;
public:
	XmlString();
	~XmlString();
public:
	virtual XmlResult parse(std::u32string::iterator input) override;
};

#endif //XMLSTRING_H
