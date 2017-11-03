#ifndef RB_TREE_NODE_H
#define RB_TREE_NODE_H
//#pragma once
#include "stdafx.h"
template <class T>
class RB_Tree_Node
{
public:
	RB_Tree_Node(T data_in);
	~RB_Tree_Node(void);
	RB_Tree_Node* Left_child;
	RB_Tree_Node* Right_child;
	RB_Tree_Node* Father_Node;
	T data;
	int color_tag; //1±íÊ¾ºìÉ« 0±íÊ¾ºÚÉ«
};

#endif
