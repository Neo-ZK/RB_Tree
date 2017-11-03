#pragma once
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
	int color_tag; //1表示红色 0表示黑色
};

