#include <stdio.h>
#include <string.h>

//option can either be 1 for displaying all values or a specfic id number to be displayed
void viewInventory(int option){
	//i is for looping, word_count counts the number of words in a line, flag detects if an id has been found
	//ch_cmp compares the string between specific id number and every id in the Inventory file
	int i, word_count=0,flag=0,ch_cmp,size;
	//words store each word of the file, id is the string equivalent of the id number, exit stores exit character 
    //in the event of an error
	char words[50],id[5], ch, exit, choice[80]; 
	
	if(option==1){
		system("CLS");
		printf("FULL ITEM LIST: \n");
	}
	
	FILE *fp;
	fp=fopen("inventory.csv","r");
	//checks if file is empty, will exit when it is
	if (NULL != fp) {
    	fseek (fp, 0, SEEK_END);
    	size = ftell(fp);
	}
    if (0 == size) {
        printf("\nCannot display item list!\n");
        printf("Inventory list is empty!\n\n");
        while(1){
        	printf("Input 'X' to return to the main menu: ");
			scanf(" %c",&exit);
        	printf("\n");
        	fflush(stdin);
        	if(exit=='x'||exit=='X'){
        		return;
			}
		}
	}
	fclose(fp);
	fp=fopen("inventory.csv","r");
	
	printf("\n%-40s%-40s%-40s%-40s%s","Item ID","Item Description","Quantity","Expiration Date","Price(PHP)");
	printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	
	//first if displays every word between " "
	//second if compares the id argument to every id in the file and prints that specific line if available.
	if(option==1){
		while(!feof(fp)){
			while(EOF!=(ch=fgetc(fp))) 
				if(ch=='"') break;
			
			for(i=0; EOF!=(ch=fgetc(fp)); i++){
				if(ch=='"'){
					word_count++;
					break;
				}
				words[i]=ch;
			}
			printf("%-40s", words);
			if(word_count==5){
				printf("\n");
				word_count=0;
			}
			memset(words,0,50);
		}
	}else if(option>9999&&option<=99999){
		itoa(option,id,10);
		while(!feof(fp)){
			while(EOF!=(ch=fgetc(fp))) 
				if(ch=='"') break;
			
			for(i=0; EOF!=(ch=fgetc(fp)); i++){
				if(ch=='"'){
					word_count++;
					break;
				}
				words[i]=ch;
			}
			if(word_count==1){
				ch_cmp=0;
				for(i=0;i<5;i++){
					if(id[i]==words[i]){
						ch_cmp+=1;
					}
					
					if(ch_cmp==5){
						ch_cmp=0;
						flag=1;
					}
				}
			}
			if(flag){
				printf("%-40s",words);
			}
			if(word_count==5){
				if(flag){
					printf("\n");
					flag=0;
				}
				word_count=0;
			}
			memset(words,0,50);
		}
	}
	printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t---------------END OF LINE---------------");
	printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	fclose(fp);
	
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