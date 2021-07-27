#ifndef JSON_NULL_H
#define JSON_NULL_H

#include "jsonsymbol.h"
#include "parser.h"

class JsonNull : public JsonSymbol {
public:
	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_NULL_H
