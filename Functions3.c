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
	printf("%s",FILE_NAME);

	FILE *fp;
	fp = fopen("default.txt", "r+");

	if (fp == NULL) {
		printf("File failed to be opened. Please enter the name again.\n");
		fflush(stdout);
		Load_Board();
	} else {
		printf("File opened successfully.\n");
		fflush(stdout);
	}

}

void Edit_List(){
	printf("Dummy function");
	fflush(stdout);
}

void Edit_Board(){
	printf("Dummy function");
	fflush(stdout);
}

void Save_Board(){
	printf("Dummy function");
	fflush(stdout);
}

