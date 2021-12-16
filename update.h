#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEN 255

int search(){
    FILE *forig = fopen("inventory.csv", "rb");
    //FILE *fnew = fopen("update.csv", "w");

    int id_line = 0;
    char findID[6];
    char line[MAX_LEN];
    char *token,*IDStr;
    char *dump;
    char currentID[6];
    char checkID[6]="\"";

    system("cls");
    getchar();
    printf("Input ID:");
    fgets(findID, 6, stdin);
	getchar();
    printf("%s\n", findID);
    //strcat(findID, checkID);

	//printf("First cat %s\n", findID);
    //strcat(checkID, findID);
	//printf("Second cat %s\n", checkID);

    int lineOfEntry =0;
    while(!feof(forig))
	{
  		if( fgets (line, MAX_LEN, forig)!=NULL ) {
            
            token = strtok(line, ",");
			lineOfEntry+=1;
			printf("%s\n", token);
            if(strcmp(findID, token)==0){
                printf("Item Found!");
                fclose(forig);
				return lineOfEntry;
            }
        }
    }
	lineOfEntry=0;
    fclose(forig);

    if(lineOfEntry==0){
        printf("Error: Item does not exist.");
        return 0;
    }
    else{
        return lineOfEntry;
    }
}

void update(){

    int item_id = 0, item_quantity = 0, item_check;
	char item_description[20], item_date[11], choice = 'Y';
	float item_price = 0;

    int lineOfEntry;
    char linebuffer[MAX_LEN],prevLine[MAX_LEN]="";
	
	FILE *originalFile = fopen("inventory.csv", "r");
	FILE *newFile = fopen("Updated.csv", "w+");
	
    while(choice=='Y'){
        lineOfEntry = search();

        if(lineOfEntry==0){
            printf("\nFailed to find item.\n");
            printf("The system couldn't find an item with the specified Item ID.\n");

            printf("Input 'X' to return to the Main Menu:");
            scanf("%c", &choice);

            while(choice!='X'){
                printf("\nInvalid Choice.");
                printf("\n\nInput 'X' to return to the Main Menu:");
	            scanf(" %c", &choice); 
            }
            break;
        }
        int x=0;
        //checkEOF=fgetc(originalFile);

        while(!feof(originalFile)){
            x+=1;
		    //checkEOF=fgetc(originalFile);

		    fgets(linebuffer, MAX_LEN, originalFile);
		    printf("Current Line is: %s\n", linebuffer);

            if(x == lineOfEntry){
                while ((item_id <= 9999 || item_id > 99999)) {	
			        printf("Please input the Item ID: ");
			        scanf(" %d", &item_id);		
			        if (item_id <= 9999 || item_id > 99999) {
			            printf("\nInvalid Item ID! Item ID should be 5 digit number.\n\n");
			        }							
			        fflush(stdin); //clear input buffer

					
		
		        	if (id_check(item_id) == 1) {
			        	printf("\nFailed to add item!\nItem with the same Item ID found!\n");

						printf("Input 'X' to return to the Main Menu:");
            			scanf("%c", &choice);

						while(choice!='X'){
                			printf("\nInvalid Choice.");
                			printf("\n\nInput 'X' to return to the Main Menu:");
	            			scanf(" %c", &choice); 
            			}
            			return 0;
					}
		        }		
		        printf("Please input the Item Description: ");		
		        fgets(item_description, 20, stdin); //fix the newline bug later
		        item_description[strcspn(item_description, "\n")] = 0; //remove fgets \n
		        item_check = 1;
		        while (item_check == 1) {
			        item_check = 0;			
			        printf("Please input the Item Quantity: ");	
			        scanf(" %d", &item_quantity);
			        if (item_quantity <= 0) {
				        printf("\nInvalid Quantity! Make sure that the quantity is a number and is non-zero and non-negative.\n\n");
				        item_check = 1;
				        getchar();
			        }   
			        fflush(stdin); //clear input buffer  
		        }
		        int dateCheck = 1;
		        while (dateCheck == 1) {
			        printf("Please input the Expiry Date (YYYY-MM-DD) (Place '-' if no expiry): ");		
			        fgets(item_date, 11, stdin);			
			        item_date[strcspn(item_date, "\n")] = 0; //remove fgets \n
			        if (strcmp(item_date, "-") == 0) {
				        dateCheck = 0;
			        } else {
				        if (strlen(item_date) < 10) {
					        dateCheck = 1;
				        } else {					
					        dateCheck = date_check(item_date);
				        }				
			        }					
			        if (dateCheck == 1) {
				        printf("\nInvalid Date! Please make sure that the date follows the YYYY-MM-DD format and does not contain any invalid characters.\n\n");
			        }	
		        }
		        while(item_price == 0) {			                                	
			        printf("Please input the Price of the Item (PHP, in two decimal places): ");	
			        scanf(" %f", &item_price);
			        if (item_price <= 0) {
				        printf("\nInvalid Price! Make sure that the price is a number and is non-zero and non-negative!\n");
				        item_price = 0;
			        }
			        fflush(stdin);
		        }  		                           
	
		        int item_check = id_check(item_id);
		
		        if (item_check == 1) {
			        printf("\nFailed to add item!\nItem with the same Item ID found!");
		        } else {
				    fprintf(newFile, "%d, %s, %d, %s, %lf\n", item_id, item_description, item_quantity, item_date, item_price);
				    //printf("PLEASE CHECK");
			    /*int toFile = update_item(item_id, item_description, item_quantity, item_date, item_price);
			    if (toFile > 0) {
				    printf("\nItem successfully added!");
			    } else {
				    printf("\nFailed to add item!\nAn error occured while trying to add the item.");
			    }*/
		        }
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
        }
	    fclose(originalFile);
        fclose(newFile);
		remove("old.csv");
	    int overwriteFileOrig=rename("inventory.csv", "old.csv");
        int overwriteFile=rename("Updated.csv", "inventory.csv");
        if(!overwriteFile)
        {
            printf("%s", "Entry Updated Succesfully\n");
		    system("pause");
        }
        else
        {
            printf("Error Updating Entry\n");
		    system("pause");
        }
        
        /*printf("\n\nDo you want to add another item? Y/N: ");
	    scanf(" %c", &choice);
        
        while(choice!='Y'&&choice!='N'){
            printf("\nInvalid Choice.");
            printf("\n\nDo you want to add another item? Y/N: ");
	        scanf(" %c", &choice);
        }*/
    }
    printf("\n\n");
}