#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void search_item() {
	char fItem[255], char_id[255], choice[80];
	FILE *fpointer;
	char *token;
	fpointer=fopen("inventory.csv","r");
	int id = 0, found;

	while (choice[0] != 'X') {
		system("CLS");	
		printf("SEARCH FOR AN INVENTORY ITEM:\n\n");
		while ((id <= 9999 || id > 99999)) {			
			printf("Please input the Item ID: ");
			fgets(char_id, 255, stdin);
			id = atoi(char_id);
			if ((floor(log10(abs(id))) + 1) == (strlen(char_id)-1)) { //evaluate if number, atoi will only take the first few integers or 0 and not character
				if (id <= 9999 || id > 99999) {
					printf("\nInvalid Item ID! Item ID should be a 5 digit number.\n\n");					
					id = 0; //reset item_id				
				}
			} else{
				printf("\nInvalid Item ID! Item ID should be a 5 digit number.\n\n");				
				id = 0; //reset item_id				
			}	
			char_id[strcspn(char_id, "\n")] = 0;
			fflush(stdin); //clear input buffer
		}
		
		int item_check = id_check(id);
		if (item_check == 1) {
			while (fgets(fItem, 255, fpointer)) 
			{
				token = strtok(fItem, ","); //get the first token
				token = remove_spec(token);	
				int item_id = atoi(token);  //convert string to an integer
				if(id == item_id){
					printf("ITEM ID\t\tITEM DESCRIPTION\tITEM QUANTITY\tITEM EXPIRY DATE\tITEM PRICE\n");
					printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					while(token)
					{												
						remove_quotation(token);						
						printf("%s\t\t", token);
						token = strtok(NULL, ",");
					}
					printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("\t\t\t\t\t\t\t\t---------------END OF LINE---------------");
					printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				}
			}
		}
		else{
		 	printf("\nCannot find Item!");
			printf("\nThere are no records of an item with the requested Item ID!");
		}
		
		do { //evaluate user input
			printf("\n\nInput 'X' to return to the main menu: ");
			fgets(choice, 80, stdin);
			choice[strcspn(choice, "\n")] = 0;
			if (strlen(choice) == 1) {							
				if (choice[0] != 'X') {
					printf("\nInvalid choice! Please input 'X' to return to the main menu!");
				}
			} else {
				printf("\nInvalid choice! Please input 'X to return to the main menu!");
				choice[0] = '0';
			}			
			fflush(stdin);	
		}while (choice[0] != 'X');
	}
	fclose(fpointer);
}