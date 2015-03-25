#include <iostream>
#include <string>
#include <vector>
#include "LinkedList.h"
#include "VectorList.h"
using namespace std;

// display program instructions to user

template< typename T >
T func(const T &A)
{
      return A+1;
}

template< typename T >
bool predicate(const T &a)
{
      return false;
}



void instructions()
{
   cout << "Enter one of the following:\n"
      << "  1 to insert at beginning of list\n" 
      << "  2 to insert at end of list\n" 
      << "  3 to delete from beginning of list\n" 
      << "  4 to delete from end of list\n" 
      << "  5 to end list processing\n"
      << "  6 to acess an array element with subscript\n"
      << "  7 to find subSum\n"
      << "  8 to sort linked list\n"
      << "  9 to reverse the linked list\n"
      << "  10 to remove duplicates in linked list\n"
      << "  11 to see shared with l2\n"
      << "  12 to +1 the linked list (map)\n"
      << "  14 to filter\n";
} 

// function to test a LinkedList
template< typename T >
void testLinkedList( LinkedList< T > &listObject, const string &typeName )
{
   cout << "Testing a LinkedList of " << typeName << " values\n";
   instructions();       // display instructions
    
   int choice;           // store user choice
   T value;              // store input value


   do                    // perform user-selected actions
   {
      cout << "? ";
      cin >> choice;

      switch ( choice ) 
      {
         case 1:         // insert at beginning
            cout << "Enter " << typeName << ": ";
            cin >> value;
            listObject.insertAtFront( value );
            listObject.print();
            break;
         case 2:         // insert at end
            cout << "Enter " << typeName << ": ";
            cin >> value;
            listObject.insertAtBack( value );
            listObject.print();
            break;
         case 3:         // remove from beginning
            if ( listObject.removeFromFront( value ) )
               cout << value << " removed from list\n";

            listObject.print();
            break;
         case 4:          // remove from end
            if ( listObject.removeFromBack( value ) )
               cout << value << " removed from list\n";

            listObject.print();
            break;
		
		case 7:      // return subsum
			cout << listObject.maxSubSum();
		 break;

		case 8:      // sort the list
			listObject.sort();
			listObject.print();
		 break;
		
      case 9:     // reverse the list
			listObject.reverse();
			listObject.print();
		 break;			
		
		case 10:     // remove duplicates
      { 
            listObject.removeDup();
            listObject.print();
         
         break;
      }
      case 14:       
      {
            listObject.filter(predicate);
            listObject.print();
            break;
      } 
      case 11:
      { 
               LinkedList < T > l2;  
               l2.insertAtFront(10);
               l2.insertAtFront(20);
               listObject.shared(l2);
            
               break;
      }
      case 12:       //map function that squares the linked list
      {
         listObject.map(func);
         listObject.print();
         break;
      }
      case 6: //access an array element
		{	
				cout << "Enter array subscript : ";
				cin >> value;
				T element = listObject[value];
				cout << "\nEntry is : " << element << endl;
	        	break;
		
         }
      }
   } while ( choice != 5 ); 

   cout << "End list test\n\n";
}
 


// function to test a VectorList

template< typename T >
void testVectorList( VectorList< T > &listObject, const string &typeName )
{
   cout << "Testing a VectorList of " << typeName << " values\n";
   instructions();       // display instructions

   int choice;           // store user choice
   T value;              // store input value

   do                    // perform user-selected actions
   {
      cout << "? ";
      cin >> choice;

      switch ( choice ) 
      {
         case 1:         // insert at beginning
         {   cout << "Enter " << typeName << ": ";
            cin >> value;
            listObject.insertAtFront( value );
            listObject.print();
            break;
         }
         case 2:         // insert at end
         {
            cout << "Enter " << typeName << ": ";
            cin >> value;
            listObject.insertAtBack( value );
            listObject.print();
            break;
         }
         case 3:         // remove from beginning
         {
            if ( listObject.removeFromFront( value ) )
               cout << value << " removed from list\n";

            listObject.print();
            break;
         }
         case 4:          // remove from end
          {
            if ( listObject.removeFromBack( value ) )
               cout << value << " removed from list\n";

            listObject.print();
            break;
         }
         case 7:      // return subsum
         {
               cout << listObject.maxSubSum();
               break;
         }
         case 8:      // sort the list
         {
               listObject.sort();
               listObject.print();
               break;
         }
         case 9:     // reverse the list
          {
               listObject.reverse();
               listObject.print();
               break;        
         }
         case 10:    // remove duplicates
          {
               listObject.removeDup();
               listObject.print();
                 break;
            }
         case 11: 
         {
            VectorList < T > l2;

            l2.insertAtFront(10);
            l2.insertAtFront(20);
            listObject.shared(l2);
            break;
         }
         case 12:
         {    
                listObject.map(func);
               listObject.print();
         break;
         }
         case 14:
         {
               listObject.filter(predicate);
               listObject.print();
               break;
         }
         case 6:
         { 
            T subscript;
            cout << "Enter array subscript : ";
            cin >> subscript;
          
            T element = listObject[subscript];
            cout << "\nEntry is : " << element << endl;
            break;
         }  
      }


   } while ( choice != 5 ); 

   cout << "End list test\n\n";
} 

int main()
{
   // test LinkedList of int values
  LinkedList< int > integerLinkedList;
  testLinkedList( integerLinkedList, "integer" ); 
        
   
   // test VectorList of int values
   VectorList< int > integerVectorList;
   testVectorList( integerVectorList, "integer" ); 

   //test LinkedList of double values
   LinkedList< double > doubleLinkedList;
   testLinkedList( doubleLinkedList, "double" ); 

   // test VectorList of double values
   VectorList< double > doubleVectorList;
   testVectorList( doubleVectorList, "double" ); 

   return 0;
} 

