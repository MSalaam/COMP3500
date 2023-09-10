// count.h

// alphabetcount.c

// specialcharcount.c

// testalphabetcount.c

// testspecialcharcount.c

// Source code for count.h:

/* charcount.h - This header file include type definitions (including function prototypes) and macros

used for the programing assignment zero.

*/

#include <stdio.h>

#define ALPHABETSIZE 26 //The total number of alphabetical letter from a - z (case insensitive)

#define SPECIALCHARSIZE 5 // The number of these special characters ',' '.' ';' ':' '!'

void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[]);

/**

The alphabetlettercount function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under

directory of the given path and write the results to a file named as filetowrite.

  

Input:

path - a pointer to a char string [a character array] specifying the path of the directory; and

filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.

alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z:

alphabetfreq[0]: the frequency of 'a'

alphabetfreq[1]: the frequency of 'b'

... ...

alphabetfreq[25]:the frequency of 'z'

  

Output: a new file named as filetowrite with the frequency of each alphabet letter written in

*/

void specialcharcount(char *path, char *filetowrite, long charfreq[]);

/**

The specialcharcount function counts the frequency of the following 5 special characters:

',' '.' ':' ';' '!'

in all the .txt files under directory of the given path and write the results to a file named as filetowrite.

  

Input:

  

path - a pointer to a char string [a character array] specifying the path of the directory; and

filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.

alphabetfreq - a pointer to a long array storing the frequency of the above 5 special characters

  

charfreq[0]: the frequency of ','

charfreq[1]: the frequency of '.'

charfreq[2]: the frequency of ':'

charfreq[3]: the frequency of ';'

charfreq[4]: the frequency of '!'

  

Output: a new file named as filetowrite with the frequency of the above special characters written in

  

Steps recommended to finish the function:

1) Find all the files ending with .txt and store in filelist.

2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array

long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert

it to lower case first.

3) Write the result in the output file: filetowrite in following format:

  

character -> frequency

example:

, -> 20

. -> 11

: -> 20

; -> 11

! -> 12

Assumption:

1) You can assume there is no sub-directory under the given path so you don't have to search the files

recursively.

2) Only .txt files are counted and other types of files should be ignored.

  

*/

// Source code for alphabetcount.c:

/*

* alphabetcount.c - this file implements the alphabetlettercount function.

*/

#include <stdio.h>

#include <dirent.h>

#include <string.h>

#include "count.h"

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

/**

The alphabetlettercount function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under

directory of the given path and write the results to a file named as filetowrite.

  

Input:

path - a pointer to a char string [a character array] specifying the path of the directory; and

filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.

alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z:

alphabetfreq[0]: the frequency of 'a'

alphabetfreq[1]: the frequency of 'b'

... ...

alphabetfreq[25]:the frequency of 'z'

  

Output: a new file named as filetowrite with the frequency of each alphabet letter written in

  

Steps recommended to finish the function:

1) Find all the files ending with .txt and store in filelist.

2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array

long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert

it to lower case first.

3) Write the result in the output file: filetowrite in following format:

  

letter -> frequency

example:

a -> 200

b -> 101

... ...

Assumption:

1) You can assume there is no sub-directory under the given path so you don't have to search the files

recursively.

2) Only .txt files are counted and other types of files should be ignored.

  

*/

// Source code for specialcharcount.c:

/*

* specialcharcount.c - this file implements the specialcharcount function.

*/

#include <stdio.h>

#include <dirent.h>

#include <string.h>

#include "count.h"

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

/**

The specialcharcount function counts the frequency of the following 5 special characters:

',' '.' ':' ';' '!'

in all the .txt files under directory of the given path and write the results to a file named as filetowrite.

  

Input:

  

path - a pointer to a char string [a character array] specifying the path of the directory; and

filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.

alphabetfreq - a pointer to a long array storing the frequency of the above 5 special characters

  

charfreq[0]: the frequency of ','

charfreq[1]: the frequency of '.'

charfreq[2]: the frequency of ':'

charfreq[3]: the frequency of ';'

charfreq[4]: the frequency of '!'

  

Output: a new file named as filetowrite with the frequency of the above special characters written in

  

Steps recommended to finish the function:

1) Find all the files ending with .txt and store in filelist.

2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array

long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert

it to lower case first.

3) Write the result in the output file: filetowrite in following format:

  

character -> frequency

example:

, -> 20

. -> 11

: -> 20

; -> 11

! -> 12

Assumption:

1) You can assume there is no sub-directory under the given path so you don't have to search the files

recursively.

2) Only .txt files are counted and other types of files should be ignored.

  

*/

// Source code for testalphabetcount.c:

/* This program is to test alphabetcount function.

*

*/

#include <stdio.h>

#include <dirent.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

#include<unistd.h>

#include <stdbool.h>

#include "count.h"

/*

* Print the frequencies of alphabetical characters stored in array: charfreq[] to output screen in the format as:

* letter -> frequency (one letter a line)

* Input: charfreq - array having the frequency of each alphabet letter

size - the total number of alphabet letters

* example:

* a -> 20

* b -> 30

*/

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

// Source code for testspecialcharcount.c:

/* This program is to test specialcharcount function.

*

*/

#include <stdio.h>

#include <dirent.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

#include<unistd.h>

#include <stdbool.h>

#include "count.h"

/*

* This function prints the frequency stored in array charfreq[] to output screen.

* Input: charfreq - array having the frequency of special characters

size - the total number of special characters

* example:

* a -> 20

* b -> 30

*/

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

}count.h

alphabetcount.c

specialcharcount.c

testalphabetcount.c

testspecialcharcount.c

// Source code for count.h:

/* charcount.h - This header file include type definitions (including function prototypes) and macros

used for the programing assignment zero.

*/

#include <stdio.h>

#define ALPHABETSIZE 26 //The total number of alphabetical letter from a - z (case insensitive)

#define SPECIALCHARSIZE 5 // The number of these special characters ',' '.' ';' ':' '!'

void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[]);

/**

The alphabetlettercount function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under

directory of the given path and write the results to a file named as filetowrite.

  

Input:

path - a pointer to a char string [a character array] specifying the path of the directory; and

filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.

alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z:

alphabetfreq[0]: the frequency of 'a'

alphabetfreq[1]: the frequency of 'b'

... ...

alphabetfreq[25]:the frequency of 'z'

  

Output: a new file named as filetowrite with the frequency of each alphabet letter written in

*/

void specialcharcount(char *path, char *filetowrite, long charfreq[]);

/**

The specialcharcount function counts the frequency of the following 5 special characters:

',' '.' ':' ';' '!'

in all the .txt files under directory of the given path and write the results to a file named as filetowrite.

  

Input:

  

path - a pointer to a char string [a character array] specifying the path of the directory; and

filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.

alphabetfreq - a pointer to a long array storing the frequency of the above 5 special characters

  

charfreq[0]: the frequency of ','

charfreq[1]: the frequency of '.'

charfreq[2]: the frequency of ':'

charfreq[3]: the frequency of ';'

charfreq[4]: the frequency of '!'

  

Output: a new file named as filetowrite with the frequency of the above special characters written in

  

Steps recommended to finish the function:

1) Find all the files ending with .txt and store in filelist.

2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array

long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert

it to lower case first.

3) Write the result in the output file: filetowrite in following format:

  

character -> frequency

example:

, -> 20

. -> 11

: -> 20

; -> 11

! -> 12

Assumption:

1) You can assume there is no sub-directory under the given path so you don't have to search the files

recursively.

2) Only .txt files are counted and other types of files should be ignored.

  

*/

// Source code for alphabetcount.c:

/*

* alphabetcount.c - this file implements the alphabetlettercount function.

*/

#include <stdio.h>

#include <dirent.h>

#include <string.h>

#include "count.h"

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

/**

The alphabetlettercount function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under

directory of the given path and write the results to a file named as filetowrite.

  

Input:

path - a pointer to a char string [a character array] specifying the path of the directory; and

filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.

alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z:

alphabetfreq[0]: the frequency of 'a'

alphabetfreq[1]: the frequency of 'b'

... ...

alphabetfreq[25]:the frequency of 'z'

  

Output: a new file named as filetowrite with the frequency of each alphabet letter written in

  

Steps recommended to finish the function:

1) Find all the files ending with .txt and store in filelist.

2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array

long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert

it to lower case first.

3) Write the result in the output file: filetowrite in following format:

  

letter -> frequency

example:

a -> 200

b -> 101

... ...

Assumption:

1) You can assume there is no sub-directory under the given path so you don't have to search the files

recursively.

2) Only .txt files are counted and other types of files should be ignored.

  

*/

// Source code for specialcharcount.c:

/*

* specialcharcount.c - this file implements the specialcharcount function.

*/

#include <stdio.h>

#include <dirent.h>

#include <string.h>

#include "count.h"

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

/**

The specialcharcount function counts the frequency of the following 5 special characters:

',' '.' ':' ';' '!'

in all the .txt files under directory of the given path and write the results to a file named as filetowrite.

  

Input:

  

path - a pointer to a char string [a character array] specifying the path of the directory; and

filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.

alphabetfreq - a pointer to a long array storing the frequency of the above 5 special characters

  

charfreq[0]: the frequency of ','

charfreq[1]: the frequency of '.'

charfreq[2]: the frequency of ':'

charfreq[3]: the frequency of ';'

charfreq[4]: the frequency of '!'

  

Output: a new file named as filetowrite with the frequency of the above special characters written in

  

Steps recommended to finish the function:

1) Find all the files ending with .txt and store in filelist.

2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array

long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert

it to lower case first.

3) Write the result in the output file: filetowrite in following format:

  

character -> frequency

example:

, -> 20

. -> 11

: -> 20

; -> 11

! -> 12

Assumption:

1) You can assume there is no sub-directory under the given path so you don't have to search the files

recursively.

2) Only .txt files are counted and other types of files should be ignored.

  

*/

// Source code for testalphabetcount.c:

/* This program is to test alphabetcount function.

*

*/

#include <stdio.h>

#include <dirent.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

#include<unistd.h>

#include <stdbool.h>

#include "count.h"

/*

* Print the frequencies of alphabetical characters stored in array: charfreq[] to output screen in the format as:

* letter -> frequency (one letter a line)

* Input: charfreq - array having the frequency of each alphabet letter

size - the total number of alphabet letters

* example:

* a -> 20

* b -> 30

*/

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

Source code for testspecialcharcount.c:

/* This program is to test specialcharcount function.

*

*/

#include <stdio.h>

#include <dirent.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

#include<unistd.h>

#include <stdbool.h>

#include "count.h"

/*

* This function prints the frequency stored in array charfreq[] to output screen.

* Input: charfreq - array having the frequency of special characters

size - the total number of special characters

* example:

* a -> 20

* b -> 30

*/

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