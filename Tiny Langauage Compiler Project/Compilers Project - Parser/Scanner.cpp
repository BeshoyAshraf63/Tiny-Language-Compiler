#include "Scanner.h"

using namespace ParserApp;

Scanner* Scanner::instance = nullptr;

Scanner* Scanner::getInstance()
{
	if (Scanner::instance == nullptr)
	{
		Scanner::instance = new Scanner();
	}
	return Scanner::instance;
}

std::string Scanner::getProgramString() const
{
	return this->programString;
}

size_t Scanner::getCurrentLine() const
{
	return currentLine;
}

void Scanner::setProgramString(std::string programString)
{
	this->programString = programString;
	this->programString += " ";
	reset();
}

void Scanner::reset()
{
	cursor = 0;
	currentLine = 1;
	previousCursor = 0;
}

void Scanner::moveCursorBack()
{
	cursor = previousCursor;
}

bool Scanner::isWhiteSpace(const char c)
{
	return (c == '\n' || c == ' ' || c == '\t');
}

bool Scanner::isDigit(const char c)
{
	return (c >= '0' && c <= '9');
}

bool Scanner::isLetter(const char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

Token Scanner::getNextToken()
{
	previousCursor = cursor;
	Token token;

	ScannerState state = ScannerState::START;
	char c;
	std::string lexeme;
	while (state != ScannerState::DONE)
	{
		if (cursor >= programString.size())
		{
			token.setTokenType(TokenType::END_FILE);
			return token;
		}
		c = programString[cursor];
		cursor++;
		bool ignoreChar = false;

		switch (state)
		{
		case ScannerState::START:

			if (isDigit(c))
				state = ScannerState::IN_NUM;
			else if (isLetter(c))
				state = ScannerState::IN_ID;
			else if (c == ':')
				state = ScannerState::IN_ASSIGN;
			else if (c == '{')
			{
				ignoreChar = true;
				state = ScannerState::IN_COMMENT;
			}
			else if (isWhiteSpace(c))
			{
				ignoreChar = true;
				state = ScannerState::START;
				if (c == '\n')
					currentLine++;
			}
			else
			{
				state = ScannerState::DONE;
				if (Token::isSpecialSymbol(std::string{ c }))
					token.setTokenType(specialSymbols.at(std::string{ c }));
				else
					token.setTokenType(TokenType::ERR);
			}
			break;
		case ScannerState::IN_NUM:
			if (!isDigit(c))
			{
				ignoreChar = true;
				state = ScannerState::DONE;
				cursor--;
				token.setTokenType(TokenType::NUM);
			}
			break;
		case ScannerState::IN_ID:
			if (!isLetter(c))
			{
				ignoreChar = true;
				state = ScannerState::DONE;
				cursor--;
				token.setTokenType(TokenType::ID);
			}
			break;
		case ScannerState::IN_ASSIGN:
			state = ScannerState::DONE;
			if (c == '=')
				token.setTokenType(TokenType::ASSIGN);
			else
			{
				ignoreChar = true;
				cursor--;
				token.setTokenType(TokenType::ERR);
			}
			break;
		case ScannerState::IN_COMMENT:
			ignoreChar = true;
			if (c == '}')
			{
				state = ScannerState::START;
			}
			else if (c == '\n')
				currentLine++;
			break;
		default:
			break;
		}
		if (!ignoreChar)
			lexeme.push_back(c);
	}
	token.setTokenStr(lexeme);
	if (token.getTokenType() == TokenType::ID)
		token.setTokenType(Token::getReservedKeyword(lexeme));

	return token;
}
