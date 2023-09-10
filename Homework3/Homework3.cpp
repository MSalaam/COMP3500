// Mohamad Salaam + Jacob Webb
// mzs0171        + jjw0036
// 3500-001
// Date: Mar/28
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
fstream inputFile; //Input file stream object

int group1 = 0;
int group2 = 0;
int group3 = 0;
int group4 = 0;
int group5 = 0;
int group6 = 0;
int group7 = 0;
int group8 = 0;
int group9 = 0;
int group10 = 0;


int main() {


   inputFile.open("IntegerList.txt");      
   if(!inputFile) cout << "there's something wrong with the file!\n";

   int a;
   while (inputFile >> a)
   {
               
      switch (a) {
      
         case 0 ... 9:
            group1++;
            break;
      
         case 10 ... 19:
            group2++;
            break;
      
         case 20 ... 29:
            group3++;
            break;
      
         case 30 ... 39:
            group4++;
            break;
      
         case 40 ... 49:
            group5++;
            break;
      
         case 50 ... 59:
            group6++;
            break;
      
         case 60 ... 69:
            group7++;
            break;
      
         case 70 ... 79:
            group8++;
            break;
      
         case 80 ... 89:
            group9++;
            break;
      
         default:
            group10++;
            break;
      
      }
      printf("%i ", a);
   
      
   }
         
   
   cout << "\nGroup 1 (0..9)     Count:" << group1
        << "\nGroup 2 (10..19)   Count:" << group2
        << "\nGroup 3 (20..29)   Count:" << group3
        << "\nGroup 4 (30..39)   Count:" << group4
        << "\nGroup 5 (40..49)   Count:" << group5
        << "\nGroup 6 (50..59)   Count:" << group6
        << "\nGroup 7 (60..69)   Count:" << group7
        << "\nGroup 8 (70..79)   Count:" << group8
        << "\nGroup 9 (80..89)   Count:" << group9
        << "\nGroup 10 (90..100) Count:"<< group10; 
         
   
   
}