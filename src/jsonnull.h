#ifndef JSON_NULL_H
#define JSON_NULL_H

#include "jsonsymbol.h"
#include "parser.h"

/**
 * JsonNull:
 * represents a null value for json
 * does not contain any data
 * implements JsonSymbol
 * */
class JsonNull : public JsonSymbol {
public:
	/* JsonSymbol implementation */
	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_NULL_H
