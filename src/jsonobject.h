#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <map>

#include "jsonsymbol.h"
#include "parser.h"
#include "jsonparser.h"

#include "jsonstring.h"

/**
 * Return type for a string : JsonSymbol pair
 * */
typedef std::optional<
	std::pair<std::pair<std::u32string,JsonSymbol*>
	,std::u32string::iterator>> 
PairResult;

/**
 * JsonObject: high level data structure, can store other objects
 * in key : value pairs
 * */
class JsonObject : public JsonSymbol {
private:
	/* inner value, the key has to be a quoted string */
	std::map<std::u32string,JsonSymbol*> contents; 

	PairResult parseKeyValue(std::u32string::iterator input);
public:
	JsonObject() = default;
	JsonObject(const std::map<std::u32string,JsonSymbol*> _contents);
	~JsonObject();

	virtual JsonResult parse(std::u32string::iterator input) override;
};

#endif //JSON_OBJECT_H
