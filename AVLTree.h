#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _parent;
	int _bf; // balance factory

	AVLTreeNode(pair<K, V> &kv)
		:_right(nullptr)
		,_left(nullptr)
		,_parent(nullptr)
		,_bf(0)
		,_kv(kv)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(pair<K, V> kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			parent = cur;
			if (cur->_kv.first > kv.first)
			{
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first)
			{
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		
		// 创建节点，连接
		cur = new Node(kv);
		cur->_parent = parent;
		if (kv.first < parent->_kv.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}

		// 调整
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)
			{
				break;
			}
			else if (abs(parent->_bf) == 1)
			{
				cur = cur->_parent;
				parent = cur->_parent;
			}
			else if (abs(parent->_bf) == 2)
			{
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					// 左单旋
					RotateL(parent);
					break;
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					// 右旋，再左旋
					Node* subR = parent->_right;
					Node* subRL = subR->_left;
					int bf = subRL->_bf;

					RotateR(parent->_right);
					RotateL(parent);

					if (bf == 1)
					{
						parent->_bf = -1;
					}
					else
					{
						subR->_bf = 1;
					}
					break;
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
					break;
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					Node* subL = parent->_left;
					Node* subLR = subL->_right;
					int bf = subLR->_bf;

					RotateL(parent->_left);
					RotateR(parent);

					subLR->_bf = 0;
					if (bf == 1)
					{
						parent->_bf = 1;
					}
					else
					{
						subL->_bf = -1;
					}
					break;
				}
			}
		}
		return true;
	}

	void InOrder()
	{
		InOrder(_root);
	}
private:
	void InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		InOrder(root->_left);
		cout << root->_kv.first << ':' << root->_bf << endl;
		InOrder(root->_right);
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left; // subL左树
		Node* subLR = subL->_right; // 左树的右树
		Node* pparent = parent->_parent; // 父节点

		// 1. 左树的右树顶替parent的左树
		// 2. 左树顶替parent的位置
		// 3. parent顶替左树的右树
		parent->_left = subLR;
		if (subLR != nullptr)
		{
			subLR->_parent = parent;
		}
		subL->_parent = pparent;
		if (pparent != nullptr)
		{
			if (pparent->_left == parent)
			{
				pparent->_left = subL;
			}
			else
			{
				pparent->_right = subL;
			}
		}
		else
		{
			// parent为根节点
			_root = subL;
			subL->_parent = nullptr;
		}
		subL->_right = parent;
		parent->_parent = subL;
		subL->_bf = parent->_bf = 0;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pparent = parent->_parent;

		parent->_right = subRL;
		if (subRL != nullptr)
		{
			subRL->_parent = parent;
		}
		subR->_parent = pparent;
		if (pparent != nullptr)
		{
			if (pparent->_left == subR)
			{
				pparent->_left = subR;
			}
			else
			{
				pparent->_right = subR;
			}
		}
		else
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		subR->_left = parent;
		parent->_parent = subR;
		subR->_bf = parent->_bf = 0;
	}
private:
	Node* _root = nullptr; // c++11新特性，相当于默认值给nullptr
};

void TestAVLTree()
{
	int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int, int> t;
	for (auto e : array)
	{
		t.Insert(make_pair(e, 0));
	}
	t.InOrder();
}