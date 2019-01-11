#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	pair<K, V> _kv;
	AVLTreeNode<K, V> _right;
	AVLTreeNode<K, V> _left;
	AVLTreeNode<K, V> _parent;
	int _bf; // balance factory

	AVLTreeNode(pair<K, V> &kv)
		:_right(nullptr)
		,_left(nullptr)
		,_right(nullptr)
		,_bf(0)
		,pair(kv)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode Node;
public:
	bool insert(pair<K, V> kv)
	{
		if (_root == nullptr)
		{
			_root = new AVLTreeNode(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = root;
		while (cur)
		{
			parent = cur;
			if (cur->_kv.first > kv.first)
			{
				cur = cur->_left;
			}
			else if (cur->_kv < kv.first)
			{
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
	}
private:
	Node* _root = nullptr; // c++11新特性，相当于默认值给nullptr
};