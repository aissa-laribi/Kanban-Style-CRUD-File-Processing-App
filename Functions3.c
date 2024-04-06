#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char file[80]; /*Static variable containing the name of file and reused anywhere in the program*/
static unsigned short int type;
struct listnode{
	char name[50]; /*Store the name of the holder of the name of the item*/
	unsigned int person; /*If 0 it is an item if 1 it is a person*/
	struct listnode *next;
};

typedef struct listnode ListNode;
typedef ListNode *ListNodePtr;

static ListNodePtr Board = NULL;


void Display_Board(){
	/*In the Detailled specification, it says if 1 (Display board) => print default.txt*/
	char line[50];
	FILE *fp;

	if ((fp = fopen("default.txt", "r+"))== NULL) {
		printf("File failed to be opened. Please enter the name again.\n");
		fflush(stdout);
	}
	while(fgets(line, sizeof(line), fp)){
			printf("%s", line);
			fflush(stdout);
		}
	fclose(fp);

	puts("");
	fflush(stdout);
}
void chain(ListNodePtr *sPtr, char *data, unsigned int person_or_item){
	ListNodePtr newPtr = malloc(sizeof(ListNode));

	if(newPtr != NULL){
		strcpy(newPtr->name, data);
		newPtr->person = person_or_item;
		newPtr->next = NULL;

		ListNodePtr prevPtr = NULL;
		ListNodePtr currentPtr = *sPtr;

		while(currentPtr != NULL){
			prevPtr = currentPtr;
			currentPtr = currentPtr->next;
		}

		if(prevPtr == NULL){
			newPtr->next = *sPtr;
			*sPtr = newPtr;
		} else{
			prevPtr->next = newPtr;
		}

	} else{
		printf("No memory slot available\n");
	}
}
void print_chain(ListNodePtr Board){
    while ( Board != NULL ) {

        printf( "%d %s",  Board->person, Board->name);
        Board = Board->next;
     }
    puts("");
    puts("");
}

void Load_Board(){

	char line[50];
	printf("Please enter the name of the file you wish to enter. Enter 'default' for the default board.\n");
	fflush(stdout);

	scanf("%s",file);
	printf("%s\n", file);


	FILE *fp;

	if ((fp = fopen(file, "r+"))== NULL) {
		printf("File failed to be opened. Please enter the name again.\n");
		fflush(stdout);
		/*Should exit function*/
	} else {
		printf("File opened successfully.\n");
		fflush(stdout);
	}

	while(fgets(line, sizeof(line), fp)){
		if(line[0] != 9 && line[0] != 32){
			type = 1;
			chain(&Board, line, type);
		} else {
			type = 0;
			chain(&Board, line, type);
		}
	}
	fclose(fp);
	print_chain(Board);
	print_chain(Board);
}

bool ListFound(ListNodePtr Board, char *data){

	ListNodePtr CurrentPtr = Board;

    while ( CurrentPtr  != NULL ) {
    	if(CurrentPtr ->person && strcmp(data, CurrentPtr ->name) == 0 ){
    		printf("List found\n");
    		fflush(stdout);
    		return true;
    	}
    	if (CurrentPtr->next  == NULL){
    		printf("List not found\n");
    		return false;
    	}
    	CurrentPtr  = CurrentPtr ->next;
     }
    return true;
}

/*void ItemFound(ListNodePtr Board, char *data, char *data2){
	if(!ListFound(Board, data)){
		printf("%s not associated with %s\n", data, data2);
	} else{
		ListNodePtr currentListPtr = Board;
		while(strcmp(data, Board->name) != 0){
			Board = Board->next;
		}
	}*/




void Edit_List(){
	/*TODO:
	 *1. Edit an item
	  2. Add a new item
	  3. Delete an item
	  4. Return to main menu */

	printf("Edit %s\n", file);
	unsigned short int user_choice;
	char list_input[50];
	char item_input[50];
	char ch;
	FILE *fp;

	if((fp = fopen(file, "r+"))== NULL) {
		printf("File failed to be opened. Please enter the name again.\n");
		fflush(stdout);
	}

	printf("Enter the name of the list to edit:");
	scanf("%s", list_input);
	list_input[strlen(list_input)] = ':';
	list_input[strlen(list_input)] = '\n';
	printf("Looking for %s", list_input);
	/*Testing printing input file*/

	if(  ListFound(Board, list_input)  ){
			printf("Options:\n "
					"1. Edit an item\n"
					"2. Add a new item\n"
					"3. Delete an item\n"
					"4. Return to main menu\n"
					"Enter your option: ");
		scanf("%hd", &user_choice);
		ch = getchar();
		while(user_choice < 1 || user_choice > 4){
			if(ch == '\n'){
				puts("Invalid input");
				printf("Options:\n"
					   "1. Edit an item\n"
					   "2. Add a new item\n"
					   "3. Delete an item\n"
					   "4. Return to main menu\n"
					   "Enter your option: ");
				scanf("%hd", &user_choice);
						}
			else{
				/*Trap the unwanted characters here*/
			}
			ch = getchar();
		}

		switch(user_choice){
		case 1:
			printf("Enter the name of the item to edit:\n");
			fgets(item_input, 50, stdin);

			/*****************************************************************
			 * Trying to solve whitespace problem before item in linked list *
			 *****************************************************************/
			//char tab[50];
			//tab[0] = "";
			//strcat(tab, item_input);

			printf("Looking for %s\n", item_input);

			ListNodePtr personPtr = Board;
			ListNodePtr itemPtr = Board;

			while(personPtr != NULL){
				if(strcmp(personPtr->name, list_input) == 0){
					break;
				}
				personPtr = personPtr->next;
			}

			printf("Now personPtr is %s \n", personPtr->name);

			itemPtr = personPtr;
			itemPtr = itemPtr->next;

			while(itemPtr != NULL || !itemPtr->person){
				if(strcmp(itemPtr->name, item_input) == 0){
					printf("%s found!\n", item_input);
					break;
				}
				printf("Now: %s \n", itemPtr->name);
				itemPtr = itemPtr->next;
			}
	}
	fclose(fp);
	}
}

void Edit_Board(){
	int choice = 0;
	struct listnode node1, node2, node3;
	printf("Options\n"
			"1. Edit The Name Of A List\n"
			"2. Add A New List\n"
			"3. Delete A List\n"
			"4. Return To Main Menu\n"
			);
	fflush(stdout);
	printf("Enter Your Choice\n");
	fflush(stdout);
	scanf("%d", &choice);

	switch(choice){
	case 1:
		printf("Enter the name of the list to edit\n");
		fflush(stdout);
		//fgets(node1, 80, stdin);  It returns c:246:9: error: passing 'struct listnode' to parameter of incompatible type 'char *'

		printf("List Found\n");
		fflush(stdout);
		printf("Enter the new name for this list.\n");
		fflush(stdout);
		//func
		break;
	case 2:
		printf("Enter the name of the new list\n");
		fflush(stdout);
		//func
		break;
	case 3:
		printf("Enter the name of the list to delete\n");
		fflush(stdout);
		//func
		break;
	case 4:
		printf("Returning you to the main menu.\n");
		fflush(stdout);
		//main(); It returns /src/Functions3.c:267:3: error: implicit declaration of function 'main' is invalid in C99
		break;
	default:
		printf("You have entered an invalid option. Please try again.\n");
		Edit_Board();
		break;
	}
}

void Save_Board(){
	printf("Dummy function");
	fflush(stdout);
}
