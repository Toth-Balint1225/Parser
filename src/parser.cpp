#include "parser.h"

// private functions -----------------------------------------------------
std::string Parser::u32_to_ascii(std::u32string const &s) {
	std::string out;
	std::transform(begin(s), end(s), back_inserter(out), [](char32_t c) {
		return c < 128 ? static_cast<char>(c) : '?';
	});
	return out;
}

int Parser::u32toi(std::u32string const &s) { return std::stoi(u32_to_ascii(s)); }
float Parser::u32tof(std::u32string const &s) { return std::stof(u32_to_ascii(s)); }

// public functions ------------------------------------------------------

CharResult Parser::parseCharacter(std::u32string::iterator input, char32_t ref) {
	if (ref == *input) {
		return std::make_pair(ref,++input);
	} else {
		return {};
	}
}

StringResult Parser::parseString(std::u32string::iterator input, const std::u32string& ref) {
	for (auto it : ref) {
		CharResult tmp = parseCharacter(input,it);
		if (!tmp.has_value())
			return {};
		input = tmp.value().second;
	}
	return std::make_pair(ref,input);
}


StringResult Parser::parseString(std::u32string::iterator input) {
	std::u32string buffer = U"";
	// non-string characters defined here
	std::list<char32_t> except = {U'\"',U'<',U'>',U'\0'};
	while (std::find(except.begin(),except.end(),*input) == except.end()) {
		buffer.append(sizeof(char32_t),*input);
		++input;
	}
	if (!buffer.empty())
		return std::make_pair(buffer,input);
	else
		return std::nullopt;
}

CharResult Parser::parseDigit(std::u32string::iterator input) {
	// decimal digit characters defined here
	std::list<char32_t> chars = {U'1',U'2',U'3',U'4',U'5',U'6',U'7',U'8',U'9',U'0'};
	if (std::find(chars.begin(),chars.end(),*input) != chars.end()) {
		char32_t res = *input;
		return std::make_pair(res,++input);
	} else { 
		return {};
	}
}

CharResult Parser::parseWhitespace(std::u32string::iterator input) {
	// whitespace characters defined here
	// TODO refactor to use stl
	const char32_t chars[] = {U'\t',U'\n',U' '};
	bool whitespace = false;
	bool character = false;
	do {
		character = false;
		for (auto it : chars) {
			if (*input == it) {
				++input;
				character = true;
				break;
			}
		}
		if (character)
			whitespace = true;
	} while (character);
	if (whitespace) 
		return std::make_pair(U' ',input);
	else
		return {};
}

IntResult Parser::parseInt(std::u32string::iterator input) {
	std::u32string buffer = U"";
	CharResult tmp = parseDigit(input);
	while (tmp.has_value()) {
		buffer.append(sizeof(char),tmp.value().first);
		input = tmp.value().second;
		tmp = parseDigit(input);
	}
	if (!buffer.empty()) {
		return std::make_pair(u32toi(buffer),input);
	} else {
		return {};
	}
}

FloatResult Parser::parseFloat(std::u32string::iterator input) {
	std::u32string buffer = U"";
	// number checking
	CharResult tmp = parseDigit(input);
	while (tmp.has_value()) {
		buffer.append(sizeof(char),tmp.value().first);
		input = tmp.value().second;
		tmp = parseDigit(input);
	}
	// decimal dot checking
	tmp = parseCharacter(input,U'.');
	if (!tmp.has_value())
		return {};
	
	while (tmp.has_value()) {
		buffer.append(sizeof(char),tmp.value().first);
		input = tmp.value().second;
		tmp = parseDigit(input);
	}

	if (!buffer.empty())
		return std::make_pair(u32tof(buffer),input);
	else
		return {};
}

std::u32string::iterator Parser::yankWhitespace(std::u32string::iterator input) {
	CharResult tmp = parseWhitespace(input);
	if (tmp.has_value())
		return tmp.value().second;
	else
		return input;
}
