 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>

void readNsearch(const char *file_name);

 int main()
 {
     FILE *filePtr = fopen("index.html", "r");

     if(filePtr == NULL) 
     {
         fprintf(stderr, "There was a problem opening the file\n");
         perror("Leaving now!!!\n");

         exit(-1);
     }
    char buffer[20];
    printf("For best viewing make sure this window is maximized\n");
    printf("Please enter the filename you wish to read (including extension)");
    scanf("%s",buffer);
    FILE *out;
    if((out = fopen(buffer,"r")) != NULL) { // checks in read only mode if it can open the file
    //file exists
     printf("File found already: %s .... \n",buffer);
     printf("This will overwrite current file \n");
     fclose(out);
      } else
      {
        printf("Could not open file %s\n", buffer);
        fclose(out);
        exit(-1);
      }
    readNsearch(buffer);

     return 0;
 }

  void readNsearch(const char *file_name)
{
  FILE *file = fopen(file_name, "r");
  char temp[100];
  int a = 0;
  int offset[4] = {0x00,0x00,0x00,0x00};

  printf("%8s\t","offset");
  printf("\t\tHexadecimal\t\t\t\t");
  printf("%8s\n\n","Characters");

  while((fread(temp, 1, 16, file)) == 16) {
        printf("  ");

        printf("%X%X%X%X", offset[0],offset[1],offset[2],offset[3]); //printing out hex offset
        offset[3] +=16; // increamenting for each new line
        
        if(offset[3] > 0x100) {
            printf("\t"); // printf hack for removing a space (backspace), makes the output look pretty
        } else {
        printf("\t\t");
        }
      for(int i = 0; i < 16; i++) {
            if(temp[i] == 0x0A || temp[i] == 0x0D || temp[i] == 0x20 ) { // Replacing nonsense them with a .
                temp[i] = 0x2E; // I could have easily used an if statement to specify the hex range for acceptable chars
            }
      printf("%X ",temp[i]);
      }
      printf("\t");
      for(int i = 0; i < 16; i++) {
            if(temp[i] == 0x0A || temp[i] == 0x0D ||temp[i] == 0x20 ) {
                temp[i] = 0x2E;
            }

         printf("%c", temp[i]);
        }
      printf("\n");
      }
        //Clearing out temp buffer
        printf("  ");
        printf("%X%X%X%X", offset[0],offset[1],offset[2],offset[3]);
        printf("\t");
        for(int i = 0; i < 16; i++) {
        if(temp[i] == 0xd) {printf("0");} //This will fix the output of 0xd to 0x0D
        if(temp[i] == '\n') {
             
            do {
                printf("   "); // prints a space for remainder of i
                i++;
            } while(i < 16); 
            break;
        }
        printf("%X ", temp[i]);
        }
        printf("\t");
        for(int i = 0; i < 16; i++) {
            if(temp[i] == 0x20 ) { //converts spaces to .
              temp[i] = 0x2E;
            }
        if(temp[i] == '\n') {
            break;
        }
        printf("%c", temp[i]);

    }
    printf("\n");
  fclose(file);
}