#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int id_check(int item_id) {
	char fItem[255];
	int retVal = 0;
	FILE * fpointer = fopen("inventory.csv", "r");
	
	while (fgets(fItem, 255, fpointer)) {
		char* token = strtok(fItem, ",");
		if (token) {
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


int search_item() {
	char fItem[255];
	FILE *fpointer;
	char *token, choice;
	fpointer=fopen("Inventory.csv","r");
	int id, found;


	printf("SEARCH FOR AN INVENTORY ITEM:\n\n");
	printf("Please input the Item ID (5 Digits MAX): "); 
	scanf("%d", &id);
	int item_check = id_check(id);
	
	if (item_check == 1) {
		while (fgets(fItem, 255, fpointer) !=NULL) 
	{
	token = strtok(fItem, ","); //get the first token
	int item_id = atoi(token);  //convert string to an integer
		if(id == item_id){
			printf("ITEM ID   ITEM DESCRIPTION    	ITEM QUANTITY   	ITEM EXPIRY DATE   	ITEM PRICE\n");
			printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			while(token != NULL)
			{
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
		printf("\nThere are no records of an item with the requested Item ID.!");
	}
	
	fclose(fpointer);
	return (0); 
}

int main() {
	search_item();
}