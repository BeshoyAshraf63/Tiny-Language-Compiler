#include "TreeNode.h"


using namespace ParserApp;

TreeNode::TreeNode()
{
	this->sibling = nullptr;
	this->modifier = 0;
}

TreeNode::TreeNode(const std::string& title, TreeNodeType type)
	: title(title), type(type)
{
	this->sibling = nullptr;
	this->modifier = 0;
}

std::string TreeNode::getTitle() const
{
	return this -> title;
}

void TreeNode::setTitle(const std::string & title)
{
	this->title = title;
}

TreeNodeType TreeNode::getType() const
{
	return this->type;
}

void TreeNode::setType(TreeNodeType type)
{
	this->type = type;
}

std::string TreeNode::getSubTitle() const
{
	return this->subTitle;
}

void TreeNode::setSubTitle(const std::string & subTitle)
{
	this->subTitle = subTitle;
}

void TreeNode::addChild(TreeNode * child)
{
	this->children.push_back(child);
}

TreeNode* const TreeNode::getChild(size_t index) const
{
	return this->children.at(index);
}

size_t TreeNode::getChildrenSize() const
{
	return this->children.size();
}

void TreeNode::setSibling(TreeNode* sibling)
{
	this->sibling = sibling;
}

TreeNode* const TreeNode::getSibling() const
{
	return this->sibling;
}

int TreeNode::getPosX() const
{
	return this->posX;
}

void TreeNode::setPosX(int posX)
{
	this->posX = posX;
}

int TreeNode::getPosY() const
{
	return this->posY;
}
void TreeNode::setPosY(int posY)
{
	this->posY = posY;
}

int TreeNode::getModifier() const
{
	return this->modifier;
}

void TreeNode::setModifier(int modifier)
{
	this->modifier = modifier;
}

TreeNode::~TreeNode()
{
	for (size_t i = 0; i < this->children.size(); i++)
	{
		delete this->children[i];
	}
	if(this->sibling)
		delete this->sibling;
}
