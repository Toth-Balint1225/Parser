#ifndef XMLSTRING_H
#define XMLSTRING_H

#include "parser.h"
#include "xmlsymbol.h"

/**
 * XmlString: represents an unquoted string literal
 * parsed using the parseString method
 * */
class XmlString : public XmlSymbol {
private:
	/* inner value of UTF-32 string */
	std::u32string value;
public:
	/* default constructor */
	XmlString();

	/* value setter constructor */
	XmlString(const std::u32string& _value);

	/* default destructor */
	~XmlString();
public:
	/* interface method implementation */
	virtual XmlResult parse(std::u32string::iterator input) override;
};

#endif //XMLSTRING_H
