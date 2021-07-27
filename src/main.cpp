/*
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

math be like
expression = ["+" | "-"] term ("+" | "-") term
term       = factor ("*" | "/") factor  
factor     = "("expression")" | number

=xml=
meta  ::= "<?" {literal "=" '"' literal '"'} "?>"
tag   ::= "<" literal [literal "=" '"' literal '"'] ">" value "</" literal ">"
value ::= literal
        | tag
        ;

needed
- symbols
- some way to get the next symbol
*/

#include <iostream>

#include "utf8printer.h"
#include "jsonparser.h"

// TODO these 2 functions need to be here, otherwise it will not compile
// find a solution
std::ostream& operator<<(std::ostream& os, const char32_t* s)
{
    const char buffer[5] {0}; // That's the famous "big-enough buffer"
    while(s && *s)
    {
		Utf8Printer::char_utf32_to_utf8(*(s++), buffer);
        os << buffer;
    }
    return os;
}


std::ostream& operator<<(std::ostream& os, const std::u32string& s)
{
    return (os << s.c_str());
}

std::ostream& operator<<(std::ostream& os, char32_t c) 
{
	const char buffer[5] {0};
	Utf8Printer::char_utf32_to_utf8(c,buffer);
	os << buffer;
	return os;
}

int main() {
	std::u32string src = U"[null, [null]]";
	JsonResult res = JsonParser::parse(src.begin());
	if (res.has_value()) {
		std::cout << "OK" << std::endl;
		JsonArray* arr = (JsonArray*)res.value().first;
		delete arr;
	} else {
		std::cout << "ERROR" << std::endl;
	}

	return 0;
}
