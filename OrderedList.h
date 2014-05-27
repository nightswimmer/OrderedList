#ifndef ARDUINO_ORDEREDLIST_H
#define ARDUINO_ORDEREDLIST_H

#include <Arduino.h>

// Class used to compare the elements of different classes
// All the classes we want to add to the list need to implement the compare() method
// This method will determine how the different variables in that class are supposed to be ordered
class Comparable
{
    public:
        virtual int compare(Comparable* element) {return 0;};
        virtual ~Comparable() {};
};

// the definition of the queue class.
class OrderedList 
{
    public:
        OrderedList();
        ~OrderedList();

		// Adds a new element to the list
		// Returns the position where the element was added to
        byte addElement ( Comparable* element );

		// Checks if an element is in the list
		// Returns the position where the element is, or -1 if the element is not found
        int checkElement ( Comparable* element );

		// Returns a pointer to the element in the specified position, 
		// or NULL if the position is invalid
        Comparable* getPosition (byte pos);
		
		// Removes the element in the specified position
		// If does not delete the object, only removes it from the list
		// If the position is invalid nothing happens
    	void removeElement (byte pos);
		
		// Removes the element in the specified position from the list
		// This also destroys the object that is removed
		// If the position is invalid nothing happens
    	void destroyElement (byte pos);
		
		// Checks in the list is empty
        bool isEmpty ();
		
		// Returns the number of elements in the list
        byte count ();
		
		// Clears the list, DELETING all the elements 
        void reset ();
		
    private:	
        // the structure of each node in the list.
        typedef struct _node 
    	{
            Comparable* item;
            struct _node* nextNode;
        } tNode, *pNode;

        byte size;
        pNode head;
        pNode tail;
		pNode nodeShortcut;
		byte posShortcut;
};


#endif
