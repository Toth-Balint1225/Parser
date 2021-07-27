#ifndef JSON_INT_H
#define JSON_INT_H

#include "jsonsymbol.h"
#include "parser.h"

class JsonInt : public JsonSymbol {
private:
	int value;
public:
	JsonInt();
	JsonInt(int _value);

	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_INT_H
