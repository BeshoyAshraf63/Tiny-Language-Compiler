#ifndef __SCANNER__
#define __SCANNER__

#include <iostream>
#include <string>
#include "Token.h"


namespace ParserApp {
	enum class ScannerState {
		START, IN_NUM, IN_ID, IN_ASSIGN, IN_COMMENT, DONE
	};

	class Scanner
	{
	private:
		std::string programString;
		size_t cursor = 0;
		size_t currentLine = 1;
		size_t previousCursor = 0;
		static Scanner* instance;


		Scanner() = default;

		static bool isWhiteSpace(const char c);
		static bool isDigit(const char c);
		static bool isLetter(const char c);

	public:
		static Scanner* getInstance();

		std::string getProgramString() const;

		size_t getCurrentLine() const;

		void setProgramString(std::string programString);

		void reset();

		void moveCursorBack();

		Token getNextToken();
	};

}
#endif /* __SCANNER__ */

