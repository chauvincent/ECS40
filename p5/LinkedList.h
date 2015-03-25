#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "ListNode.h"
using namespace std;

template< typename NODETYPE >
class LinkedList 
{
 public:
  LinkedList(); // constructor
  ~LinkedList(); // destructor

  void insertAtFront( const NODETYPE & );
  void insertAtBack( const NODETYPE & );
  bool removeFromFront( NODETYPE & );
  bool removeFromBack( NODETYPE & );
  bool isEmpty() const;
  void print() const;
  int getSize() const;
  /////////////////////////////////////////////////////////
  // new member functions for HW 5

  // overload array access operator 
  NODETYPE &operator[](int index) const;

  // Find the MAXIMAL SUM of values among all consecutive sub-lists 
  // of the linked list, assuming +, <, == are overloaded for NODETYPE
  NODETYPE maxSubSum() const; 

  // Sort the linked list in ascending order, 
  // assuming NODETYPE supports <, ==, etc.
  void sort(); 

  // In-place reversal of the linked list, i.e., don't create a new list
  // to perform the reversal, and use the list itself
  void reverse();        
  
  // Check whether the current list and the input l2 share any nodes or not 
  bool shared(const LinkedList< NODETYPE > &l2); 

  // Apply the function func to each element in the linked list
  void map(NODETYPE func(const NODETYPE &));

  // Keep only those nodes n where predicate(n) = true 
  void filter(bool predicate(const NODETYPE &)); 

  // Remove all duplicates from the list 
  void removeDup(); 
  
  //
  /////////////////////////////////////////////////////////

 private:
  ListNode< NODETYPE > *firstPtr;   // pointer to first node
  ListNode< NODETYPE > *lastPtr;    // pointer to last node

  // utility function to allocate new node
  ListNode< NODETYPE > *getNewNode( const NODETYPE & );
}; 

template <typename NODETYPE>
int LinkedList <NODETYPE>::getSize() const
{
	ListNode < NODETYPE > *currentPtr = firstPtr;
	int len = 0;
	while(currentPtr != NULL)
	{
		len++;
		
		currentPtr = currentPtr -> nextPtr;
		
	}
	return len;
}


template< typename NODETYPE >
LinkedList< NODETYPE >::LinkedList() 
: firstPtr( 0 ), lastPtr( 0 ) 
{ 
  // empty body
} 

template< typename NODETYPE >
LinkedList< NODETYPE >::~LinkedList()
{
  if ( !isEmpty() ) // LinkedList is not empty
    {    
      ListNode< NODETYPE > *currentPtr = firstPtr;
      ListNode< NODETYPE > *tempPtr;

      while ( currentPtr != 0 ) // delete remaining nodes
	{  
	  tempPtr = currentPtr;
	  cout << tempPtr->data << '\n';
	  currentPtr = currentPtr->nextPtr;
	  delete tempPtr;
	} 
    } 
} 

// insert node at front of list
template< typename NODETYPE >
void LinkedList< NODETYPE >::insertAtFront( const NODETYPE &value )
{
  ListNode< NODETYPE > *newPtr = getNewNode( value ); // new node

  if ( isEmpty() )                 // LinkedList is empty
    firstPtr = lastPtr = newPtr;   // new list has only one node
  else // LinkedList is not empty
    {
      newPtr->nextPtr = firstPtr;  // point new node to previous 1st node
      firstPtr = newPtr;           // aim firstPtr at new node
    } 
} 

// insert node at back of list
template< typename NODETYPE >
void LinkedList< NODETYPE >::insertAtBack( const NODETYPE &value )
{
  // new node
  ListNode< NODETYPE > *newPtr = getNewNode( value ); 

  if ( isEmpty() )                // LinkedList is empty
    firstPtr = lastPtr = newPtr;  // new list has only one node
  else                            // LinkedList is not empty
    {
      lastPtr->nextPtr = newPtr;  // update previous last node
      lastPtr = newPtr;           // new last node
    }
} 

// delete node from front of list
template< typename NODETYPE >
bool LinkedList< NODETYPE >::removeFromFront( NODETYPE &value )
{
  if ( isEmpty() )                // LinkedList is empty
    return false;                 // delete unsuccessful
  else 
    {
      // hold tempPtr to delete
      ListNode< NODETYPE > *tempPtr = firstPtr; 

      if ( firstPtr == lastPtr )
	firstPtr = lastPtr = 0;   // no nodes remain after removal
      else
	firstPtr = firstPtr->nextPtr; // point to previous 2nd node

      value = tempPtr->data;      // return data being removed
      delete tempPtr;             // reclaim previous front node
      return true;                // delete successful
    } 
} 

// delete node from back of list
template< typename NODETYPE >
bool LinkedList< NODETYPE >::removeFromBack( NODETYPE &value )
{
  if ( isEmpty() )                // LinkedList is empty
    return false;                 // delete unsuccessful
  else 
    {
      ListNode< NODETYPE > *tempPtr = lastPtr; // hold tempPtr to delete

      if ( firstPtr == lastPtr )  // LinkedList has one element
	firstPtr = lastPtr = 0;   // no nodes remain after removal
      else 
	{
	  ListNode< NODETYPE > *currentPtr = firstPtr;

	  // locate second-to-last element            
	  while ( currentPtr->nextPtr != lastPtr )    
            currentPtr = currentPtr->nextPtr; // move to next node

	  lastPtr = currentPtr;    // remove last node
	  currentPtr->nextPtr = 0; // this is now the last node
	} 

      value = tempPtr->data;       // return value from old last node
      delete tempPtr;              // reclaim former last node
      return true;                 // delete successful
    }
} 

// is LinkedList empty?
template< typename NODETYPE > 
bool LinkedList< NODETYPE >::isEmpty() const 
{ 
  return firstPtr == 0; 
} 

// return pointer to newly allocated node
template< typename NODETYPE >
ListNode< NODETYPE > *LinkedList< NODETYPE >::getNewNode( const NODETYPE &value )
{
  return new ListNode< NODETYPE >( value );
}

// display contents of LinkedList
template< typename NODETYPE >
void LinkedList< NODETYPE >::print() const
{
  if ( isEmpty() )           // LinkedList is empty
    {
      cout << "The list is empty\n\n";
      return;
    }

  ListNode< NODETYPE > *currentPtr = firstPtr;

  cout << "The list is: ";

  while ( currentPtr != 0 ) // get element data
    {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;
    } 

  cout << "\n\n";
} 

// overloading subscript operator to point to next ptr
template <typename NODETYPE>
NODETYPE & LinkedList < NODETYPE> ::operator[](int index) const
{
	
	ListNode < NODETYPE > *currentPtr = firstPtr;
	
	int i = 0;
	
	if(index < getSize())
	{
	
		while(i < index)
		{
	
			currentPtr = currentPtr -> nextPtr;
	
			i++;
	
		}
	
		NODETYPE temp = currentPtr -> getData();
	
		NODETYPE &node = temp;
	
		return node;
	}
	else
	{
		cout << "Out of Bounds" << endl;
	
		NODETYPE temp = 0;
	
		NODETYPE &node = temp;
	
		return node;
	}
	//return currentPtr; 
}

template <typename NODETYPE>
NODETYPE LinkedList < NODETYPE > :: maxSubSum() const
{

	NODETYPE subsum = 0;
	
	if (isEmpty())
	{
		cout << "The list is empty" << endl;
	}
	else
	{
	
		for(ListNode< NODETYPE > *currentPtr = firstPtr; currentPtr != 0; currentPtr = currentPtr -> nextPtr)
		{
			subsum += currentPtr->getData();
		}
		
	}
	return subsum;
}

template <typename NODETYPE>
void LinkedList < NODETYPE > :: sort()
{
	int length = getSize();

	ListNode < NODETYPE > *currentPtr = firstPtr;

	ListNode < NODETYPE > *prevPtr = 0;

	ListNode < NODETYPE> *tempNode = 0;

	int flag = 0;

	for (int i = 0; i < length; i++)
	{

		while(currentPtr -> nextPtr != NULL)
		{

			tempNode = currentPtr -> nextPtr;
			
			if(currentPtr -> data > tempNode -> data)
			{
				flag = 1;

				currentPtr -> nextPtr = tempNode -> nextPtr;
			
				tempNode -> nextPtr = currentPtr;
			
				if (prevPtr != 0)
			
					prevPtr->nextPtr = tempNode;
			
					prevPtr = tempNode;
			
				if (firstPtr == currentPtr)
			
					firstPtr = tempNode;
			
				if (currentPtr -> nextPtr == 0)
			
					lastPtr = currentPtr;
			}
			else
			{
			
				prevPtr = currentPtr;
			
				currentPtr = currentPtr -> nextPtr;
			}
		}
		if(flag == 0)
		
			break;
		
		else
		{
		
			prevPtr = 0;
		
			currentPtr = firstPtr;
		
			flag = 0;
		
		}
	}
}

template <typename NODETYPE>
void LinkedList < NODETYPE > :: reverse()
{
		ListNode < NODETYPE > *currentPtr = firstPtr;
		
		int size = getSize();
		
		if((firstPtr == NULL) || (size == 1))
		{
			cout << "Not enough elements to reverse\n";
		}
		else
		{

		ListNode < NODETYPE > *prevPtr = NULL;


		ListNode < NODETYPE > *nextPtr = 0;

		while(currentPtr)
		{

			nextPtr = currentPtr->nextPtr;
			
			currentPtr->nextPtr = prevPtr;

			prevPtr = currentPtr;

			currentPtr = nextPtr;
		}

		firstPtr = prevPtr;

		}
}
template <typename NODETYPE>
void LinkedList < NODETYPE > :: removeDup()
{
	ListNode <NODETYPE> *currentPtr = firstPtr;
	
	for(NODETYPE number; currentPtr != NULL; currentPtr = currentPtr ->nextPtr)
	{
		number = currentPtr -> data;

		ListNode <NODETYPE> *tempPtr = currentPtr -> nextPtr;
		
		ListNode <NODETYPE> *prevPtr = currentPtr;

		while(tempPtr)
		{
			if(number == tempPtr->getData())
			{
				ListNode <NODETYPE> *temp2 = tempPtr->nextPtr;				
		
				prevPtr->nextPtr = tempPtr->nextPtr;
		
				delete tempPtr;
		
				tempPtr = temp2;
			}
			else
			{
				tempPtr = tempPtr->nextPtr;
			}
		}
		
	}
}

template <typename NODETYPE>
bool LinkedList<NODETYPE> :: shared(const LinkedList< NODETYPE > &l2) 
{
	ListNode <NODETYPE> *currentPtr;

	for(currentPtr = firstPtr; currentPtr != NULL; currentPtr = currentPtr -> nextPtr)
  	{
    		
    	for(ListNode <NODETYPE> *l2ptr = l2.firstPtr; l2ptr != NULL; l2ptr = l2ptr -> nextPtr)
    	{
    
    		if(currentPtr->data == l2ptr->data)
        	{
        		cout << "at least one node in common\n";
        	
        		return true;
    		}
    	}
  	}
  
  	cout<< "no nodes in common\n";
  
  return 0;
  
}


template <typename NODETYPE>
void LinkedList <NODETYPE> :: map(NODETYPE func(const NODETYPE &))
{
	for(ListNode<NODETYPE> *currentPtr = firstPtr; currentPtr!=NULL; currentPtr = currentPtr->nextPtr)
	{
		currentPtr->data = func(currentPtr->data); 
	}		

}

template <typename NODETYPE>
void LinkedList <NODETYPE> :: filter(bool predicate(const NODETYPE &)) 
{

	if (!isEmpty())
	{
		ListNode< NODETYPE > *prevPtr = firstPtr;
		ListNode< NODETYPE > *currentPtr = firstPtr;
		
		while (currentPtr != 0 )
		{
		
			if (predicate(currentPtr->getData()) == true)
			{
				prevPtr = currentPtr;
				currentPtr = currentPtr->nextPtr;
			}
			else if (currentPtr == firstPtr)
			{
				prevPtr = firstPtr->nextPtr;
				firstPtr = prevPtr;
				delete currentPtr;
				currentPtr = prevPtr;
			}
			else
			{
				ListNode<NODETYPE>*tempPtr = currentPtr;
				prevPtr->nextPtr = currentPtr->nextPtr;
				currentPtr = currentPtr->nextPtr;
				delete tempPtr;
			}
		}
	}
	
}


#endif
