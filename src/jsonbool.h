#ifndef JSON_BOOL_H
#define JSON_BOOL_H

#include "jsonsymbol.h"
#include "parser.h"

class JsonBool : public JsonSymbol {
private:
	bool value;
public:
	JsonBool();
	JsonBool(bool _value);

	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_BOOL_H
