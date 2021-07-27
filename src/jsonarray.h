#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <list>

#include "jsonsymbol.h"
#include "parser.h"
#include "jsonparser.h"

class JsonArray : public JsonSymbol {
private:
	std::list<JsonSymbol*> contents;
public:
	JsonArray() = default;
	JsonArray(const std::list<JsonSymbol*>& _contents);
	~JsonArray();

	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_ARRAY_H
