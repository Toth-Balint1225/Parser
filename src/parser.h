#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <optional>
#include <list>
#include <algorithm>

/**
 * Return types: the whole program uses type aliases for the complicated return types
 * convention: 
 * 	o a result is an optional of a pair
 * 	o the pair's second is always a std::u32string::iterator
 * 	o the name always looks like: TypeResult, where Type is the type of the pair's first
 *
 * the optional takes care of faulty inputs and errors during parsing
 * */

/* return type for UTF-32 characters */
typedef std::optional<std::pair<char32_t,std::u32string::iterator>> CharResult;
/* return type for UTF-32 strings */
typedef std::optional<std::pair<std::u32string,std::u32string::iterator>> StringResult;
/* return type for ints */
typedef std::optional<std::pair<int,std::u32string::iterator>> IntResult;
/* return type for floats */
typedef std::optional<std::pair<float,std::u32string::iterator>> FloatResult;

/**
 * Parser: universal parsing functions packed in a class
 * these functions are implemented as static member functions
 * */
class Parser {
/* private helper functions stolen from stackOverflow
 * */
private:
	/* converst UTF-32 strings to std::string */
	static std::string u32_to_ascii(std::u32string const &s);

	/* converst UTF-32 strings to floating point numerals */
	static int u32toi(std::u32string const &s);

	/* converst UTF-32 strings to floating point numerals */
	static float u32tof(std::u32string const &s);
/* API functions
 * implements the basic parser components and some high order, but 
 * common and simple parsers that can be used in other high order parsers
 *
 * convention:
 * 	o every parsing function returns some Result type (discussed above)
 * 	o every parsing function's name starts with parse, followed by the type it parses (the Result's type)
 * 	o every parsing function takes a UTF-32 iterator as minimal input
 *
 * TODO exceptions testing
 * TODO responsive and informative error system for the user
 * */
public:
	/* parses 1 character
	 * if the input's first character is ref, then returns the character and the unconsumed input
	 * otherwise returns nullopt
	 * */
	static CharResult parseCharacter(std::u32string::iterator input, char32_t ref);

	/* parses a string to a reference
	 * if the input starts with ref, then returns the reference string
	 * otherwise returns nullopt
	 * */
	static StringResult parseString(std::u32string::iterator input, const std::u32string& ref);

	/* parses a string
	 * parses the input stream until it finds a non-string character
	 * non string characters: \0, " ' < >
	 * */
	static StringResult parseString(std::u32string::iterator input);

	/* parses a string in " quotes
	 * requires a starting "
	 * parses the string until the next " or \0, otherwise returns nullopt
	 * */
	static StringResult parseQuotedString(std::u32string::iterator input);

	/* parses a digit
	 * if the input starts with a decimal digit, then returns it
	 * otherwise returns nullopt
	 * */
	static CharResult parseDigit(std::u32string::iterator input);

	/* parses whitespace characters and consumes the input until it finds a non-whitespace character
	 * if the input starts with a whitespace character, then it always returns a constant ' ' character
	 * */
	static CharResult parseWhitespace(std::u32string::iterator input);

	/* parses an integer
	 * parses the input until it finds a non-digit character
	 * returns the parsed number converted to int
	 * */
	static IntResult parseInt(std::u32string::iterator input);

	/* parses a floating point number
	 * parses the input as a float (with the decimal point in it) until it finds a non-digit character
	 * returns the parsed number converted to float
	 * */
	static FloatResult parseFloat(std::u32string::iterator input);

	/* public helper function
	 * consumes all the following whitespaces and returns the iterator to the next usable token
	 * */
	static std::u32string::iterator yankWhitespace(std::u32string::iterator input);
};

#endif //PARSER_H
