#ifndef _PARSER_
#define _PARSER_

#include <string>
#include <vector>
#include "Scanner.h"
#include "Tree.h"
#include "Token.h"

namespace ParserApp{

	class Parser
	{
	private:
		Scanner* scanner;
		bool error;
		std::vector<std::string> errorMsgs;
		Token currentToken;

		void addErrorMsg(const std::string& errorMsg);
		void match(TokenType expectedTokenType);

		TreeNode* stmt_sequence();
		TreeNode* statement();
		TreeNode* if_stmt();
		TreeNode* repeat_stmt();
		TreeNode* assign_stmt();
		TreeNode* read_stmt();
		TreeNode* write_stmt();
		TreeNode* exp();
		TreeNode* simple_exp();
		TreeNode* term();
		TreeNode* factor();

	public:
		Parser(std::string programString);
		Tree* parse(std::vector<std::string>& errorMsgs);
	};
}

#endif

