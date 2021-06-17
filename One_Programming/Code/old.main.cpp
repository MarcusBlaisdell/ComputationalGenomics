/*
* Marcus Blaisdell
* Cpt_S 471
* Programming Assignment #1
* February 12, 2019
* Professor Kalyanaraman
*/

#include <string.h>
#include <fstream>

using namespace std;

int main (int argc, char * argv [])
{
  int match = 1;
  int mismatch = -2;
  int h = -5;
  int g = -1;

  ifstream inFile ("../Data/test.txt");

  string line;

  if (!inFile)
  {
    cout << "Unable to open file" << endl;
  } // end if file fails to open, warn user
  else
  {
    while (getline (inFile, line) )
    {
      cout << "line:" << endl;
      cout << line << endl;
    } // end while there are lines to read

    inFile.close ();

  } // end else, read from file

} // end main function
