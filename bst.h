/*bsh.h*/

//
// Binary search tree
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max


using namespace std;

template<typename TKey,typename TValue>

class binarysearchtree
{
private:
  struct NODE
  {
    TKey  Key;
	TValue Value;
    NODE* Left;
    NODE* Right;
  };
 

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

  // 
  // _inorder does the actual inorder traversal and output 
  // to console.  Each key is output to the console followed
  // by " ", including the last key.
  //
  //---------------------------------------------------------------------------------
  void _inorder(NODE* cur)
  {
     if (cur == nullptr)
       return;
     else
     {
        _inorder(cur->Left);
        cout << cur->Key << " ";
        _inorder(cur->Right);
     }
  }
  //---------------------------------------------------------------------------------
  // private helper function for the copy constructor
  void _copyBST(NODE* copy)
  {
    if(copy == nullptr)
	    return ;
    else
	{
		 insert(copy->Key, copy->Value);
		 _copyBST(copy->Left);
		 _copyBST(copy->Right);
		 
	}
  
  }
  //---------------------------------------------------------------------------------
 // private helper function for the height function
  int Height(NODE* temp)
  {
     int left = 0;
     int right = 0;
     if(temp == NULL)
     return -1;
     else
     {
        left = Height(temp->Left);
        right = Height(temp->Right);
        return 1 + max(left,right);
     }

  }
//---------------------------------------------------------------------------------
 public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
  }
//   copy constructor
  binarysearchtree(const binarysearchtree& other){
  
  this->Root = nullptr;
  this->Size = 0;
	  
  _copyBST(other.Root);
  }
 //---------------------------------------------------------------------------------
  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  
  int size()
  {
    return Size;
  }
  //---------------------------------------------------------------------------------
  //
  // height
  //
  // Computes and returns height of tree; height of an empty tree is
  // defined as -1.
  int height()
  {
    return Height(Root); 
  }
  //---------------------------------------------------------------------------------

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return &(cur->Value);

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  
  
    // if get here, not found
    return nullptr;
  }

  //---------------------------------------------------------------------------------
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //  
  void insert(TKey key, TValue value)
  {
    
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
		  return;

      if (key < cur->Key)  // search left:
	  {
		
		  cur = cur->Left;
	  }
		else
		{
	
			cur = cur->Right;
		}
	}//while

   // creating a new node to insert into the binary search tree
   NODE* newNode = new NODE;
   newNode->Key = key;
   newNode->Value = value;
   newNode->Left = nullptr;
   newNode->Right = nullptr;
   // inserting new node 
   if(Root == nullptr)
   {
      Root = newNode;
      Size++;
   }
   
   else
   {
      cur = Root;
      while (cur != nullptr)
      {
         if (key < cur->Key)
         {
            if( cur->Left == nullptr)
            {
               cur->Left = newNode;
               Size++;
               break;
            }
            else
            {
            cur = cur->Left;
            }
         }
      else
      {
        if( cur->Right == nullptr)
        {
           cur->Right = newNode;
           Size++;
           break;
        }
        else
           cur = cur->Right;
      }
    }
   }
  }
//---------------------------------------------------------------------------------

  void inorder()
  {
     cout << "Inorder: ";
     
     _inorder(Root);
     
     cout << endl;
  }

};

 