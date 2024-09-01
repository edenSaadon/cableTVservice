#ifndef _LIST_
#define _LIST_
#include "Employee.h"
//#define _CRT_SECURE_NO_WARNINGS update in project properties


// List
#define		EMPTY	0x7FFFFFFF

// new types
typedef void* DATA;					// a type for data (easy to change)
typedef enum { False, True } BOOL;	// a boolean type

// Node
typedef struct node
{
	DATA			key;
	struct node* next;
}NODE;

typedef struct
{
	NODE head;
}LIST;



/*** Function prototypes ***/
NODE* L_insert_NEW(NODE* pNode, DATA Value);

BOOL L_init(LIST* pList);					// create new list

BOOL L_delete(NODE* pNode, void (*freeFunc)(void*));					// erase node after *pNode

BOOL L_free(LIST* pList, void (*freeFunc)(void*));					// free list memory

int L_print(const LIST* pList, void(*print)(const void*));					// print the list content

#endif


