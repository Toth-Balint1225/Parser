#ifndef UTF8PRINTER_H
#define UTF8PRINTER_H

#include <ostream>

class Utf8Printer {
public:
	static char* char_utf32_to_utf8(char32_t utf32, const char* buffer);
	friend std::ostream& operator<<(std::ostream& os, const char32_t* s);
	friend std::ostream& operator<<(std::ostream& os, const std::u32string& s);
};

#endif //UTF8PRINTER_H
