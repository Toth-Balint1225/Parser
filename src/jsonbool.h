#ifndef JSON_BOOL_H
#define JSON_BOOL_H

#include "jsonsymbol.h"
#include "parser.h"

/**
 * JsonBool: represents a boolean 
 * implements JsonSymbol
 * since a boolean can only be true or false, it accepts only these 2 values
 * */
class JsonBool : public JsonSymbol {
private:
	/* the inner boolean */
	bool value;
public:
	/* default constructor: sets the value to false */
	JsonBool();

	/* value-setter constructor */
	JsonBool(bool _value);

	/* implmentation of the JsonSymbol interface */
	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_BOOL_H
