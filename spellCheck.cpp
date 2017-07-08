/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
using namespace std;

/****************************************
* S HASH
* A hash of Strings. The formula for the hash function is to 
****************************************/
class SHash : public Hash <string>
{
public:
   SHash(int numBuckets)    throw (const char *) : Hash <string>(numBuckets) {}
   SHash(const SHash & rhs) throw (const char *) : Hash <string>(rhs) {}

   // add the ascii values of all letters and mod by capacity, adding ascii value of first letter
   int hash(const string & value) const
   {
      int total = 0;
      const char * firstLetter = value.c_str();
      int firstValue = *firstLetter;
      for (const char * p = value.c_str(); *p; p++)
      {
         total += *p;
      }
      return (total % capacity()) + firstValue - 65;
   }

};

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   ifstream fin(/*"/home/cs235e/week12/*/"dictionary.txt");
   SHash s(1000);
   string temp;
   while (fin >> temp)
   {
      s.insert(temp);
   }
   

}
