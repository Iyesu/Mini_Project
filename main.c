#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "add_item.h"
#include "viewInventory.h"
#include "update.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void main() {
	char choice;	
	
	while (choice != 'X') {
		system("CLS");
		printf("MAIN MENU:\n");
		printf("[A] Add Inventory Item\n");
		printf("[B] Update Inventory Item\n");
		printf("[C] View Inventory List\n");
		printf("[D] Search for an Inventory Item\n");
		printf("[X] Exit Program\n\n");
		printf("Please input choice: ");
		scanf(" %c", &choice);
		        
		switch(choice) {
			case 'A':				
				getchar();
				add_file();
				break;
			case 'B':
				//update inventory item
				update();
				break;
			case 'C':
				//view inventory list
				printf("I'm in.");
				viewInventory(1);
				getch();
				break;
			case 'D':
				//search for an inventory item
				search_item();
				break;
			case 'X':
				printf("\nThank you for using the program!\nProgram now closing.");
				break;
			default:
				printf("\nInvalid input! Please enter a valid input!\n\n");
				system("pause");
				break;                                                   
		}
		fflush(stdin);
	} 
}