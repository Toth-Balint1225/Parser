#ifndef JSON_INT_H
#define JSON_INT_H

#include "jsonsymbol.h"
#include "parser.h"

/**
 * JsonInt:
 * stores an integer numeric literal
 * implements JsonSymbol
 * uses Parser
 * */
class JsonInt : public JsonSymbol {
private:
	/* inner value is stored as int */
	int value;
public:
	/* default constructor: sets inner value to 0 */
	JsonInt();

	/* setter constructor */
	JsonInt(int _value);

	/* JsonSymbol implementation */
	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_INT_H
