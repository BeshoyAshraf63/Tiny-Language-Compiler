#ifndef __TREE_NODE__
#define __TREE_NODE__

#include <vector>
#include <string>


namespace ParserApp {
	enum class TreeNodeType {
		STMT, EXP
	};

	class TreeNode
	{
	private:
		std::string title;
		TreeNodeType type;
		std::string subTitle;
		TreeNode* sibling;
		std::vector<TreeNode*> children;
		int posX;
		int posY;
		int modifier;

	public:
		TreeNode();
		TreeNode(const std::string& title, TreeNodeType type);

		std::string getTitle() const;
		void setTitle(const std::string& title);

		TreeNodeType getType() const;
		void setType(TreeNodeType type);

		std::string getSubTitle() const;
		void setSubTitle(const std::string& subTitle);

		void addChild(TreeNode* child);
		TreeNode* const getChild(size_t index) const;
		size_t getChildrenSize() const;

		void setSibling(TreeNode* sibling);
		TreeNode* const getSibling() const;

		int getPosX() const;
		void setPosX(int posX);

		int getPosY() const;
		void setPosY(int posY);

		int getModifier() const;
		void setModifier(int modifier);

		~TreeNode();

	};
}
#endif /* __TREE_NODE__ */
