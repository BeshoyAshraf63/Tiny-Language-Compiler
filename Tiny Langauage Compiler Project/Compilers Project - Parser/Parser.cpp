#include "Parser.h"

using namespace ParserApp;

Parser::Parser(std::string programString)
{
	scanner = Scanner::getInstance();
	scanner->setProgramString(programString);
}

void Parser::addErrorMsg(const std::string& errorMsg)
{
	error = true;
	int lineNo = scanner->getCurrentLine();
	errorMsgs.push_back("Syntax Error at line: " + std::to_string(lineNo) + "\n" + errorMsg);
}

void Parser::match(TokenType expectedTokenType)
{
	if (currentToken.getTokenType() == expectedTokenType)
	{
		currentToken = scanner->getNextToken();
	}
	else
	{
        Token expectedToken;
        expectedToken.setTokenType(expectedTokenType);
		addErrorMsg("Unxpected Token: " + currentToken.getTokenStr() + " Expected Token: " + expectedToken.getTokenTypeStr());
	}
}

TreeNode* Parser::stmt_sequence()
{
	TreeNode* t_n = statement();
	TreeNode* p_n = t_n;
	Token curr_token = currentToken;
	TokenType curr_token_type = curr_token.getTokenType();
	while ((curr_token_type != TokenType::END_FILE) &&
		(curr_token_type != TokenType::END) &&
		(curr_token_type != TokenType::ELSE) &&
		(curr_token_type != TokenType::UNTIL))
	{
		match(TokenType::SEMICOLON);
		TreeNode* q_n = statement();
		if (q_n != NULL)
		{
			if (t_n == NULL)
			{
				t_n = p_n = q_n;
			}
			else
			{
				p_n->setSibling(q_n);
				p_n = q_n;
			}
		}
        curr_token_type = currentToken.getTokenType();
	}

	return t_n;
}

TreeNode* Parser::statement()
{
    TreeNode* t_n = NULL;
    Token curr_token = currentToken;
    TokenType curr_token_type = curr_token.getTokenType();
    switch (curr_token_type)
    {
    case TokenType::IF:
        t_n = if_stmt();
        break;

    case TokenType::REPEAT:
        t_n = repeat_stmt();
        break;
    case TokenType::ID:
        t_n = assign_stmt();
        break;

    case TokenType::READ:
        t_n = read_stmt();
        break;

    case TokenType::WRITE:
        t_n = write_stmt();
        break;

    default:
        addErrorMsg("Unexpected token: " + currentToken.getTokenStr());
        currentToken = scanner->getNextToken();
        break;
    }

    return t_n;
}

TreeNode* Parser::if_stmt()
{
    TreeNode* t_n = new TreeNode("if", TreeNodeType::STMT);
    match(TokenType::IF);
    if (t_n != NULL)
    {
        t_n->addChild(exp());
    }
    match(TokenType::THEN);
    if (t_n != NULL)
    {
        t_n->addChild(stmt_sequence());
    }

    if (currentToken.getTokenType() == TokenType::ELSE)
    {
        match(TokenType::ELSE);
        if (t_n != NULL)
        {
            t_n->addChild(stmt_sequence());
        }
    }

    match(TokenType::END);
    return t_n;
}

TreeNode* Parser::repeat_stmt()
{
    TreeNode* t_n = new TreeNode("repeat", TreeNodeType::STMT);
    match(TokenType::REPEAT);
    if (t_n != NULL)
    {
        t_n->addChild(stmt_sequence());
    }
    match(TokenType::UNTIL);
    if (t_n != NULL)
    {
        t_n->addChild(exp());
    }

    return t_n;
}

TreeNode* Parser::assign_stmt()
{
    TreeNode* t_n = new TreeNode("assign", TreeNodeType::STMT);
    if ((t_n != NULL) && (currentToken.getTokenType() == TokenType::ID))
    {
        t_n->setSubTitle(currentToken.getTokenStr());
    }
    match(TokenType::ID);
    match(TokenType::ASSIGN);
    if (t_n != NULL)
    {
        t_n->addChild(exp());
    }

    return t_n;
}

TreeNode* Parser::read_stmt()
{
    TreeNode* t_n = new TreeNode("read", TreeNodeType::STMT);
    match(TokenType::READ);
    if ((t_n != NULL) && (currentToken.getTokenType() == TokenType::ID))
    {
        t_n->setSubTitle(currentToken.getTokenStr());
    }
    match(TokenType::ID);
    return t_n;
}

TreeNode* Parser::write_stmt()
{
    TreeNode* t_n = new TreeNode("write", TreeNodeType::STMT);
    match(TokenType::WRITE);
    if (t_n != NULL)
    {
        t_n->addChild(exp());
    }
    return t_n;
}

TreeNode* Parser::exp()
{

    TreeNode* t_n = simple_exp();

    TokenType curr_token_type = currentToken.getTokenType();
    if ((curr_token_type == TokenType::LT) || (curr_token_type == TokenType::EQ))
    {
        TreeNode* p_n = new TreeNode("op", TreeNodeType::EXP);
        if (p_n != NULL)
        {
            p_n->addChild(t_n);
            p_n->setSubTitle(currentToken.getTokenStr());
            t_n = p_n;
        }
        match(currentToken.getTokenType());
        if (t_n != NULL)
        {
            t_n->addChild(simple_exp());
        }
    }

    return t_n;
}

TreeNode* Parser::simple_exp()
{
    TreeNode* t_n = term();

    TokenType curr_token_type = currentToken.getTokenType();

    while ((curr_token_type == TokenType::PLUS) || (curr_token_type == TokenType::MINUS))
    {
        TreeNode* p_n = new TreeNode("op", TreeNodeType::EXP);
        if (p_n != NULL)
        {
            p_n->addChild(t_n);
            p_n->setSubTitle(currentToken.getTokenStr());
            t_n = p_n;
            match(currentToken.getTokenType());
            t_n->addChild(term());
        }
        curr_token_type = currentToken.getTokenType();
    }
    return t_n;
}

TreeNode* Parser::term()
{
    TreeNode* t_n = factor();
    TokenType curr_token_type = currentToken.getTokenType();
    while ((curr_token_type == TokenType::TIMES) || (curr_token_type == TokenType::DIV))
    {
        TreeNode* p_n = new TreeNode("op", TreeNodeType::EXP);
        if (p_n != NULL)
        {
            p_n->addChild(t_n);
            p_n->setSubTitle(currentToken.getTokenStr());
            t_n = p_n;
            match(curr_token_type);
            p_n->addChild(factor());
            curr_token_type = currentToken.getTokenType();
        }
        curr_token_type = currentToken.getTokenType();
    }

    return t_n;
}

TreeNode* Parser::factor()
{
    TreeNode* t_n = NULL;
    TokenType curr_token_type = currentToken.getTokenType();
    switch (curr_token_type)
    {
    case TokenType::NUM:
        t_n = new TreeNode("const", TreeNodeType::EXP);
        if ((t_n != NULL) && (curr_token_type == TokenType::NUM))
        {
            t_n->setSubTitle(currentToken.getTokenStr());
        }
        match(TokenType::NUM);

        break;

    case TokenType::ID:
        t_n = new TreeNode("id", TreeNodeType::EXP);
        if ((t_n != NULL) && (curr_token_type == TokenType::ID))
        {
            t_n->setSubTitle(currentToken.getTokenStr());
        }
        match(TokenType::ID);
        break;

    case TokenType::L_PAREN:
        match(TokenType::L_PAREN);
        t_n = exp();
        match(TokenType::R_PAREN);
        break;

    default:
        addErrorMsg("Unexpected token: " + currentToken.getTokenStr());
        currentToken = scanner->getNextToken();
        break;
    }

    return t_n;
}

Tree* Parser::parse(std::vector<std::string>& errorMsgs)
{
    error = false;
    errorMsgs.clear();
	TreeNode* root;
	currentToken = scanner->getNextToken();
	root = stmt_sequence();
	if (currentToken.getTokenType() != TokenType::END_FILE)
	{
		addErrorMsg("Unexpected end of file");
	}
	Tree *tree = new Tree(root);

    errorMsgs = this->errorMsgs;
	return tree;
}
