#include "OrderedList.h"

OrderedList::OrderedList ()
{
	size = 0;
	head = NULL;
	nodeShortcut = NULL;
	posShortcut = 0;
}

OrderedList::~OrderedList () 
{    
    reset();
}

// Adds a new element to the list
// Returns the position where the element was added to
byte OrderedList::addElement (Comparable* element) 
{
	// Creates a new node with the element we want to add
	pNode new_node = (pNode) malloc (sizeof (tNode));
	new_node->item = element;
	pNode aux_node = head;
	pNode previous_node = NULL;
	byte pos = 0;
	// Goes through all the elements that are smaller than the one we want to add
	while (aux_node != NULL && element->compare(aux_node->item)>=0)
	{
		previous_node = aux_node;
		aux_node = aux_node->nextNode;
		pos++;
	}
	// If there is no previous node, it means that the new node will be the new head of the list
	if (previous_node == NULL)
	{
		head = new_node;
		new_node->nextNode = aux_node;
	}
	// Otherwise let's put the new node between two other nodes (ordered)
	else
	{
		previous_node->nextNode = new_node;
		new_node->nextNode = aux_node;
	}
	// Reset the shortcut node to the head of the list again
	nodeShortcut = head;
	posShortcut = 0;
	size++;
	return pos;
}

// Checks if an element is in the list
// Returns the position where the element is, or -1 if the element is not found
int OrderedList::checkElement (Comparable* element) 
{
	// If the list is empty there's no need to check anything
	if (size == 0) return -1; 
	
	// Otherwise we go through all the elements that are smaller than the one we want to check
	pNode aux_node = head;
	byte pos = 0;
	int compare;
	do
	{	
		// If the element is equal to the one we want, return the position 
		compare = element->compare(aux_node->item);
		if (compare == 0) return pos;
		
		// If it's not, advance to the next one and try again
		aux_node = aux_node->nextNode;
		pos++;
	}
	while (aux_node != NULL && compare>0);
	// If we reach this point, the element was not found
	return -1;
}

// Returns a pointer to the element in the specified position, 
// or NULL if the position is invalid
Comparable* OrderedList::getPosition (byte pos)
{
	if (pos>=size) return NULL;
	byte steps;
	// Checks if we can use the shortcut
	// We can't do it if the position we want is before the shortcut
	if (pos<posShortcut)
	{
		nodeShortcut = head;
		steps = pos;
	}
	else 
	{
		steps = pos-posShortcut;
	}
	for (byte i=0; i<steps; i++)
		nodeShortcut = nodeShortcut->nextNode;	

	posShortcut = pos;
	return nodeShortcut->item;
}

// Removes a link from a specific position of the list
// deleting the object depending on the destroy parameter
// used to implement the removeElement and destroyElement methods
void OrderedList::deletePosition (byte pos, bool destroy)
{
	// If the position is invalid doesn't do anything
	if (pos>=size) return;
	pNode remove_node;
	pNode previous_remove_node;
	// If we're removing the first element, then the node to remove is 
	// the head node, and there is no previous node
	if (pos == 0)
	{
		remove_node = head;
	}
	// If we're not removing the head, let's look for the node to remove
	else
	{
		// Searches for the node PREVIOUS to the node we want to remove
		previous_remove_node = head;
		for(byte i=0; i<pos-1; i++)
			previous_remove_node = previous_remove_node->nextNode;
		// Now what we found the previous node, the one we want to remove is the next one	
		remove_node = previous_remove_node->nextNode;
	}
	// Deletes the selected node
	if (destroy) delete(remove_node->item);
	
	// Updates the links so the surrounding nodes are connected properly
	// If the node we just removed was NOT the head, then the previous node
	// needs to point to the the node after the one we just removed
	if (pos > 0)
		previous_remove_node->nextNode = remove_node->nextNode;
	// If the node removed was the head, then we just update the head to the new value	
	else head = remove_node->nextNode;
	free(remove_node);
	size--;
	nodeShortcut = head;
	posShortcut = 0;
}

// Removes the element in the specified position
// If does not delete the object, only removes it from the list
// If the position is invalid nothing happens
void OrderedList::removeElement (byte pos)
{
	deletePosition (pos, false);
}

// Removes the element in the specified position from the list
// This also destroys the object that is removed
// If the position is invalid nothing happens
void OrderedList::destroyElement (byte pos)
{
	deletePosition (pos, true);
}

// Checks in the list is empty
bool OrderedList::isEmpty ()  
{
    return head == NULL;
}

// Returns the number of elements in the list
byte OrderedList::count ()
{
    return size;
}

// Clears the list, DELETING all the elements 
void OrderedList::reset () 
{    
	// Iterates through all the nodes in the list, deleting the objects 
	// on each one and then deleting the node itself
    for (pNode t = head; t != NULL; head = t) 
    {
        delete( t->item );
        t = head->nextNode;
        free (head);
    }
    size = 0;
    tail = NULL;
}

