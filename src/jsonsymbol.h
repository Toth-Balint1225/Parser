#ifndef JSON_SYMBOL_H
#define JSON_SYMBOL_H

#include <string>
#include <optional>

class JsonSymbol;
typedef std::optional<std::pair<JsonSymbol*,std::u32string::iterator>> JsonResult;

class JsonSymbol {
public:
	virtual JsonResult parse(std::u32string::iterator input) = 0;
};

#endif //JSON_SYMBOL_H
