#ifndef VECTORLIST_H
#define VECTORLIST_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

template< typename NODETYPE >
class VectorList 
{
 public:
  VectorList(); // constructor
  ~VectorList(); // destructor

  void insertAtFront( const NODETYPE & );
  void insertAtBack( const NODETYPE & );
  bool removeFromFront( NODETYPE & );
  bool removeFromBack( NODETYPE & );
  bool isEmpty() const;
  void print() const;

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
  bool shared(const VectorList< NODETYPE > &l2); 

  // Apply the function func to each element in the linked list
  void map(NODETYPE func(const NODETYPE &));

  // Keep only those nodes n where predicate(n) = true 
  void filter(bool predicate(const NODETYPE &)); 

  // Remove all duplicates from the list 
  void removeDup(); 

  //
  /////////////////////////////////////////////////////////

 private:
  vector< NODETYPE > *vList;  // list data as a vector
}; 

template<typename NODETYPE>
NODETYPE &VectorList <NODETYPE> :: operator[](int index) const
{
    return ((*vList)[index]);
}

template< typename NODETYPE > 
VectorList< NODETYPE >::VectorList()  
: vList(new vector<NODETYPE>)  
{  
  // empty body 
  
}  

template< typename NODETYPE > 
VectorList< NODETYPE >::~VectorList() 
{ 
    if(vList->size() != 0)
    {
        vList->clear();
      
        delete vList;
    }
}  

// insert node at front of list
template< typename NODETYPE >
void VectorList< NODETYPE >::insertAtFront( const NODETYPE &value )
{
   vList->insert(vList->begin(),value);
} 

// insert node at back of list
template< typename NODETYPE >
void VectorList< NODETYPE >::insertAtBack( const NODETYPE &value )
{
   vList->push_back(value);
} 

// delete node from front of list
template< typename NODETYPE >
bool VectorList< NODETYPE >::removeFromFront( NODETYPE &value )
{
   if(vList->size() == 0)
   {
      return false;
   } 
   else
   {
      vList->erase(vList->begin());
      return true;
   }
   
} 

// delete node from back of list
template< typename NODETYPE >
bool VectorList< NODETYPE >::removeFromBack( NODETYPE &value )
{
  if(vList->size() == 0)
  {
    return false;
  }
  else
  {
    vList->erase(vList->end()-1); 
    
    return false;
  }

} 

// is VectorList empty?
template< typename NODETYPE > 
bool VectorList< NODETYPE >::isEmpty() const 
{ 
    return vList->size();
} 

// display contents of VectorList
template< typename NODETYPE >
void VectorList< NODETYPE >::print() const
{
    if(vList->size() == 0)
    {
      cout << "The list is empty\n";
    }
    else
    {
        for(unsigned int i = 0; i < vList->size(); i++)
        cout << (*this)[i] << ' ';
    
        cout << endl;
    }
}
 
template<typename NODETYPE>
void VectorList<NODETYPE> :: reverse()
{

  for(unsigned int i = 0, j = vList->size()-1; i < vList->size()/2; i++, j--)
  {
  
          int temp = (*this)[i];
  
          (*this)[i] = (*this)[j];
  
          (*this)[j] = temp;
  
  }
  cout << endl; 

}    

template <typename NODETYPE>
void VectorList<NODETYPE> :: sort() 
{

  for (unsigned int j = 0; j < vList->size(); j++)
  {
      for(unsigned int k = 0; k < j; k++)
      {
        int temp;
      
          if((*this)[j] < (*this)[k])
          {
            
            temp = (*this)[j];
        
            (*this)[j] = (*this)[k];
          
            (*this)[k] = temp;
      
          }
      }
  }
  

    
}
template <typename NODETYPE>
void VectorList <NODETYPE> :: removeDup()
{

  vList->resize(distance(vList->begin(), unique(vList->begin(), vList->end())));
  
}
template <typename NODETYPE>
void VectorList <NODETYPE> ::map(NODETYPE func(const NODETYPE &))
{
    for (unsigned int j = 0; j<vList->size(); j++)
    {
        (*this)[j] = func((*this)[j]);

    }
}
template <typename NODETYPE>
NODETYPE VectorList <NODETYPE> :: maxSubSum() const
{

    NODETYPE subsum = 0;

    for(unsigned int i = 0; i < vList->size(); i++)
    { 
      subsum+= (*this)[i];

    }

  return subsum;
}
template <typename NODETYPE>
void VectorList <NODETYPE> :: filter(bool predicate(const NODETYPE &))
{
    for(unsigned int i = 0; i < vList->size(); i++)
    {

      if(!predicate((*this)[i]))
      {
        vList->erase(vList->begin(), vList->end());
        i = i -1;
      }

    }
}
template <typename NODETYPE>
bool VectorList <NODETYPE> :: shared(const VectorList< NODETYPE > &l2)
{
  for(unsigned int i = 0; i< l2.vList->size(); i++)
  {
  
      for(unsigned int j=0; j < vList->size(); j++)
      {
          if((*vList)[j] == l2[i])       
          {
              
              cout << "at least one node in common\n";
    
              return true;

          }
      }
  
    }
  
  cout << "No nodes in common\n";
  
  return 0;
}
#endif
