#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct listnode{
	char name[50]; /*Store the name of the holder of the name of the item*/
	unsigned int person; /*If 0 it is an item if 1 it is a person*/
	struct listnode *next;
};

typedef struct listnode ListNode;
typedef ListNode *ListNodePtr;


void Display_Board();
void chain(ListNodePtr *sPtr, char *data, unsigned int person_or_item);
void print_chain(ListNodePtr Board);
void Load_Board();
bool ItemFound(ListNodePtr Board);
void Edit_List();
void Edit_Board();
void Save_Board();
