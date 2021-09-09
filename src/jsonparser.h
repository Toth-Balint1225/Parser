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
#include "jsonstring.h"
#include "jsonobject.h"

/**
 * JsonParser:
 * a parser class for the JsonSymbol interface
 * uses the recursive descent parser as the underlying wisdom
 * follows the Singleton and the Factory design pattern
 * stores:
 * 	o the source string
 * 	o the current position in the source
 * 	o a list of parser prototypes
 * 	o the next token prepared
* */
class JsonParser {
/* Private data */
private: 
	/* source code (optional) */
	std::u32string source;
	/* the current position in the string */
	std::u32string::iterator position;
	/* the prototypes for the parsers */
	std::list<JsonSymbol*> parsers;
	/* the next token */
	JsonSymbol* next;

/* Private  constructors and setup functions (Singleton) */
private:
	/* sets the prototypes to be used */
	void setupParsers();
	JsonParser();
	JsonParser(const std::u32string& _source);
	~JsonParser();

/* Private API implementations */
private:
	/* typecheck for the next token */
	template <typename T>
	bool impl_accept();
	/* read in the next token from the string and update the position */
	void impl_step();

	template <typename T>
	bool impl_expect();

	/* multi-purpose helper function, technically enough for the whole class 
	 * Factory method
	 * */
	JsonResult impl_parse(std::u32string::iterator input);
	/* sets the source and resets the position and next */
	void impl_setSource(const std::u32string& _source);

/* Public API functions for end user code */
public:
	/* disables the construction of any other instances */
	JsonParser(const JsonParser&) = delete; 
	/* instantiation function (Singleton) */
	static JsonParser& getInstance();
	template <typename T>
	static bool accept();
	static void step();
	template <typename T>
	static bool expect();
	static JsonResult parse(std::u32string::iterator input);
	static void setSource(const std::u32string& _source);
};

#endif //JSON_PARSER_H
