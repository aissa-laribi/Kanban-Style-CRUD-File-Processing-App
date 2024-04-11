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
		fflush(stdout);
	}
}
void print_chain(ListNodePtr Board){
    while ( Board != NULL ) {

        printf( "%d %s",  Board->person, Board->name);
		fflush(stdout);
        Board = Board->next;
     }
    puts("");
	fflush(stdout);
    puts("");
	fflush(stdout);
}

void Load_Board(){

	char line[50];
	printf("Please enter the name of the file you wish to enter. Enter 'default.txt' for the default board.\n");
	fflush(stdout);

	scanf("%s",file);
	printf("%s\n", file);
	fflush(stdout);


	FILE *fp;

	if ((fp = fopen(file, "r+"))== NULL) {
		printf("File failed to be opened. Please enter the name again.\n");
		fflush(stdout);
		/*Should exit function*/
		/*main(); may work here as it'll redirect the user to the main menu to input the text file again */

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
}

int ListFound(ListNodePtr Board, char *data){

	ListNodePtr CurrentPtr = Board;

    while ( CurrentPtr  != NULL ) {
    	if(CurrentPtr ->person && strcmp(data, CurrentPtr ->name) == 0 ){
    		printf("List found\n");
    		fflush(stdout);
    		return 1;
    	}
    	if (CurrentPtr->next  == NULL){
    		printf("List not found\n");
    		fflush(stdout);
    		return 0;
    	}
    	CurrentPtr  = CurrentPtr ->next;
     }
    return 1;
}

void InsertItem(ListNodePtr Board, char *Person, char *Item){
	if(ListFound(Board, Person)){



		ListNodePtr personPtr = Board;
		ListNodePtr itemPtr = Board;
		ListNodePtr newPtr = malloc(sizeof(ListNode));
		strcpy(newPtr->name, Item);
		newPtr->person = 0;
		newPtr->next = NULL;


		while(personPtr != NULL){
			if(strcmp(personPtr->name, Person) == 0){
				break;
			}
			personPtr = personPtr->next;
		}

		itemPtr = personPtr;
		itemPtr = itemPtr->next;

		while(itemPtr != NULL){
			if(itemPtr->next == NULL){
				itemPtr->next = newPtr;
				break;
			} else if(itemPtr->next->person){
				personPtr = itemPtr->next;
				newPtr->next = personPtr;
				itemPtr->next = newPtr;
				break;
			}
			/*printf("Now: %s \n", itemPtr->name);*/
			/*fflush(stdout);*/
			itemPtr = itemPtr->next;
		}

	} else{
		printf("There is a problem, we cannot find a list starting with %s\n", Person);
		fflush(stdout);
	}
}

void Delete_Item(ListNodePtr Board, char *Person, char *Item){
	if(ListFound(Board, Person)){


			ListNodePtr personPtr = Board;
			ListNodePtr itemPtr = Board;

			while(personPtr != NULL){
				if(strcmp(personPtr->name, Person) == 0){
					break;
				}
				personPtr = personPtr->next;
			}

			itemPtr = personPtr;

			while(itemPtr != NULL){
				if(strcmp(Item, itemPtr->next->name) == 0){
					ListNodePtr TempPtr = itemPtr->next;
					itemPtr->next = itemPtr->next->next;
					free(TempPtr);
					break;
				}
				itemPtr = itemPtr->next;
			}

			} else{
				printf("There is a problem, we cannot find a list starting with %s\n", Person);
				fflush(stdout);
			}
	}
void InsertList(ListNodePtr Board, char *Person){
	if(!ListFound(Board, Person)){
		/*printf("Person passed: %s", Person); */
		/* fflush(stdout); */
		ListNodePtr personPtr = Board;
		ListNodePtr newPtr = malloc(sizeof(ListNode));


		strcpy(newPtr->name, Person);
		newPtr->person = 1;
		newPtr->next = NULL;

		while(personPtr->next != NULL){
			personPtr = personPtr->next;
			/*printf("Now: %s \n", personPtr->name);*/
			/*fflush(stdout);*/
		}
		/*printf("After loop: %s \n", personPtr->name);*/
		/*fflush(stdout);*/
		personPtr->next = newPtr;

	} else{
		printf("There is a problem, already a list starting with %s exists\n", Person);
		fflush(stdout);
	}
}
void DeleteList(ListNodePtr Board, char *Person) {


    ListNodePtr current = Board;
    ListNodePtr previous = NULL;


    while (current != NULL) {
        if (strcmp(current->name, Person) == 0) {
            if (previous == NULL) {
                current = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("List '%s' deleted successfully.\n", Person);
            fflush(stdout);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("List '%s' not found.\n", Person);
    fflush(stdout);
}



void Edit_List(){
	/*TODO:
	 *1. Edit an item
	  2. Add a new item
	  3. Delete an item
	  4. Return to main menu */

	printf("Edit %s\n", file);
	fflush(stdout);
	unsigned short int user_choice;
	char list_input[50];
	char item_input[50];
	char ch;



	printf("Enter the name of the list to edit:");
	fflush(stdout);
	scanf("%s", list_input);
	printf("Strlen after input :%lu\n", strlen(list_input));
	printf("last char = %c\n", list_input[strlen(list_input)]);
	list_input[strlen(list_input)] = ':';
	list_input[strlen(list_input)] = '\n';
	list_input[strlen(list_input)] = '\0';
	printf("Strlen after input['\n'] :%lu\n", strlen(list_input));
	printf("Looking for %s\n", list_input);
	fflush(stdout);
	/*printf("Length of %s: %lu", list_input, strlen(list_input));*/
	/*fflush(stdout);*/
	print_chain(Board);



	ListNodePtr listFinder = Board;
	while(listFinder != NULL){
		if(listFinder->person && strcmp(list_input, listFinder ->name) == 0){
			printf("LIST FOUND\n");
		}
		listFinder = listFinder->next;
	}
	LISTMENU:
			printf("Options:\n "
					"1. Edit an item\n"
					"2. Add a new item\n"
					"3. Delete an item\n"
					"4. Return to main menu\n"
					"Enter your option: ");
			fflush(stdout);
		scanf("%hd", &user_choice);
		ch = getchar();
		while(user_choice < 1 || user_choice > 4){
			if(ch == '\n'){
				puts("Invalid input");
				fflush(stdout);
				printf("Options:\n"
					   "1. Edit an item\n"
					   "2. Add a new item\n"
					   "3. Delete an item\n"
					   "4. Return to main menu\n"
					   "Enter your option: ");
				fflush(stdout);
				scanf("%hd", &user_choice);
						}
			else{
				/*Trap the unwanted characters here*/
			}
			ch = getchar();
		}

		switch(user_choice){
		char item[50];
		case 1:
			printf("Enter the name of the item to edit:\n");
			fflush(stdout);
			fgets(item_input, 50, stdin);


			strcpy(item, "	");
			strcat(item, item_input);

			printf("Looking for %s\n", item);
			fflush(stdout);
			ListNodePtr personPtr = Board;
			ListNodePtr itemPtr = Board;

			while(personPtr != NULL){
				if(strcmp(personPtr->name, list_input) == 0){
					break;
				}
				personPtr = personPtr->next;
			}

			printf("Now personPtr is %s \n", personPtr->name);
			fflush(stdout);
			itemPtr = personPtr;
			itemPtr = itemPtr->next;

			while(itemPtr != NULL || !itemPtr->person){
				if(strcmp(itemPtr->name, item) == 0){
					printf("%s found!\n", item);
					fflush(stdout);
					printf("Enter the new name:");
					fflush(stdout);
					fgets(item_input, 50, stdin);
					strcpy(item, "	");
					strcat(item, item_input);
					strcpy(itemPtr->name, item);
					break;
				}
				printf("Now: %s \n", itemPtr->name);
				fflush(stdout);
				itemPtr = itemPtr->next;
			}
			printf("Updated List:\n");
			fflush(stdout);
			print_chain(Board);
			goto LISTMENU;
		case 2:
			printf("Enter the name of the item to add:\n");
			fflush(stdout);
			fgets(item_input, 50, stdin);

			strcpy(item, "	");
			strcat(item, item_input);
			InsertItem(Board, list_input, item);
			printf("Updated List:\n");
			fflush(stdout);
			print_chain(Board);
			goto LISTMENU;
		case 3:
			printf("Enter the name of the item to delete:\n");
			fflush(stdout);
			fgets(item_input, 50, stdin);

			strcpy(item, "	");
			strcat(item, item_input);
			Delete_Item(Board, list_input, item);
			printf("Updated List:\n");
			fflush(stdout);
			print_chain(Board);
			goto LISTMENU;
		case 4:
			/*To be completed*/
			break;
	}
}

void Edit_Board(){
	int main_choice = 0;
	char list_input[50];
	/*char ch;*/
	printf("Options\n"
			"1. Edit The Name Of A List\n"
			"2. Add A New List\n"
			"3. Delete A List\n"
			"4. Return To Main Menu\n"
			);
	fflush(stdout);
	printf("Enter Your Choice\n");
	fflush(stdout);
	scanf("%d", &main_choice);

	switch(main_choice){

	case 1:

		printf("Enter the name of the list to edit\n");
		fflush(stdout);
		scanf("%s", list_input);
		list_input[strlen(list_input)] = ':';
		list_input[strlen(list_input)] = '\n';
		printf("list_input = %s", list_input);
		printf("Looking for %s", list_input);
		fflush(stdout);

		ListNodePtr personPtr = Board;
		/*ListNodePtr newPtr = malloc(sizeof(ListNode));*/
		char list[50];

		while(personPtr != NULL){
			if(strcmp(personPtr->name, list_input) == 0){
				break;
			}
			personPtr = personPtr->next;
		}

		if(ListFound(Board, list_input) == 1){
			fflush(stdout);
			printf("Enter the new name for this list.\n");
			fflush(stdout);
			fgets(list, 50, stdin);

			while(personPtr != NULL){
				if(strcmp(personPtr->name, list_input) == 0){
					printf("Enter the new name:");
					fflush(stdout);
					fgets(list_input, 50, stdin);
					strcpy(list, ":");
					strcat(list_input, list);
					strcpy(personPtr->name, list_input);
					break;
				}
				personPtr = personPtr->next;
			}

		printf("Updated List:\n");
		fflush(stdout);
		print_chain(Board);
		Edit_Board();
		}
		break;
	case 2:
		printf("Enter the name of the new list\n");
		fflush(stdout);
		scanf("%s", list_input);
		strcpy(list, ":");
		strcat(list_input, list);
		/*printf("Passing %s\n", list_input);*/
		/*fflush(stdout);*/
		InsertList(Board, list_input);
		printf("Updated List:\n");
		fflush(stdout);
		print_chain(Board);
		Edit_Board();
		break;
	case 3:

		printf("Enter the name of the list to delete\n");
		fflush(stdout);


		scanf("%s", list_input);
		list_input[strlen(list_input) ] = ':';
		list_input[strlen(list_input) ] = '\n';
		printf("list_input Edit Board : %s", list_input);
		DeleteList(Board, list_input);
		puts("Updated List");
		print_chain(Board);
		Edit_Board();
		break;
	case 4:
		printf("Returning you to the main menu.\n");
		fflush(stdout);
		break;
	default:
		printf("You have entered an invalid option. Please try again.\n");
		fflush(stdout);
		Edit_Board();
		break;
	}
}



void Save_Board(){


	char file[50];
	FILE *fp;
	printf("Enter filename.\n");
	fflush(stdout);

	scanf("%s",file);
	printf("%s\n", file);
	fflush(stdout);

	fp = fopen(file, "w");


	if (fp == NULL ) {
		printf("File failed to be opened. Please enter the name again.\n");
		fflush(stdout);
	}
	while(Board != NULL){
			fwrite(Board->name, 1, sizeof(Board->name), fp);
			printf("%s", Board->name);
			Board = Board->next;
			fflush(stdout);
		}
	fclose(fp);



}
