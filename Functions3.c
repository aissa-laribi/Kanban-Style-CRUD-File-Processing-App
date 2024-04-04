#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void Display_Board(){
	printf("Dummy function");
	fflush(stdout);
}

void Load_Board(){
	char FILE_NAME[80];

	printf("Please enter the name of the file you wish to enter. Enter 'default' for the default board.\n");
	fflush(stdout);
	scanf("%s", FILE_NAME);


	FILE *fp;

	if ((fp = fopen(FILE_NAME, "r+"))== NULL) {
		printf("File failed to be opened. Please enter the name again.\n");
		fflush(stdout);
	} else {
		printf("File opened successfully.\n");
		fflush(stdout);
	}

}

void Edit_List(){
	/*1. Edit an item
	  2. Add a new item
	  3. Delete an item
	  4. Return to main menu */

	struct listnode{
		char name[50];
		struct listnode *next;
	};

	unsigned short int user_choice;
	char first_name[50];
	//char ch;

	typedef struct listnode ListNode;
	typedef ListNode *ListNodePtr;

	int getc(FILE *fp);

	printf("Enter the name of the list to edit:");
	fgets(first_name, 50, stdin);

	/*Null character*/

	/*Compare fname and

	scanf("%hu", &user_choice);
	ch = getchar();
	while(user_choice < 1 || user_choice > 4){
		print
	}
	fflush(stdout);
	*/
}

void Edit_Board(){
	printf("Dummy function");
	fflush(stdout);
}

void Save_Board(){
	printf("Dummy function");
	fflush(stdout);
}

