#ifndef JSON_STRING_H
#define JSON_STRING_H

#include "jsonsymbol.h"
#include "parser.h"

/**
 * JsonString: a duble-quoted literal, can contain alphanumerics
 * */

class JsonString : public JsonSymbol {
private:
	std::u32string value;
public:
	JsonString() = default;
	JsonString(const std::u32string& _value);
	virtual JsonResult parse(std::u32string::iterator input) override;
};
#endif //JSON_STRING_H
