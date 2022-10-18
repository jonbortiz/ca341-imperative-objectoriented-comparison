#include <stdio.h>
#include <stdlib.h>

struct Phonebook
{
		char name[30];
		char address[50];
		int phone_number; 
};

// example line - susan, 13 glasnevin avenue, 0867450643
void read_file() {
   FILE *details;
   char content;

   details = fopen("details.txt", "r");
   if(details == NULL)
   {
       printf("File is empty \n");
       exit(0);
   }

   content =  fgetc(details);
   while(content != EOF){
        printf("%c", content);
        content = fgetc(details);
   }

   fclose(details);
}

int main(){
    read_file();
    return 0;
}