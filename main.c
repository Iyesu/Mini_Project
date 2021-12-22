#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "add_item.h"
#include "viewInventory.h"
#include "update.h"
#include "search_item.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void main() {
	int result_check;
	char choice[80];
	
	while (toupper(choice[0]) != 'X') {
		system("CLS");
		printf("MAIN MENU:\n");
		printf("[A] Add Inventory Item\n");
		printf("[B] Update Inventory Item\n");
		printf("[C] View Inventory List\n");
		printf("[D] Search for an Inventory Item\n");
		printf("[X] Exit Program\n\n");
		printf("Please input choice: ");
		fgets(choice, 80, stdin);
		choice[strcspn(choice, "\n")] = 0;
		//scanf(" %s%*[ \t]", &choice);	
		fflush(stdin);
		if (strlen(choice) == 1) {
			switch(toupper(choice[0])) {	
				case 'A':						
					add_file();
					break;
				case 'B':
					//update inventory item
					update();
					break;
				case 'C':
					//view inventory list
					viewInventory(1);
					//getch();
					break;
				case 'D':
					//search for an inventory item
					search_item(0);		
					break;
				case 'X':
					printf("\nThank you for using the program!\nProgram now closing.");
					break;
				default:
					printf("\nInvalid input! Please enter a valid input!\n\n");
					system("pause");
					break;                                                   
			}
		} else {
			printf("\nInvalid input! Please enter a valid input!\n\n");
			system("pause");
		}
	} 
}