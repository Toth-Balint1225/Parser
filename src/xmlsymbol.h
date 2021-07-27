#ifndef XMLSYMBOL_H
#define XMLSYMBOL_H

#include <string>
#include <optional>

class XmlSymbol;
typedef std::optional<std::pair<XmlSymbol*,std::u32string::iterator>> XmlResult;

class XmlSymbol {
public:
	virtual XmlResult parse(std::u32string::iterator input) = 0;
};

#endif //XMLSYMBOL_H
