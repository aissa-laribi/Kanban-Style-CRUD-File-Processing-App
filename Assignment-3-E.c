#include <stdio.h>
#include <stdlib.h>
#include "Functions3.h"

 /* _   ______  ___    __ 
   / | / / __ \/   |  / / 
  /  |/ / /_/ / /| | / /  
 / /|  / _, _/ ___ |/ /___
/_/ |_/_/ |_/_/  |_/_____/
                          
*/

int main(void) {
	int choice = 0;

	printf("Menu:\n1. Display Board\n2. Load Board From File\n3. Edit List\n4. Edit Board\n5. Save Board To A File\n6. Quit\nEnter Your Choice (1-6)\n");
	fflush(stdout);
	scanf("%d", &choice);

	switch(choice){
	case 1:
		Display_Board();
		main();
		break;
	case 2:
		Load_Board();
		main();
		break;
	case 3:
		Edit_List();
		break;
	case 4:
		Edit_Board();
		break;
	case 5:
		Save_Board();
		main();
		break;
	case 6:
		printf("Exiting Program.");
		fflush(stdout);
		break;
	default:
		printf("You have entered an invalid choice. Please try again.\n");
		fflush(stdout);
		main();
		break;
	}

}
