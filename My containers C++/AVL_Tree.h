#pragma once

namespace spaceAVL_Tree
{
	template <class T>
	class AVL_Tree
	{
		struct TreeNode
		{
			T data;
			int height;
			TreeNode *left;
			TreeNode *right;
			TreeNode(T _data) : data(_data), height(1), left(nullptr), right(nullptr) {}
		};
		TreeNode *main_root;

	public:
		AVL_Tree()
		{
			this->clear(this->main_root);
			this->main_root = nullptr;
		}
		AVL_Tree(AVL_Tree &obj)
		{
			copy(this->main_root, obj.main_root);
		}
		~AVL_Tree()
		{
			this->clear(this->main_root);
			this->main_root = nullptr;
		}

		AVL_Tree& operator=(AVL_Tree &obj)
		{
			if (&obj == this) return *this;
			this->clear(this->main_root);
			this->main_root = nullptr;
			copy(this->main_root, obj.main_root);
			return *this;
		}

		bool IsEmpty()
		{
			return (this->main_root ? false : true);
		}
		T Find(T data)
		{
			TreeNode *p = this->main_root;
			while (p && p->data != data)
			{
				if (p->data < data) p = p->right;
				else if (p->data > data) p = p->left;
			}
			if (!p) return T();
			return p->data;
		}
		bool Insert(T data)
		{
			return insert(data, this->main_root);
		}
		bool Delete(T data)
		{
			return deleteNode(data, this->main_root);
		}
		void Clear()
		{
			this->clear(this->main_root);
			this->main_root = nullptr;
		}

	private:
		bool insert(T _data, TreeNode *&root) 
		{
			if (!root)
			{
				root = new TreeNode(_data);
				return false;
			}
			bool k = false;
			if (_data > root->data)
			{
				if (root->right != nullptr) k = insert(_data, root->right);
				else root->right = new TreeNode(_data);
			}
			else if (_data < root->data)
			{
				if (root->left != nullptr) k = insert(_data, root->left);
				else root->left = new TreeNode(_data);
			}
			else if (_data == root->data) { return true; }

			root->height = 1 + max(Height(root->left), Height(root->right));
			int balance = Balance(root);

			if (balance >  1 && Balance(root->left) >= 0) { R_rotate(root); return k; }
			if (balance >  1 && Balance(root->left)  <  0) { LR_rotate(root); return k; }
			if (balance < -1 && Balance(root->right) <= 0) { L_rotate(root); return k; }
			if (balance < -1 && Balance(root->right) >  0) { RL_rotate(root); return k; }
			return k;
		}
		bool deleteNode(T _data, TreeNode *&root)
		{
			if (!root) return false;
			bool res = false;
			if (_data < root->data) res = deleteNode(_data, root->left);
			else if (_data > root->data) res = deleteNode(_data, root->right);
			else
			{
				if ((root->left == nullptr) || (root->right == nullptr))
				{
					TreeNode *temp = (root->left ? root->left : root->right);
					if (temp == nullptr)
					{
						temp = root;
						root = nullptr;
					}
					else *root = *temp;
					delete temp;
				}
				else
				{
					TreeNode *temp = root->right;
					while (temp->left != nullptr) temp = temp->left;
					root->data = temp->data;
					deleteNode(temp->data, root->right);
				}
				res = true;
			}
			if (root == nullptr) return;

			root->height = 1 + max(Height(root->left), Height(root->right));
			int balance = Balance(root);

			if (balance >  1 && Balance(root->left) >= 0) { R_rotate(root); return res; }
			if (balance >  1 && Balance(root->left)  <  0) { LR_rotate(root); return res; }
			if (balance < -1 && Balance(root->right) <= 0) { L_rotate(root); return res; }
			if (balance < -1 && Balance(root->right) >  0) { RL_rotate(root); return res; }
		}
		void clear(TreeNode *root)
		{
			if (!root) return;
			clear(root->left);
			clear(root->right);
			delete root;
		}
		void copy(TreeNode *&into, TreeNode *&from)
		{
			if (!from) return;
			into = new TreeNode(from->data);
			into->height = from->height;
			copy(into->left, from->left);
			copy(into->right, from->right);
		}

		inline int max(int a, int b) 
			{ return (a > b) ? a : b; }
		inline int Balance(TreeNode *&root)
		{
			return ((root->left) ? root->left->height : 0) - ((root->right) ? root->right->height : 0);
		}
		inline int Height(TreeNode *&root)
		{
			return (root ? root->height : 0);
		}
		inline void L_rotate(TreeNode *&p1)
		{
			TreeNode *p2 = p1->right;
			p1->right = p2->left;
			p2->left = p1;
			p1->height = max(Height(p1->left), Height(p1->right)) + 1;
			p2->height = max(Height(p2->left), Height(p2->right)) + 1;
			if (p1 == this->main_root) this->main_root = p2;
			p1 = p2;
		}
		inline void R_rotate(TreeNode *&p1)
		{
			TreeNode *p2 = p1->left;
			p1->left = p2->right;
			p2->right = p1;
			p1->height = max(Height(p1->left), Height(p1->right)) + 1;
			p2->height = max(Height(p2->left), Height(p2->right)) + 1;
			if (p1 == this->main_root) this->main_root = p2;
			p1 = p2;
		}
		inline void LR_rotate(TreeNode *&p1)
		{
			TreeNode *p2 = p1->left;
			TreeNode *p3 = p2->right;
			p2->right = p3->left;
			p3->left = p2;
			p1->left = p3->right;
			p3->right = p1;
			p1->height = max(Height(p1->left), Height(p1->right)) + 1;
			p2->height = max(Height(p2->left), Height(p2->right)) + 1;
			p3->height = max(Height(p3->left), Height(p3->right)) + 1;
			if (p1 == this->main_root) this->main_root = p3;
			p1 = p3;
		}
		inline void RL_rotate(TreeNode *&p1)
		{
			TreeNode *p2 = p1->right;
			TreeNode *p3 = p2->left;
			p2->left = p3->right;
			p3->right = p2;
			p1->right = p3->left;
			p3->left = p1;
			p1->height = max(Height(p1->left), Height(p1->right)) + 1;
			p2->height = max(Height(p2->left), Height(p2->right)) + 1;
			p3->height = max(Height(p3->left), Height(p3->right)) + 1;
			if (p1 == this->main_root) this->main_root = p3;
			p1 = p3;
		}
	};
}