#include "LinkedList.h"

// ----------------------------------- Linked List -------------------------------------

LinkedList* createLinkedList()
{
	LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
	if (l)
	{
		l->size = 0;
		l->first = NULL;
		l->last = NULL;
	}

	return l;
}

void insertInLast(LinkedList* l, void* element)
{

	LinkedListNode* newElem = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	if (newElem)
	{

		newElem->next = NULL;
		newElem->data = element;
		if (l->size == 0)
		{
			l->first = newElem;
			l->last = l->first;
		}
		else
		{
			l->last->next = newElem;
			l->last = newElem;
		}
	}
	
	l->size++;
}

void* getLinkedListAtIndex(LinkedList* l, int index)
{
	void* res = NULL;

	if (index >= 0 && index < l->size)
	{
		LinkedListNode* curr = l->first;
		int i = 0;
		while (i < index)
		{
			curr = curr->next;
			i++;
		}

		res = curr->data;
	}

	return res;
}

void freeLinkedList(LinkedList* l)
{
	LinkedListNode* current = l->first;
	LinkedListNode* tmp;

	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	
	free(l);
}
