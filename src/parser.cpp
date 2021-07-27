#include "parser.h"

std::string Parser::u32_to_ascii(std::u32string const &s) {
	std::string out;
	std::transform(begin(s), end(s), back_inserter(out), [](char32_t c) {
		return c < 128 ? static_cast<char>(c) : '?';
	});
	return out;
}

int Parser::u32toi(std::u32string const &s) { return std::stoi(u32_to_ascii(s)); }
float Parser::u32tof(std::u32string const &s) { return std::stof(u32_to_ascii(s)); }

CharResult Parser::parseCharacter(std::u32string::iterator input, char ref) {
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
	std::list<char> except = {'\"','<','>','\0'};
	while (std::find(except.begin(),except.end(),*input) != except.end()) {
		buffer.append(sizeof(char),*input);
		++input;
	}
	if (!buffer.empty())
		std::make_pair(buffer,input);
	else
		return std::nullopt;
}

CharResult Parser::parseDigit(std::u32string::iterator input) {
	std::list<char> chars = {'1','2','3','4','5','6','7','8','9','0'};
	if (std::find(chars.begin(),chars.end(),*input) != chars.end()) {
		char res = *input;
		return std::make_pair(res,++input);
	} else { 
		return {};
	}
}

CharResult Parser::parseWhitespace(std::u32string::iterator input) {
	const char chars[] = {'\t','\n',' '};
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
		return std::make_pair(' ',input);
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
	CharResult tmp = parseDigit(input);
	while (tmp.has_value()) {
		buffer.append(sizeof(char),tmp.value().first);
		input = tmp.value().second;
		tmp = parseDigit(input);
	}
	tmp = parseCharacter(input,'.');
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
