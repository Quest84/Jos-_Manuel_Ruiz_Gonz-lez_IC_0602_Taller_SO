#include <stdio.h>
#include <string.h>

int main(void)
{
   FILE * pFile;
   char mystring [100];
   char* pch;

   pFile = fopen ("output.txt" , "r");
   if (pFile == NULL) perror ("Error opening file");
   else {
     while ( fgets (mystring , 100 , pFile) != NULL )
       printf ("%s", mystring);
     fclose (pFile);
   }

   pFile = fopen ("input.txt" , "r");
   if (pFile == NULL) perror ("Error opening file");
   else {
     while ( fgets (mystring , 100 , pFile) != NULL ) {
       printf ("%s", mystring);
       pch = strtok (mystring," ");
       while (pch != NULL)
       {
         printf ("%s\n",pch);
         pch = strtok (NULL, " ");
       }
     }
     fclose (pFile);
   }

   return 0;
}
