#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

// ---------------------------------------------- Structures ---------------------------------------------------

/**
 * Structure repesenting an element in a LinkedList.
 */
struct LinkedListNode
{
	/**
	 * Actual observation embedded in the element.
	 */
	void* data;

	/**
	 * Reference to the next element in the list.
	 */
	struct LinkedListNode* next;
} ;
typedef struct LinkedListNode LinkedListNode;


/**
 * Structure repesenting a LinkedList.
 */
struct LinkedList
{
	/**
	 * Reference to the first element in the list.
	 */
	LinkedListNode* first;

    /**
	 * Last element in the list.
	 * It is useful to insert a new element at the end of the list.
	 */
	LinkedListNode* last;

	/**
	 * Number of elements in the list.
	 */
	size_t size;
} ;
typedef struct LinkedList LinkedList;


// ---------------------------------------------- Functions ----------------------------------------------------

// --------------- Linked List -----------------

/**
 * Returns a pointer to an empty LinkedList.
 */
LinkedList* createLinkedList();

/**
 * Inserts an element at the end of the list.
 */
void insertInLast(LinkedList *l ,void* element );


/**
 * Returns the index-th element of the list.
 */
void* getLinkedListAtIndex(LinkedList* l, int index);


/**
 * Frees the memory space allocated to the list.
 */
void freeLinkedList(LinkedList* l);




#endif // LINKEDLIST_H_INCLUDED