#include "stdafx.h"
#include "RB_Tree_Node.h"

template <class T>
RB_Tree_Node<T>::RB_Tree_Node(T data_in):data(data_in),color_tag(0),Left_child(NULL),Right_child(NULL),Father_Node(NULL)
{
	data = data_in;
	color_tag = 1;
}

template <class T>
RB_Tree_Node<T>::~RB_Tree_Node(void)
{
}
