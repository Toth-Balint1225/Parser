#ifndef JSON_STRING_H
#define JSON_STRING_H

#include "jsonsymbol.h"
#include "parser.h"

/**
 * JsonString: a duble-quoted literal, can contain alphanumerics
 * */
class JsonString : public JsonSymbol {
private:
	std::u32string value;
public:
	/* default useless constructor */
	JsonString() = default;

	/* value setter constructor */
	JsonString(const std::u32string& _value);

	/* interface implementation */
	virtual JsonResult parse(std::u32string::iterator input) override;
};
#endif //JSON_STRING_H
