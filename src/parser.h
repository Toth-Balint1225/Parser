#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <optional>
#include <list>
#include <algorithm>

typedef std::optional<std::pair<char,std::u32string::iterator>> CharResult;
typedef std::optional<std::pair<std::u32string,std::u32string::iterator>> StringResult;
typedef std::optional<std::pair<int,std::u32string::iterator>> IntResult;
typedef std::optional<std::pair<float,std::u32string::iterator>> FloatResult;

class Parser {
private:
	static std::string u32_to_ascii(std::u32string const &s);
	static int u32toi(std::u32string const &s);
	static float u32tof(std::u32string const &s);
public:
	static CharResult parseCharacter(std::u32string::iterator input, char ref);
	static StringResult parseString(std::u32string::iterator input, const std::u32string& ref);
	static StringResult parseString(std::u32string::iterator input);
	static CharResult parseDigit(std::u32string::iterator input);
	static CharResult parseWhitespace(std::u32string::iterator input);
	static IntResult parseInt(std::u32string::iterator input);
	static FloatResult parseFloat(std::u32string::iterator input);
	static std::u32string::iterator yankWhitespace(std::u32string::iterator input);
};

#endif //PARSER_H
