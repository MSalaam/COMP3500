#include <stdio.h>

#define ALPHABETSIZE 26 //The total number of alphabetical letter from a - z (case insensitive)

#define SPECIALCHARSIZE 5 // The number of these special characters ',' '.' ';' ':' '!'

void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[]);

void specialcharcount(char *path, char *filetowrite, int charfreq[]);

#include <stdio.h>

#include <dirent.h>

#include <string.h>


void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])

{

   DIR *d;

   char *filename;

   char *fil;

   struct dirent *dir; //directory opening process

   d = opendir(path);

   if(d != NULL) {
   
      while((dir = readdir(d)) != NULL) {
      
         filename = dir->d_name; //assigns current name to string filename
      
         size_t t = strlen(filename) - 3; //checks for .txt extentsion
      
         int ctr = 0;
      
         while(t < strlen(filename)) {
         
            if(!(filename[t] == 't' || filename[t] == 'x'))
            
               continue;
            
            else {
            
               ctr++; //adds the current letter to a counter
            
            }
         
            t++;
         
         }
      
         if(ctr == 3) { //counter will only be 3 if "txt" is read
         
            fil = dir->d_name; //immediately stores validated file to be read
         
            char p[256];
         
            strcpy(p, path); //concatenates the full data directory to p
         
            strcat(p, "/");
         
            strcat(p, fil);
         
            FILE *f = fopen(p, "r"); //opens the file path for reading
         
            if(f == NULL) { //can't open file, abort
            
               return;
            
            }
         
            int c = fgetc(f); //grabs the first character
         
            while(!feof(f)) {
            
               if((c >= 65) && (c <= 90)) //checks if char's ascii value is uppercase, and changes it to lowercase
               
                  c = c + 32;
            
               if((c >= 97) && (c <= 122)) { //if alphabet letter is found
               
                  alphabetfreq[c - 97] = (long) alphabetfreq[c - 97] + 1; //increments desired character counter. c-97 corresponds to each lowercase's location in the array
               
               }
            
               c = fgetc(f); //re-initializes fgetc for next character in while loop
            
            }
         
         
         
            fclose(f);
         
            FILE *g = fopen(filetowrite, "w"); //opens result.txt for writing
         
            for(int i = 0; i < 26; i++) { //loops through entire alphabetfreq
            
               fprintf(f, "%c -> %ld\n", (char)(i+97), alphabetfreq[i]); //formatted writing
            
            }
         
         
         
            fclose(g);
         
         }
      
      }
   
   }

   closedir(d); //close directory

}

#include <stdio.h>

#include <dirent.h>

#include <string.h>

void specialcharcount(char *path, char *filetowrite, int charfreq[])

{

   DIR *d;

   char *filename;

   char *fil; //stored filename

   struct dirent *dir; //directory opening process

   d = opendir(path);

   if(d != NULL) {
   
      while((dir = readdir(d)) != NULL) {
      
         filename = dir->d_name; //assigns current name to string filename
      
         size_t t = strlen(filename) - 3; //checks extension for .txt
      
         int ctr = 0;
      
         while(t < strlen(filename)) {
         
            if(!(filename[t] == 't' || filename[t] == 'x'))
            
               continue;
            
            else {
            
               ctr++; //adds the current letter to a counter
            
            }
         
            t++;
         
         }
      
         if(ctr == 3) { //counter will only be 3 if "txt" is read
         
            fil = dir->d_name; //once file checks out, it is immediately read. Using an array has lead to several issues such as data corruption, so I switched to this.
         
            char p[256];
         
            strcpy(p, path); //concatenates the entire filepath to p
         
            strcat(p, "/");
         
            strcat(p, fil);
         
            FILE *f = fopen(p, "r"); //opens the file path for reading
         
            if(f == NULL) { //can't open file, abort
            
               return;
            
            }
         
            int c = fgetc(f); //grabs the first character
         
            while(!feof(f)) {
            
               if(c == 44) {
               
                  charfreq[0] = (long) charfreq[0] + 1; //increments desired character counter
               
               }
               
               else if(c == 46) {
               
                  charfreq[1] = (long) charfreq[1] + 1;
               
               }
               
               else if(c == 58) {
               
                  charfreq[2] = (long) charfreq[2] + 1;
               
               }
               
               else if(c == 59) {
               
                  charfreq[3] = (long) charfreq[3] + 1;
               
               }
               
               else if(c == 33) {
               
                  charfreq[4] = (long) charfreq[4] + 1;
               
               }
            
               c = fgetc(f); //re-initializes fgetc for next character in while loop
            
            }
         
         
         
            fclose(f); //close
         
            FILE *g = fopen(filetowrite, "w"); //opens result.txt for writing
         
            fprintf(f, ", -> %ld\n", charfreq[0]); //formatted writing
         
            fprintf(f, ". -> %ld\n", charfreq[1]);
         
            fprintf(f, ": -> %ld\n", charfreq[2]);
         
            fprintf(f, "; -> %ld\n", charfreq[3]);
         
            fprintf(f, "! -> %ld\n", charfreq[4]);
         
            fclose(g);
         
         
         
         }
      
      }
   
   }

   closedir(d); //close directory

  

}

#include <stdio.h>

#include <dirent.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

#include<unistd.h>

#include <stdbool.h>

void displayalphabetfreq(long charfreq[], int size)

{

   for(int i = 0; i < size; i++)
   
   {
   
      printf("%c -> %d\n", (char)(i+97), charfreq[i]);
   
   }

}

int main()

{

  

   char *path = "../data"; // the data *.txt files are under this folder

   char *filetowrite = "result.txt"; // the frequency of all alphabetical letters will be written in this file

  

   long alphabetfreq[ALPHABETSIZE] = {0}; // array to store the frequency of each alphablet letter

  

  

   alphabetlettercount(path, filetowrite, alphabetfreq); // process the data files

  

   displayalphabetfreq(alphabetfreq, ALPHABETSIZE); // print the frequency stored in the array to output screen

}

void displayspecialcharfreq(long charfreq[], int size)

{  

   for(int i = 0; i < size; i++)
   
   {
   
      switch(i)
      
      {
      
         case 0:
         
            printf(", -> %d\n", charfreq[i]);
         
            break;
      
         case 1:
         
            printf(". -> %d\n", charfreq[i]);
         
            break;
      
         case 2:
         
            printf(": -> %d\n", charfreq[i]);
         
            break;
      
         case 3:
         
            printf("; -> %d\n", charfreq[i]);
         
            break;
      
         case 4:
         
            printf("! -> %d\n", charfreq[i]);
         
            break;
      
      }   
   
   }

}

int main()

{

   char *path = "../data"; // the path of the directory including the *.txt files to be processed

   char *filetowrite = "specialresult.txt"; // the frequency of all alphabetical letters will be written in this file

  

   long charfreq[SPECIALCHARSIZE] = {0}; // array to store the frequency of 5 special characters

  

   specialcharcount(path, filetowrite, charfreq); // count the frequency of special characters and write into file

  

   displayspecialcharfreq(charfreq, SPECIALCHARSIZE); // print the array to output screen  

}

#include <stdio.h>

#define ALPHABETSIZE 26 //The total number of alphabetical letter from a - z (case insensitive)

#define SPECIALCHARSIZE 5 // The number of these special characters ',' '.' ';' ':' '!'

void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[]);

void specialcharcount(char *path, char *filetowrite, long charfreq[]);

#include <stdio.h>

#include <dirent.h>

#include <string.h>

void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])

{

   DIR *d;

   char *filename;

   char *fil;

   struct dirent *dir; //directory opening process

   d = opendir(path);

   if(d != NULL) {
   
      while((dir = readdir(d)) != NULL) {
      
         filename = dir->d_name; //assigns current name to string filename
      
         size_t t = strlen(filename) - 3; //checks for .txt extentsion
      
         int ctr = 0;
      
         while(t < strlen(filename)) {
         
            if(!(filename[t] == 't' || filename[t] == 'x'))
            
               continue;
            
            else {
            
               ctr++; //adds the current letter to a counter
            
            }
         
            t++;
         
         }
      
         if(ctr == 3) { //counter will only be 3 if "txt" is read
         
            fil = dir->d_name; //immediately stores validated file to be read
         
            char p[256];
         
            strcpy(p, path); //concatenates the full data directory to p
         
            strcat(p, "/");
         
            strcat(p, fil);
         
            FILE *f = fopen(p, "r"); //opens the file path for reading
         
            if(f == NULL) { //can't open file, abort
            
               return;
            
            }
         
            int c = fgetc(f); //grabs the first character
         
            while(!feof(f)) {
            
               if((c >= 65) && (c <= 90)) //checks if char's ascii value is uppercase, and changes it to lowercase
               
                  c = c + 32;
            
               if((c >= 97) && (c <= 122)) { //if alphabet letter is found
               
                  alphabetfreq[c - 97] = (long) alphabetfreq[c - 97] + 1; //increments desired character counter. c-97 corresponds to each lowercase's location in the array
               
               }
            
               c = fgetc(f); //re-initializes fgetc for next character in while loop
            
            }
         
         
         
            fclose(f);
         
            FILE *g = fopen(filetowrite, "w"); //opens result.txt for writing
         
            for(int i = 0; i < 26; i++) { //loops through entire alphabetfreq
            
               fprintf(f, "%c -> %ld\n", (char)(i+97), alphabetfreq[i]); //formatted writing
            
            }
         
         
         
            fclose(g);
         
         }
      
      }
   
   }

   closedir(d); //close directory

}

#include <stdio.h>

#include <dirent.h>

#include <string.h>

void specialcharcount(char *path, char *filetowrite, long charfreq[])

{

   DIR *d;

   char *filename;

   char *fil; //stored filename

   struct dirent *dir; //directory opening process

   d = opendir(path);

   if(d != NULL) {
   
      while((dir = readdir(d)) != NULL) {
      
         filename = dir->d_name; //assigns current name to string filename
      
         size_t t = strlen(filename) - 3; //checks extension for .txt
      
         int ctr = 0;
      
         while(t < strlen(filename)) {
         
            if(!(filename[t] == 't' || filename[t] == 'x'))
            
               continue;
            
            else {
            
               ctr++; //adds the current letter to a counter
            
            }
         
            t++;
         
         }
      
         if(ctr == 3) { //counter will only be 3 if "txt" is read
         
            fil = dir->d_name; //once file checks out, it is immediately read. Using an array has lead to several issues such as data corruption, so I switched to this.
         
            char p[256];
         
            strcpy(p, path); //concatenates the entire filepath to p
         
            strcat(p, "/");
         
            strcat(p, fil);
         
            FILE *f = fopen(p, "r"); //opens the file path for reading
         
            if(f == NULL) { //can't open file, abort
            
               return;
            
            }
         
            int c = fgetc(f); //grabs the first character
         
            while(!feof(f)) {
            
               if(c == 44) {
               
                  charfreq[0] = (long) charfreq[0] + 1; //increments desired character counter
               
               }
               
               else if(c == 46) {
               
                  charfreq[1] = (long) charfreq[1] + 1;
               
               }
               
               else if(c == 58) {
               
                  charfreq[2] = (long) charfreq[2] + 1;
               
               }
               
               else if(c == 59) {
               
                  charfreq[3] = (long) charfreq[3] + 1;
               
               }
               
               else if(c == 33) {
               
                  charfreq[4] = (long) charfreq[4] + 1;
               
               }
            
               c = fgetc(f); //re-initializes fgetc for next character in while loop
            
            }
         
         
         
            fclose(f); //close
         
            FILE *g = fopen(filetowrite, "w"); //opens result.txt for writing
         
            fprintf(f, ", -> %ld\n", charfreq[0]); //formatted writing
         
            fprintf(f, ". -> %ld\n", charfreq[1]);
         
            fprintf(f, ": -> %ld\n", charfreq[2]);
         
            fprintf(f, "; -> %ld\n", charfreq[3]);
         
            fprintf(f, "! -> %ld\n", charfreq[4]);
         
            fclose(g);
         
         
         
         }
      
      }
   
   }

   closedir(d); //close directory

  

}

#include <stdio.h>

#include <dirent.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

#include<unistd.h>

#include <stdbool.h>

void displayalphabetfreq(long charfreq[], int size)

{

   for(int i = 0; i < size; i++)
   
   {
   
      printf("%c -> %d\n", (char)(i+97), charfreq[i]);
   
   }

}

int main()

{

  

   char *path = "../data"; // the data *.txt files are under this folder

   char *filetowrite = "result.txt"; // the frequency of all alphabetical letters will be written in this file

  

   long alphabetfreq[ALPHABETSIZE] = {0}; // array to store the frequency of each alphablet letter

  

  

   alphabetlettercount(path, filetowrite, alphabetfreq); // process the data files

  

   displayalphabetfreq(alphabetfreq, ALPHABETSIZE); // print the frequency stored in the array to output screen

}

void displayspecialcharfreq(long charfreq[], int size)

{  

   for(int i = 0; i < size; i++)
   
   {
   
      switch(i)
      
      {
      
         case 0:
         
            printf(", -> %d\n", charfreq[i]);
         
            break;
      
         case 1:
         
            printf(". -> %d\n", charfreq[i]);
         
            break;
      
         case 2:
         
            printf(": -> %d\n", charfreq[i]);
         
            break;
      
         case 3:
         
            printf("; -> %d\n", charfreq[i]);
         
            break;
      
         case 4:
         
            printf("! -> %d\n", charfreq[i]);
         
            break;
      
      }
   
   }

}

int main()

{

   char *path = "../data"; // the path of the directory including the *.txt files to be processed

   char *filetowrite = "specialresult.txt"; // the frequency of all alphabetical letters will be written in this file

  

   long charfreq[SPECIALCHARSIZE] = {0}; // array to store the frequency of 5 special characters

  

   specialcharcount(path, filetowrite, charfreq); // count the frequency of special characters and write into file

  

   displayspecialcharfreq(charfreq, SPECIALCHARSIZE); // print the array to output screen  

}