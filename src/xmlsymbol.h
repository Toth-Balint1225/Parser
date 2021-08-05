#ifndef XMLSYMBOL_H
#define XMLSYMBOL_H

#include <string>
#include <optional>

/*
=xml=
meta  ::= "<?" {literal "=" '"' literal '"'} "?>"
tag   ::= "<" literal [literal "=" '"' literal '"'] ">" value "</" literal ">"
value ::= literal
        | tag
        ;
*/

/**
 * Standard return type for the xml interface
 * */
class XmlSymbol;
typedef std::optional<std::pair<XmlSymbol*,std::u32string::iterator>> XmlResult;

/**
 * Interface XmlSymbol
 * sets the shared behaviour of xml data structures via the parse function
 * */
class XmlSymbol {
public:
	virtual XmlResult parse(std::u32string::iterator input) = 0;
};

#endif //XMLSYMBOL_H
