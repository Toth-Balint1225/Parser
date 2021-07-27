#ifndef XMLTAG_H
#define XMLTAG_H

#include "parser.h"
#include "xmlsymbol.h"

class XmlTag : public XmlSymbol {
public:
	XmlTag();
	~XmlTag();
	virtual XmlResult parse(std::u32string::iterator input) override;
};

#endif //XMLTAG_H
