/***********************************************************************
* Module:
*    BNode
* Author:
*    Sam, John, and Nathan
* Summary:
*    This class implements a single BNode data structure.
************************************************************************/

#ifndef BNODE_H
#define BNODE_H

#include <iostream>

using namespace std;


/*******************************************
* CLASS - BNode
* This class implements a single BNode data
* structure.
*******************************************/
    template <class T>
    class BNode
    {
        public:
            T data;
            BNode * pLeft;
            BNode * pRight;
            BNode * pParent;

            //constructors
            BNode() : pLeft(NULL), pRight(NULL), pParent(NULL) { }
            BNode(const T & t) : pLeft(NULL), pRight(NULL), pParent(NULL), data(t) {  }
    };

/******************************************************************************
 * BNode :: displayVLR
 * Recursively display the tree in LVR order separated by a single space.
 ****************************************************************************/
    template <class T>
    void displayLVR(const BNode <T>* pHead)
    {
       if (pHead == NULL)
       {
          return;
       }

       displayLVR(pHead->pLeft);
       cout << "'" << pHead->data << "'" << ", ";
       displayLVR(pHead->pRight);
    }

/******************************************************************************
 * BNode :: operator <<
 * Calls on the displayLVR() function to display binary trees in LVR order
 * reference assignment08.cpp line 247 for expected use
 * reference pair.h lines 61-72 for similar operation (pair.h operator <<)
 ****************************************************************************/
    template <class T>
    ostream& operator << (ostream& out, const BNode <T>* rhs)
    {
       displayLVR(rhs);

       return out;
    }

/******************************************************************************
 * BNode :: ADDLEFT (T)
 * Adds a child node to the pLeft of a given Node with a template variable
 ****************************************************************************/
    template <class T>
    void addLeft(BNode <T> * pNode, const T & t)
    {
        BNode <T>* pAdd;

        try
        {
           pAdd = new BNode<T>(t);
        }
        catch(std::bad_alloc) { throw "ERROR: Unable to allocate a node"; }
        pAdd->pParent = pNode;
        pNode->pLeft = pAdd;
    }

/******************************************************************************
 * BNode :: ADDLEFT (BNode)
 * Adds a child node to the pLeft of a given Node with given Node
 ****************************************************************************/
    template <class T>
    void addLeft(BNode <T> * pNode, BNode <T>* noddy)
    {
       if (noddy != NULL)
       {
          noddy->pParent = pNode;
       }

       pNode->pLeft = noddy;
    }

/******************************************************************************
 * BNode :: ADDRIGHT (T)
 * Adds a child node to the pLeft of a given Node with a template variable
 ****************************************************************************/
    template <class T>
    void addRight(BNode <T>* pNode, const T & t)
    {
       BNode <T>* pAdd;

       try
       {
          pAdd = new BNode<T>(t);
       }
       catch (std::bad_alloc) { throw "ERROR: Unable to allocate a node"; }
       pAdd->pParent = pNode;
       pNode->pRight = pAdd;
    }

/******************************************************************************
 * BNode :: ADDRIGHT (BNode)
 * Adds a child node to the pLeft of a given Node with given Node
 ****************************************************************************/
    template <class T>
    void addRight(BNode <T> * pNode, BNode<T>* noddy)
    {
       if (noddy != NULL)
       {
          noddy->pParent = pNode;
       }

       pNode->pRight = noddy;
    }

/******************************************************************************
* BNode :: COPYBTREE
*
* Takes a BNode as a parameter makes a copy of the tree.
* The return value is the newly copied tree. This is a
* recursive function.
******************************************************************************/
    template <class T>
    BNode <T>* copyBTree(BNode <T>* toCopy)
    {
        if (toCopy == NULL)
        {
            //Returns null when the end of the tree is reached. 
            return NULL;
        }
        else
        {
            //Makes a new node that copies the value of the old one
            BNode<T>* newNode = new BNode<T>(toCopy->data);

            //Travels down the tree on either side, copying those elements
            addLeft(newNode, copyBTree(toCopy->pLeft));
            if (newNode->pLeft != NULL)
            {
               newNode->pLeft->pParent = newNode;
            }

            addRight(newNode, copyBTree(toCopy->pRight));
            if (newNode->pRight != NULL)
            {
               newNode->pRight->pParent = newNode;
            }

            return newNode;
        }
    }

    /*************************************************************
    *   BNode :: DELETEBTREE
    *
    *   Takes a BNode and deletes it and all its children.
    **************************************************************/
    template <class T>
    void deleteBTree(BNode <T>* &toDelete)
    {
        if (toDelete == NULL)
        {
            //Ends the function when null is reached.
            return;
        }
        else
        {
            //Runs the function on both of the node's children before deleting the node
            deleteBTree(toDelete->pLeft);
            deleteBTree(toDelete->pRight);
            delete toDelete;
            toDelete = NULL;
            return;
        }
    }

    /*************************************************************
    *   BNode :: SIZEBTREE
    *
    *   Takes a BNode and returns the size of it
    **************************************************************/
    template <class T>
    int sizeBTree(BNode <T>* getSize)
    {
        if (getSize == NULL)
        {
            //Ends the function when null is reached
            return 0;
        }
        else
        {
            //Returns 1 for each node that isn't null
            return sizeBTree(getSize->pLeft) + 1 + sizeBTree(getSize->pRight);
        }
    }
#endif //end BNODE_H definition
