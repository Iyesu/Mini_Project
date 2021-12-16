#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "functions.h"

void add_file() {
	int item_id, item_quantity = 0, item_check, price_check = 0;
	char item_description[255], item_date[255], char_id[255], char_quantity[255], char_price[255], choice = 'Y';
	float item_price = 0;
	
	while (choice == 'Y') {
		system("CLS");	
		item_id = 0;
		item_price = 0;
		printf("ADD INVENTORY ITEM: \n\n");	
		while ((item_id <= 9999 || item_id > 99999)) {	
			printf("Please input the Item ID: ");
			fgets(char_id, 255, stdin);
			item_id = atoi(char_id);
			if ((floor(log10(abs(item_id))) + 1) == (strlen(char_id)-1)) { //evaluate if number, atoi will only take the first few integers or 0 and not character
				if (item_id <= 9999 || item_id > 99999) {
					printf("\nInvalid Item ID! Item ID should be a 5 digit number.\n\n");
				}
			} else{
				printf("\nInvalid Item ID! Item ID should be a 5 digit number.\n\n");
			}	
			char_id[strcspn(char_id, "\n")] = 0;				
			fflush(stdin); //clear input buffer
		}
		do {
			printf("Please input the Item Description: ");		
			fgets(item_description, 255, stdin); //fix the newline bug later
			if (item_description[0] != '\n') {
				item_description[strcspn(item_description, "\n")] = 0; //remove fgets \n
				remove_comma(item_description);
			} else {
				printf("\nItem description cannot be empty!\n\n");
			}
			fflush(stdin); //clear input buffer
		}while (item_description[0] == '\n');	
		item_check = 1;
		while (item_check == 1) {
			item_check = 0;			
			printf("Please input the Item Quantity: ");	
			fgets(char_quantity, 255, stdin);
			item_quantity = atoi(char_quantity);
			if (item_quantity > 0) {				
				if ((floor(log10(abs(item_quantity))) + 1) != (strlen(char_quantity)-1)) {
					printf("\nInvalid Quantity! Make sure that the quantity is a number and is non-zero and non-negative.\n\n");
					item_check = 1;
				}
			} else {
				printf("\nInvalid Quantity! Make sure that the quantity is a number and is non-zero and non-negative.\n\n");
				item_check = 1;
			}
			char_quantity[strcspn(char_quantity, "\n")] = 0;
			fflush(stdin); //clear input buffer  
		}
		int dateCheck = 1;
		while (dateCheck == 1) {
			printf("Please input the Expiry Date (YYYY-MM-DD) (Place '-' if no expiry): ");		
			fgets(item_date, 255, stdin);			
			item_date[strcspn(item_date, "\n")] = 0; //remove fgets \n
			if (strcmp(item_date, "-") == 0) {
				dateCheck = 0;
			} else {
				if (strlen(item_date) < 10 || strlen(item_date) > 10) {
					dateCheck = 1;
				} else {					
					dateCheck = date_check(item_date);
				}				
			}					
			if (dateCheck == 1) {
				printf("\nInvalid Date! Please make sure that the date follows the YYYY-MM-DD format and does not contain any invalid characters.\n\n");
			}
			fflush(stdin);	
		}
		while(item_price == 0) {	
			do {					                                	
				printf("Please input the Price of the Item (PHP, in TWO decimal places): ");	
				fgets(char_price, 255, stdin);
				if (char_price[0] == '\n') {
					printf("\nPrice of item cannot be empty!\n\n");
				}
			}while(char_price[0] == '\n');		
			char_price[strcspn(char_price, "\n")] = 0;	
			price_check = decimal_check(char_price);
			
			if (price_check == 1) {
				printf("\nInvalid Price! Make sure the the price is a non-negative, non-zero number and is in TWO decimal places.\n\n");
			} else {				
				item_price = atof(char_price);	
			}
			fflush(stdin);
		}  		                           
	
		item_check = id_check(item_id);
		
		if (item_check == 1) {
			printf("\nFailed to add item!\nItem with the same Item ID found!");
		} else {
			int toFile = push_item(char_id, item_description, char_quantity, item_date, char_price);
			if (toFile > 0) {
				printf("\nItem successfully added!");
			} else {
				printf("\nFailed to add item!\nAn error occured while trying to add the item.");
			}
		}
		printf("\n\nDo you want to add another item? Y/N: ");
		scanf(" %c", &choice);		
		fflush(stdin);
	}  
	printf("\n\n");                                                                                                          
}