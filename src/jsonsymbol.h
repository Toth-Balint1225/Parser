#ifndef JSON_SYMBOL_H
#define JSON_SYMBOL_H

#include <string>
#include <optional>
/**
=json=

object ::= "{" '"' literal '"' ":" symbol {"," '"' literal '"' ":" symbol} "}"
         ;

array  ::= "[" symbol {"," symbol} "]"
         ;

symbol ::= null
         | bool
		 | number
		 | u32string
		 | array 
		 | object
         ;

*/


/** 
 * Result type
 * every Json parsing components has to return the Json result type
 * */
class JsonSymbol;
typedef std::optional<std::pair<JsonSymbol*,std::u32string::iterator>> JsonResult;

/**
 * JsonSymbol interface
 * defines the parse function of each json token
 * every Json object shall implement the JsonSymbol interface
 *
 * convention:
 * every parse function has to clear whitespaces at start
 * */
class JsonSymbol {
public:
	/* expects an iterator to the input string and returns a Json object, or nullopt */
	virtual JsonResult parse(std::u32string::iterator input) = 0;
};

#endif //JSON_SYMBOL_H
