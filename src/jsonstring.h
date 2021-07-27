#ifndef JSON_STRING_H
#define JSON_STRING_H

#include "jsonsymbol.h"
#include "parser.h"

class JsonString : public JsonSymbol {
private:
	std::u32string value;
public:
	virtual JsonResult parse(std::u32string::iterator input) override;
};
#endif //JSON_STRING_H
