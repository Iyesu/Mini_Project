#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_quotation(char value[255]) {
	const char *ptr = value;
	char *ptr2 = value;
	
	do {
		if (*ptr != '"') {
			*ptr2++ = *ptr;
		}
	} while (*ptr++);
}

void remove_comma(char value[255]) {
	const char *ptr = value;
	char *ptr2 = value;
	
	do {
		if (*ptr != ',') {
			*ptr2++ = *ptr;
		}
	} while (*ptr++);
}

int push_item(char char_id[255], char item_description[255], char char_quantity[255], char item_date[255], char char_price[255]) {
	int retVal = 0;
	
	FILE * fpointer = fopen("inventory.csv", "a");
	retVal = fprintf(fpointer, "\n\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"", char_id, item_description, char_quantity, item_date, char_price);
	fclose(fpointer);
	
	return retVal;
}

int id_check(int item_id) {
	char fItem[255];
	int retVal = 0;
	FILE * fpointer = fopen("inventory.csv", "r");
	
	while (fgets(fItem, 255, fpointer)) {
		char* token = strtok(fItem, ",");
		if (token) {
			remove_quotation(token);
			int n = atoi(token);
			if (n == item_id) {
				retVal = 1;
				break;
			}
		}
	}
	fclose(fpointer);
	return retVal;
}

int date_check(char item_date[255]) {
	int returnVal = 0;
	for (int i = 0; i < strlen(item_date); i++) {
		if (i != 4 && i != 7) {
			if (isdigit(item_date[i]) == 0) {
				returnVal = 1;
				break;
			}
		} else {			
			if (item_date[i] != '-') {
					returnVal = 1;
					break;
			}
		}
	}
	return returnVal;
}

int decimal_check(char value[255]) {
	int trigger = 0, count = 0, retVal = 0;
	for (int i = 0; i < strlen(value); i++) {
		if (isdigit(value[i]) == 0) {
			if (value[i] == '.' && trigger == 0) {
			    trigger = 1;
			} else {
			    retVal = 1;
			    break;
			}
		} else {
		    if (trigger == 1) {
		        count++;
		    }
		}
	}
	if (count != 2) {
		retVal = 1;
	}
    
    return retVal;
}
