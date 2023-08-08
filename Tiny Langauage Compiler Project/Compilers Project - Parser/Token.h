#ifndef __TOKEN__
#define __TOKEN__

#include <fstream>
#include <unordered_map>

#define RESERVED_KEYWORDS_COUNT 8

namespace ParserApp {

	enum class TokenType {
		/* tokens related to file reading */
		END_FILE, ERR,

		/* reserved words */
		IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,

		/* multichars tokens */
		ID, NUM,

		/* special symbols */
		PLUS, MINUS, TIMES, DIV, EQ, LT, L_PAREN, R_PAREN, SEMICOLON, ASSIGN
	};

	const std::unordered_map<std::string, TokenType> reservedKeywords = {
		{"if", TokenType::IF},
		{"then", TokenType::THEN},
		{"else", TokenType::ELSE},
		{"end", TokenType::END},
		{"repeat", TokenType::REPEAT},
		{"until", TokenType::UNTIL},
		{"read", TokenType::READ},
		{"write", TokenType::WRITE}
	};

	const std::unordered_map<std::string, TokenType> specialSymbols = {
		{"+", TokenType::PLUS},
		{"-", TokenType::MINUS},
		{"*", TokenType::TIMES},
		{"/", TokenType::DIV},
		{"=", TokenType::EQ},
		{"<", TokenType::LT},
		{"(", TokenType::L_PAREN},
		{")", TokenType::R_PAREN},
		{";", TokenType::SEMICOLON},
		{":=", TokenType::ASSIGN}
	};

	const std::unordered_map<TokenType, std::string> reservedKeywordsEnumStr = {
		{TokenType::IF, "IF"},
		{TokenType::THEN, "THEN"},
		{TokenType::ELSE, "ELSE"},
		{TokenType::END, "END"},
		{TokenType::REPEAT, "REPEAT"},
		{TokenType::UNTIL, "UNTIL"},
		{TokenType::READ, "READ"},
		{TokenType::WRITE, "WRITE"},
	};

	const std::unordered_map<TokenType, std::string> specialSymbolsEnumStr = {
		{TokenType::PLUS, "PLUS"},
		{TokenType::MINUS, "MINUS"},
		{TokenType::TIMES, "TIMES"},
		{TokenType::DIV, "DIV"},
		{TokenType::EQ, "EQ"},
		{TokenType::LT, "LT"},
		{TokenType::L_PAREN, "L_PAREN"},
		{TokenType::R_PAREN, "R_PAREN"},
		{TokenType::SEMICOLON, "SEMICOLON"},
		{TokenType::ASSIGN, "ASSIGN"}
	};

	class Token
	{
	private:
		TokenType tokenType;
		std::string tokenStr;

	public:
		Token();
		Token(TokenType tokenType, std::string tokenStr);

		/* Copy Constructor */
		Token(const Token& token) = default;

		/* Move Constructor */
		Token(Token&& token) noexcept = default;

		/* assignment operator overloading */
		Token& operator=(Token&& token) = default;

		TokenType getTokenType() const;
		void setTokenType(const TokenType& tokenType);
		std::string getTokenTypeStr() const;

		std::string getTokenStr() const;
		void setTokenStr(const std::string& tokenStr);

		std::string toString() const;

		static TokenType getReservedKeyword(const std::string& tokenStr);

		static bool isReservedKeyword(const std::string& tokenStr);

		static bool isSpecialSymbol(const std::string& tokenStr);
	};
}

#endif /* __TOKEN__ */
