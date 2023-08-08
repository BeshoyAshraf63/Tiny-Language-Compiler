#ifndef __TREE__
#define __TREE__

#include <vector>
#include <string>
#include "TreeNode.h"

namespace ParserApp {

	class Tree
	{
	private:
		TreeNode* root;
		static void updateTreeNodesYPos(TreeNode* node, int y, int& maxHeight);
		static void updateTreeNodesXPost(TreeNode* node, std::vector<int>& nextX, std::vector<int>& modifierX);
		static void updateTreeNodesXPre(TreeNode* node, std::vector<int>& nextX, std::vector<int>& modifierX, int& modifierSum);

	public:
		Tree() = default;
		Tree(TreeNode* root);

		void setRoot(TreeNode* root);
		TreeNode* const getRoot() const;

		void updateTreeNodesPos();

		~Tree();
	};
}
#endif /* __TREE__ */
