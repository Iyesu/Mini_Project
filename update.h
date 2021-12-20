#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEN 255

int totalLines(){
	int total_lines =0;

	char lines[MAX_LEN];
	FILE * fpointer = fopen("inventory.csv", "r");
	
	while (!feof(fpointer)){
		if(fgets (lines, MAX_LEN, fpointer)!=NULL ) {
			total_lines +=1;
		}
	}
	fclose(fpointer);
	return total_lines;
}

int get_oldID(int lineFound){
    FILE *forig = fopen("inventory.csv", "rb");
	
    char line[MAX_LEN];
    char *token;

    while(lineFound!=0)
	{
  		if( fgets (line, MAX_LEN, forig)!=NULL ) {
		  	token = strtok(line, ",");
			token = remove_spec(token);
			lineFound -= 1;
			remove_quotation(token);
			
		  }
    }
	fclose(forig);
	return atoi(token);
}

int update(){

    int item_id = 0, item_quantity = 0, item_check, price_check = 0, old_id=0;;
	char item_description[255], item_date[255], char_id[255], char_quantity[255], char_price[255], choice = 'N';
	float item_price = 0;

    int lineOfEntry, countOfLines;
    char linebuffer[MAX_LEN],prevLine[MAX_LEN]="";
	
	FILE *originalFile = fopen("inventory.csv", "r");
	FILE *newFile = fopen("Updated.csv", "w+");

	system("cls");
	printf("UPDATE INVENTORY ITEM:\n");
	
    //while(choice=='Y'){
		countOfLines = totalLines();
		//printf("entries: %d", countOfLines);
        lineOfEntry = search_item(1);
		//printf("%d", lineOfEntry);
        if(lineOfEntry==0){
            printf("\nInput 'X' to return to the Main Menu:");
            scanf("%c", &choice);
			fflush(stdin);

            while(toupper(choice)!='X'){
                printf("\nInvalid Choice.");
                printf("\n\nInput 'X' to return to the Main Menu:");
	            scanf(" %c", &choice);
				fflush(stdin); 
            }
			return 0;
        }
        int x=0;

        while(!feof(originalFile)){
            x+=1;
		    fgets(linebuffer, MAX_LEN, originalFile);
		    
			
            if(x == lineOfEntry){
				while(choice=='N'){
                	while ((item_id <= 9999 || item_id > 99999)) {	
						printf("Please update the Item ID: ");
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
						printf("Please update the Item Description: ");		
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
						printf("Please update the Item Quantity: ");	
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
						printf("Please update the Expiry Date (YYYY-MM-DD) (Place '-' if no expiry): ");		
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
							printf("Please update the Price of the Item (PHP, in TWO decimal places): ");	
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
	
		        	int item_check = id_check(item_id);
					old_id = get_oldID(lineOfEntry);

		
		        	if (item_check == 1 && old_id != item_id) {
			        	printf("\nFailed to add item!\nItem with the same Item ID found!");
						printf("\nInput 'X' to return to the Main Menu:");
            			scanf("%c", &choice);
						fflush(stdin); 
						while(toupper(choice)!='X'){
                			printf("\nInvalid Choice.");
                			printf("\n\nInput 'X' to return to the Main Menu:");
	            			scanf(" %c", &choice); 
							fflush(stdin); 
            			}
            			return 0;
		        	} else {
				    
						printf("\nITEM UPDATE SUMMARY\n");
						printf("ITEM ID   ITEM DESCRIPTION    	ITEM QUANTITY   	ITEM EXPIRY DATE   	ITEM PRICE\n");
						printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						printf("%d\t\t%s\t\t%d\t\t%s\t\t%lf", item_id, item_description, item_quantity, item_date, item_price);
						printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						printf("\t\t\t\t\t\t\t\t---------------END OF LINE---------------");
						printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						//getchar();
						printf("\nAre you satisfied with the changes? Y/N:");
						choice=getchar();
						choice=toupper(choice);
						fflush(stdin); 
						//printf("choice: %c", choice);
						//getchar();
						while(choice!='Y'){
							if(choice=='N'){
								//reset values
								item_id = 0;
								item_price = 0;
								break;
							}
							printf("\nInvalid input.");
							printf("\nAre you satisfied with the changes? Y/N:");
							choice=getchar();
							choice=toupper(choice);
							fflush(stdin); 
							//printf("choice: %c", choice);
						}
						if(choice=='Y'){
							//fprintf(newFile, "%d, %s, %d, %s, %lf\n", item_id, item_description, item_quantity, item_date, item_price);
							if(x==countOfLines){
								fprintf(newFile, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"", char_id, item_description, char_quantity, item_date, char_price);
							}
							else{
								fprintf(newFile, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n", char_id, item_description, char_quantity, item_date, char_price);
							}
						}
		        	}
				}
            }
			else if(x>countOfLines){
				break;
			}
            else{
                if(strcmp(prevLine, linebuffer)==0){
					break;
				}
				else{
					fputs(linebuffer, newFile);
					strcpy(prevLine, linebuffer);
				}
         	}
			//}
        }
	    fclose(originalFile);
        fclose(newFile);

        int overwriteOrigFile=rename("inventory.csv", "old.csv");
		remove("inventory.csv");
		remove("old.csv");
        int overwriteFile=rename("Updated.csv", "inventory.csv");
        if(!overwriteFile)
        {
            printf("\nInventory Entry Updated Succesfully\n");
			printf("Input 'X' to return to the Main Menu:");
            scanf("%c", &choice);
			fflush(stdin);
				while(toupper(choice)!='X'){
            		printf("\nInvalid Choice.");
                	printf("\n\nInput 'X' to return to the Main Menu:");
	            	scanf(" %c", &choice);
					fflush(stdin); 
            	}
        }
        else
        {
            printf("Error Updating Entry. CSV File might be open or still in use.\n");
		    system("pause");
        }

	return 0;
}