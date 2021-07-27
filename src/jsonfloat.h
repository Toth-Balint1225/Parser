#ifndef JSON_FLOAT_H
#define JSON_FLOAT_H

#include "jsonsymbol.h"
#include "parser.h"

class JsonFloat : public JsonSymbol {
private:
	float value;
public:
	JsonFloat();
	JsonFloat(float _value);

	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_FLOAT_H
