#include "Tree.h"

using namespace ParserApp;

Tree::Tree(TreeNode* root)
	: root(root)
{
}

void Tree::setRoot(TreeNode* root)
{
	this->root = root;
}

TreeNode* const Tree::getRoot() const
{
	return this->root;
}

void Tree::updateTreeNodesPos()
{
	int maxHeight = 0;
	updateTreeNodesYPos(this->root, 0, maxHeight);
	std::vector<int> modifierX(maxHeight + 1, 0);
	std::vector<int> nextX(maxHeight + 1, 0);
	updateTreeNodesXPost(this->root, nextX, modifierX);
	int modifierSum = 0;
	updateTreeNodesXPre(this->root, nextX, modifierX, modifierSum);
}

void Tree::updateTreeNodesYPos(TreeNode* node, int y, int& maxHeight)
{
	if (y > maxHeight) maxHeight = y;
	node->setPosY(y);
	if (node->getSibling())
		updateTreeNodesYPos(node->getSibling(), y, maxHeight);
	for (size_t i = 0; i < node->getChildrenSize(); i++)
	{
		updateTreeNodesYPos(node->getChild(i), y + 1, maxHeight);
	}
}

void Tree::updateTreeNodesXPost(TreeNode* node, std::vector<int>& nextX, std::vector<int>& modifierX)
{
	int avgX = 0, place = 0, h = node->getPosY();
	for (size_t i = 0; i < node->getChildrenSize(); i++)
	{
		updateTreeNodesXPost(node->getChild(i), nextX, modifierX);
		avgX += node->getChild(i)->getPosX();
	}
	if (node->getChildrenSize() == 0)
	{
		place = nextX[h];
	}
	else if (node->getChildrenSize() == 1)
	{
		place = node->getChild(0)->getPosX();
	}
	else if (node->getTitle() == "if")
	{
		place = node->getChild(1)->getPosX();
	}
	else
	{
		avgX /= node->getChildrenSize();
		place = avgX;
	}
	modifierX[h] = std::max(modifierX[h], nextX[h] - place);

	if (node->getChildrenSize() == 0)
	{
		node->setPosX(place);
	}
	else
	{
		node->setPosX(place + modifierX[h]);
	}
	nextX[h] = node->getPosX() + 2;
	node->setModifier(modifierX[h]);
	if (node->getSibling())
		updateTreeNodesXPost(node->getSibling(), nextX, modifierX);
}

void Tree::updateTreeNodesXPre(TreeNode* node, std::vector<int>& nextX, std::vector<int>& modifierX, int& modifierSum)
{
	int h = node->getPosY();
	node->setPosX(node->getPosX() + modifierSum);
	modifierSum += node->getModifier();

	for (size_t i = 0; i < node->getChildrenSize(); i++)
	{
		updateTreeNodesXPre(node->getChild(i), nextX, modifierX, modifierSum);
	}
	modifierSum -= node->getModifier();
	if (node->getSibling())
		updateTreeNodesXPre(node->getSibling(), nextX, modifierX, modifierSum);
}


Tree::~Tree()
{
	delete this->root;
}