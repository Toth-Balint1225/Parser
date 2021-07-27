#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <map>

#include "jsonsymbol.h"
#include "parser.h"

class JsonObject : public JsonSymbol {
private:
	std::map<std::u32string,JsonSymbol*> contents; 
public:
	~JsonObject();

	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_OBJECT_H
