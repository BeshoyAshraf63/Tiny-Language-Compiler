#include "Token.h"

using namespace ParserApp;

Token::Token() : tokenType(TokenType::ERR), tokenStr("")
{
}

Token::Token(TokenType tokenType, std::string tokenStr) 
	: tokenType(tokenType), tokenStr(tokenStr)
{
}

TokenType Token::getTokenType() const
{
	return this->tokenType;
}

void Token::setTokenType(const TokenType& tokenType)
{
	this->tokenType = tokenType;
}

std::string Token::getTokenTypeStr() const
{
	if (reservedKeywordsEnumStr.find(this->tokenType) != reservedKeywordsEnumStr.end())
	{
		return reservedKeywordsEnumStr.at(this->tokenType);
	}
	else if (specialSymbolsEnumStr.find(this->tokenType) != specialSymbolsEnumStr.end())
	{
		return specialSymbolsEnumStr.at(this->tokenType);
	}
	return "";
}

std::string Token::getTokenStr() const
{
	return this->tokenStr;
}

void Token::setTokenStr(const std::string& tokenStr)
{
	this->tokenStr = tokenStr;
}

std::string Token::toString() const
{
	std::string out;
	out = "Token Type:\t";
	if (isReservedKeyword(this->tokenStr))
	{
		out += "Reserved Keyword (" + getTokenTypeStr() + ")";
	} 
	else if(isSpecialSymbol(this->tokenStr))
	{
		out += "Special Symbol (" + getTokenTypeStr() + ")";
	}
	else
	{
		switch (this->tokenType)
		{
		case TokenType::ID:
			out += "Identifier";
			break;
		case TokenType::NUM:
			out += "Number";
			break;
		case TokenType::END_FILE:
			out += "EOF";
			break;
		default:
			out += "ERROR (Unknown Token)";
			break;
		}
	}
	out += "\nToken String:\t";
	out += this->tokenStr;
	return out;
}

TokenType Token::getReservedKeyword(const std::string& tokenStr)
{
	if (isReservedKeyword(tokenStr))
	{
		return reservedKeywords.at(tokenStr);
	}
	return TokenType::ID;
}

bool Token::isReservedKeyword(const std::string& tokenStr)
{
	return (reservedKeywords.find(tokenStr) != reservedKeywords.end());
}

bool Token::isSpecialSymbol(const std::string& tokenStr)
{
	return (specialSymbols.find(tokenStr) != specialSymbols.end());
}
