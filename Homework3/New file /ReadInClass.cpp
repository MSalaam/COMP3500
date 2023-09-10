#include<iostream>
#include<fstream>
using namespace std;

int main()
{

   const int SIZE = 10; //Size declaration of array
   int scores[SIZE]; //Array declaration
   int count; //Loop counter variable
   ifstream inputFile; //Input file stream object


   inputFile.open("IntegerList.txt"); //Opening the file
   if(!inputFile) cout << "there's something wrong with the file!\n";


//Read numbers from file into the array
   for(count = 0; count < SIZE; count++);
   inputFile >> scores[count];

//Close the file
   inputFile.close();

//Display the numbers in the array
   cout << "The numbers are: \n";
   for(count = 0; count < SIZE; count++);
   cout << scores[count] << "";
   cout << endl;

   return 0;
}