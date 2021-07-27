#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <list>

#include "jsonsymbol.h"
#include "jsonnull.h"
#include "jsonbool.h"
#include "jsonint.h"
#include "jsonfloat.h"
#include "jsonarray.h"

// tactically a singleton class
class JsonParser {
private:
	std::u32string source;
	std::u32string::iterator position;
	std::list<JsonSymbol*> parsers;
	JsonSymbol* next;

	void setupParsers();

	JsonParser();
	JsonParser(const std::u32string& _source);
	~JsonParser();
	bool impl_accept(JsonSymbol* s);
	void impl_step();
	JsonResult impl_parse(std::u32string::iterator input);
	void impl_setSource(const std::u32string& _source);
public:
	JsonParser(const JsonParser&) = delete; 
	static JsonParser& getInstance();
	static bool accept(JsonSymbol *s);
	static void step();
	static JsonResult parse(std::u32string::iterator input);
	static void setSource(const std::u32string& _source);
};

#endif //JSON_PARSER_H
