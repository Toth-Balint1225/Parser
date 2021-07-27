#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <list>

#include "jsonsymbol.h"
#include "parser.h"
#include "jsonparser.h"

/**
 * JsonArray:
 * represents the array-list data structure of json
 * implements JsonSymbol
 * */
class JsonArray : public JsonSymbol {
private:
	/* uses a list to store any kind of JsonSymbol */
	std::list<JsonSymbol*> contents;
public:
	/* default empty constructor */
	JsonArray() = default;

	/* overloaded constructor that takes a list of JsonSymbols */
	JsonArray(const std::list<JsonSymbol*>& _contents);

	/* destroys the data stored in the list */
	~JsonArray();

	/* interface method */
	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_ARRAY_H
