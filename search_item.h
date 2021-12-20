#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int search_item(int forUpdateFunc) {
	char fItem[255], char_id[255], choice[80];
	FILE *fpointer;
	char *token;	
	int id = 0, found, lineofEntry = 0;
	
	if (!(fpointer=fopen("inventory.csv","r"))) {
		printf("\nError! Cannot find the file where inventory items are stored.");
		do { //evaluate user input
			printf("\n\nInput 'X' to return to the main menu: ");
			fgets(choice, 80, stdin);
			choice[strcspn(choice, "\n")] = 0;
			if (strlen(choice) == 1) {							
				if (choice[0] != 'X') {
					printf("\nInvalid choice! Please input 'X' to return to the main menu!");
				}
			} else {
				printf("\nInvalid choice! Please input 'X' to return to the main menu!");
				choice[0] = '0';
			}			
			fflush(stdin);	
		}while (choice[0] != 'X');
	}
	
	while (choice[0] != 'X') {
		
		if(forUpdateFunc==0){
			system("CLS");
			printf("SEARCH FOR AN INVENTORY ITEM:\n");
		}
		while ((id <= 9999 || id > 99999)) {			
			printf("\nPlease input the Item ID: ");
			fgets(char_id, 255, stdin);
			fflush(stdin);
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
				lineofEntry +=1;
				token = strtok(fItem, ","); //get the first token
				token = remove_spec(token);	
				int item_id = atoi(token);  //convert string to an integer

				if(id == item_id){
					
					if(forUpdateFunc==1){
						printf("\n\nItem found!\n");
					}
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

					if(forUpdateFunc == 1){
						fclose(fpointer);
						return lineofEntry;
					}
				}
			}
		}
		else{
		 	if(forUpdateFunc == 0){
				printf("\nCannot find Item!");
				printf("\nThere are no records of an item with the requested Item ID!");
			}
			else{
				printf("\nFailed to find Item!");
				printf("\nThe system couldn't find an item with the specified Item ID.");
				
				lineofEntry = 0;
				return lineofEntry;
			}	
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
				printf("\nInvalid choice! Please input 'X' to return to the main menu!");
				choice[0] = '0';
			}			
			fflush(stdin);	
		}while (choice[0] != 'X');
	}
	fclose(fpointer);
	return 0;
}
