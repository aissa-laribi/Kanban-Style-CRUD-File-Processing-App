#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char file[80]; /*Static variable containing the name of file and reused anywhere in the program*/

struct listnode{
	char name[50];
	struct listnode *next;
};

typedef struct listnode ListNode;
typedef ListNode *ListNodePtr;


void Display_Board(){
	/*In the Detailled specification, it says if 1 (Display board) => print default.txt*/
	char line[256];
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

void Load_Board(){

	printf("Please enter the name of the file you wish to enter. Enter 'default' for the default board.\n");
	fflush(stdout);

	scanf("%s",file);
	printf("%s\n", file);


	FILE *fp;

	if ((fp = fopen(file, "r+"))== NULL) {
		printf("File failed to be opened. Please enter the name again.\n");
		fflush(stdout);
	} else {
		printf("File opened successfully.\n");
		fflush(stdout);
	}
	fclose(fp);


}

void Edit_List(){
	/*TODO:
	 *1. Edit an item
	  2. Add a new item
	  3. Delete an item
	  4. Return to main menu */

	printf("Edit %s\n", file);
	unsigned short int user_choice;
	char input[50];
	char line[256];
	char ch;
	FILE *fp;

	if((fp = fopen(file, "r+"))== NULL) {
		printf("File failed to be opened. Please enter the name again.\n");
		fflush(stdout);
	}

	printf("Enter the name of the list to edit:");
	scanf("%s", input);
	input[strlen(input)] = ':';
	input[strlen(input)] = '\n';
	printf("Looking for %s\n", input);
	/*Testing printing input file*/

	while(fgets(line, sizeof(line), fp)){
		if(strcmp(input, line) == 0){
			printf("found\n");
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
			fgets(input, 50, stdin);
			input[strlen(input)] = '\n';
			input[strlen(input)] = '\0';
			printf("%s\n", input);
			printf("%lu\n", strlen(input));

			/*Stuck here when comparing input let say Oculus Pro and cannot match it*/
			while(fgets(line, sizeof(line), fp)){
				printf("%lu", strlen(input));
				if(strcmp(line, input) == 0){
					puts("True");
				}
			}

		}

		}
	}
	fclose(fp);


}

void Edit_Board(){
	printf("Dummy function");
	fflush(stdout);
}

void Save_Board(){
	printf("Dummy function");
	fflush(stdout);
}
