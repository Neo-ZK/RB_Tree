#include "stdafx.h"
#include "RB_Tree.h"
template <class T>
RB_Tree<T>::RB_Tree(T Root_Data):Root_Node(NULL)
{	
	if (Root_Node == NULL)
	{
		Root_Node = new RB_Tree_Node<T>(Root_Data);
		Root_Node->color_tag = 0;
	}
}

template <class T>
RB_Tree<T>::~RB_Tree()
{
}
/************************************************************************/
/* 函数功能：向红黑树中插入一个节点                                     */
// 入口参数：插入的数据
// 返回值：无
/************************************************************************/
template <class T>
void RB_Tree<T>::Insert_Node(T insert_data)
{
	
	RB_Tree_Node<T>* temp_Node = Root_Node;
	while(temp_Node != NULL)
	{
		if (insert_data > temp_Node->data)
		{
			if (temp_Node->Right_child == NULL)
			{
				temp_Node->Right_child = new RB_Tree_Node<T>(insert_data);
				temp_Node->Right_child->color_tag = 1;
				temp_Node->Right_child->Father_Node = temp_Node;
				if (temp_Node->color_tag == 1)
				{
					Fix_Tree(temp_Node->Right_child);
				}				
				break;
			}
			else
			{
				temp_Node = temp_Node->Right_child;
			}			
		}
		else
		{
			if (temp_Node->Left_child == NULL)
			{
				temp_Node->Left_child  = new RB_Tree_Node<T>(insert_data);
				temp_Node->Left_child->color_tag = 1;
				temp_Node->Left_child->Father_Node = temp_Node;
				if (temp_Node->color_tag == 1)
				{
					Fix_Tree(temp_Node->Left_child);
				}				
				break;
			}
			else
			{
				temp_Node = temp_Node->Left_child;
			}			
		}
	}	
}

/************************************************************************/
/* 函数功能：从红黑树中搜寻要删除的数据节点                             */
// 入口参数：删除的数据
// 返回值：1表示删除成功 -1表示删除失败
/************************************************************************/
template<class T>
int RB_Tree<T>::Delete_Node(T delete_data)
{	
	RB_Tree_Node<T>* temp_Node = Root_Node;
	while(temp_Node->data != delete_data && temp_Node != NULL)
	{
		if (delete_data > temp_Node->data)
		{
			temp_Node = temp_Node->Right_child;
		}
		else
		{
			temp_Node = temp_Node->Left_child;
		}
	}	
	if (temp_Node)
	//找到返回的数据
	{
		int color_tag = temp_Node->color_tag;
		
		if (temp_Node->Left_child == NULL && temp_Node->Right_child == NULL)
		//左右子树为空则直接删除
		{
			//			
			delete temp_Node;
		}
		else
		if (temp_Node->Left_child == NULL && temp_Node->Right_child != NULL)
		//左子树为空,右子树不为空
		{				
			if (temp_Node != Root_Node)
			//不为根节点
			{
				if (temp_Node->Father_Node->Left_child == temp_Node)
				{
					temp_Node->Father_Node->Left_child = temp_Node->Right_child;
					temp_Node->Right_child->Father_Node = temp_Node->Father_Node;
					
				}
				else
				{
					temp_Node->Father_Node->Right_child = temp_Node->Right_child;
					temp_Node->Right_child->Father_Node = temp_Node->Father_Node;
					
				}
			}
			else
			//根节点
			{
				Root_Node = temp_Node->Right_child;
				temp_Node->Right_child->Father_Node = Root_Node;
				
			}
		}
		else if (temp_Node->Left_child != NULL && temp_Node->Right_child == NULL)
		//左子树不为空,右子树为空
		{
			if (temp_Node != Root_Node)
				//不为根节点
			{
				if (temp_Node->Father_Node->Left_child == temp_Node)
				{
					temp_Node->Father_Node->Left_child = temp_Node->Left_child;
					temp_Node->Left_child->Father_Node = temp_Node->Father_Node;
					
				}
				else
				{
					temp_Node->Father_Node->Right_child = temp_Node->Left_child;
					temp_Node->Left_child->Father_Node = temp_Node->Father_Node;
					
				}
			}
			else
				//根节点
			{
				Root_Node = temp_Node->Left_child;
				temp_Node->Left_child->Father_Node = Root_Node;
				//delete temp_Node;
			}
		}
		else if (temp_Node->Left_child != NULL && temp_Node->Right_child != NULL)
		//左右子树都不为空
		{
			RB_Tree_Node<T>* Successor_Node = Find_Successor_Node(temp_Node);
			if (temp_Node == temp_Node->Father_Node->Left_child)
			{
				temp_Node->Father_Node->Left_child = Successor_Node;
				Successor_Node->Right_child = temp_Node->Right_child;
				Successor_Node->Left_child = temp_Node->Left_child;
				Successor_Node->Father_Node = temp_Node->Father_Node;
				Successor_Node->color_tag = temp_Node->color_tag;
				if (Successor_Node->Right_child)
				{
					Successor_Node->Father_Node->Left_child = Successor_Node->Right_child;
					Successor_Node->Right_child->Father_Node = Successor_Node->Father_Node;
				}
				
			}
			else
			{
				temp_Node->Father_Node->Right_child = Successor_Node;
				Successor_Node->Right_child = temp_Node->Right_child;
				Successor_Node->Left_child = temp_Node->Left_child;
				Successor_Node->Father_Node = temp_Node->Father_Node;
				Successor_Node->color_tag = temp_Node->color_tag;
				if (Successor_Node->Right_child)
				{
					Successor_Node->Father_Node->Left_child = Successor_Node->Right_child;
					Successor_Node->Right_child->Father_Node = Successor_Node->Father_Node;
				}
			}			
		}
		
		if (color_tag == 0)
		//如果删除的节点为黑色  则需调整红黑树
		{
			Fix_Tree_Delete(RB_Tree_Node<T>* temp_Node)
		}
	}
	//未发现删除的数据  返回-1
	else
	{
		return -1;
	}
	return 1;
	
}

/************************************************************************/
/* 函数功能：插入节点后修整红黑树，保证满足性质                         */
// 入口参数：插入的当前节点
// 返回值：无
/************************************************************************/
template <class T>
void RB_Tree<T>::Fix_Tree(RB_Tree_Node<T>* current_Node)
{
	RB_Tree_Node<T>* temp_current_Node = current_Node;	
	RB_Tree_Node<T>* uncle_Node;	
		
	while(true)
	{
		if ( temp_current_Node->Father_Node == NULL)
		{
			break;
		}
		if (temp_current_Node->Father_Node->color_tag != 1)
		{
			break;
		}		 
		RB_Tree_Node<T>* father_Node = temp_current_Node->Father_Node;
		RB_Tree_Node<T>* grandfa_Node = father_Node->Father_Node;
		if (grandfa_Node)
		{
			if (father_Node == grandfa_Node->Left_child)
			{
				uncle_Node = grandfa_Node->Right_child;
				//如果有叔叔节点时
				if (uncle_Node)
				{
					//情况1 叔叔为红色  将父亲节点和叔叔节点设置为黑色 
					//祖父节点设置为红色 将祖父节点设置为当前节点
					if (uncle_Node->color_tag == 1)
					{
						uncle_Node->color_tag = 0;
						father_Node->color_tag = 0;						
						grandfa_Node->color_tag = 1;						
						temp_current_Node = grandfa_Node;						
					}
					//情况2：叔叔是黑色 且当前节点为右孩子 将父节点作为当前节点 对父节点进行左旋
					else if (temp_current_Node == father_Node->Right_child)
					{
						temp_current_Node = temp_current_Node->Father_Node;						
						Left_Rotate(temp_current_Node);					
					}
					//情况3：叔叔是黑色 且当前节点为左孩子 将父节点设为黑色 祖父节点设为红色 对祖父节点右旋
					else
					{
						father_Node->color_tag = 0;
						grandfa_Node->color_tag = 1;
						Right_Rotate(grandfa_Node);				
					}					
				}
				//没有叔叔节点时
				else
				{
					if (temp_current_Node == father_Node->Right_child)
					{
						temp_current_Node = temp_current_Node->Father_Node;						
						Left_Rotate(temp_current_Node);					
					}					
					else
					{
						father_Node->color_tag = 0;
						grandfa_Node->color_tag = 1;
						Right_Rotate(grandfa_Node);	
					}
				}
			}
			else
			{
				uncle_Node = grandfa_Node->Left_child;
				if (uncle_Node)
				{
					//情况1 叔叔为红色  将父亲节点和叔叔节点设置为黑色 
					//祖父节点设置为红色 将祖父节点设置为当前节点
					if (uncle_Node->color_tag == 1)
					{
						uncle_Node->color_tag = 0;
						father_Node->color_tag = 0;						
						grandfa_Node->color_tag = 1;						
						temp_current_Node = grandfa_Node;						
					}
					//情况2：叔叔是黑色 且当前节点为右孩子 将父节点作为当前节点 对父节点进行左旋
					else if (temp_current_Node == father_Node->Left_child)
					{
						temp_current_Node = temp_current_Node->Father_Node;
						Right_Rotate(temp_current_Node);						
					}
					//情况3：叔叔是黑色 且当前节点为左孩子 将父节点设为黑色 祖父节点设为红色 对祖父节点右旋
					else
					{
						father_Node->color_tag = 0;
						grandfa_Node->color_tag = 1;
						Left_Rotate(grandfa_Node);	
					}									
				}
				else
				{
					if (temp_current_Node == father_Node->Left_child)
					{
						temp_current_Node = temp_current_Node->Father_Node;
						Right_Rotate(temp_current_Node);						
					}					
					else
					{
						father_Node->color_tag = 0;
						grandfa_Node->color_tag = 1;
						Left_Rotate(grandfa_Node);	
					}	
				}
			}
		}
	}
	Root_Node->color_tag = 0;

}

/************************************************************************/
/* 函数功能：对当前节点进行左旋操作                                     */
// 入口参数：左旋的当前节点
// 返回值：无
/************************************************************************/
template <class T>
void RB_Tree<T>::Left_Rotate(RB_Tree_Node<T>* current_Node)
{
	RB_Tree_Node<T>* Right_child = current_Node->Right_child;	
	RB_Tree_Node<T>* father_Node = current_Node->Father_Node;
	current_Node->Right_child = Right_child->Left_child;
	Right_child->Father_Node = father_Node;
	if (father_Node == NULL)
	{
		Root_Node = Right_child;
	}
	else if(current_Node == father_Node->Left_child)
	{
		father_Node->Left_child = Right_child;
	}
	else
	{
		father_Node->Right_child = Right_child;
	}	

	Right_child->Left_child = current_Node;
	current_Node->Father_Node = Right_child;

}

/************************************************************************/
/* 函数功能：对当前节点进行右旋操作                                     */
// 入口参数：右旋的当前节点
// 返回值：无
/************************************************************************/
template <class T>
void RB_Tree<T>::Right_Rotate(RB_Tree_Node<T>* current_Node)
{
	RB_Tree_Node<T>* left_Node = current_Node->Left_child;
	RB_Tree_Node<T>* father_Node = current_Node->Father_Node;
	current_Node->Left_child = left_Node->Right_child;
	left_Node->Right_child = current_Node;
	if (father_Node == NULL)
	{
		Root_Node = left_Node;
	}
	else if (current_Node = father_Node->Left_child)
	{
		father_Node->Left_child = left_Node;
	}
	else
	{
		father_Node->Right_child = left_Node;
	}
	current_Node->Father_Node = left_Node;
	left_Node->Father_Node = father_Node;
}


/************************************************************************/
/* 函数功能：找寻当前节点的中序后继节点                                 */
// 入口参数：当前节点
// 返回值：当前节点的中序后继节点
/************************************************************************/
template<class T>
RB_Tree_Node<T>* RB_Tree<T>::Find_Successor_Node(RB_Tree_Node<T>* current_Node)
{
	RB_Tree_Node<T>* temp_Node = current_Node->Right_child;
	while(temp_Node->Left_child != NULL)
	{
		temp_Node = temp_Node->Left_child;
	}
	return temp_Node;	
}

/************************************************************************/
/* 函数功能：清除该节点相关的所有信息                                   */
// 入口参数：当前节点
// 返回值：无
/************************************************************************/
template<class T>
void RB_Tree<T>::erase_Node(RB_Tree_Node<T>* Node_del)
{
	if (Node_del->Father_Node)
	{
		Node_del->Father_Node = NULL;
	}
	Node_del->color_tag = NULL;
	Node_del->Father_Node = NULL;
	Node_del->Left_child = NULL;
	Node_del->Right_child = NULL;
	Node_del->data = NULL;	
	delete Node_del;
}