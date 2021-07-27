#ifndef JSON_FLOAT_H
#define JSON_FLOAT_H

#include "jsonsymbol.h"
#include "parser.h"

/**
 * JsonFloat: represents a floating point numeric literal
 * implements JsonSymbol
 * floating point number: {decimal}"."{decimal}
 * uses Parser::parseFloat
 * */
class JsonFloat : public JsonSymbol {
private:
	/* inner value */
	float value;
public:
	/* default constructor: sets value to 0.0f */
	JsonFloat();

	/* setter constructor: sets the value upon construction */
	JsonFloat(float _value);

	/* JsonSymbol implementation */
	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_FLOAT_H
