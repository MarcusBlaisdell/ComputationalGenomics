
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct myStruct
{
  int a;
  int b;
  int c;
};

int main (int argc, char * argv[])
{
  int a = 0, b = 0;
  int n = 0, m = 0;
  string theString;

  if (argc > 1)
  {
    n = stoi (argv[1]);
  } // end get n

  if (argc > 2)
  {
    m = stoi (argv[2]);
  } // end get m

  cout << "n: " << n << " - m: " << m << endl;

  struct myStruct **myArray = new struct myStruct * [n];
  //struct myStruct **myArray = (struct ADP_cell **) malloc (sizeof(ADP_cell *) * n);
  //struct myStruct myArray[n];


  for (int a = 0; a < n; a++)
  {
    myArray[a] = new struct myStruct [m];
  }

  cout << "Matrix created successfully" << endl;

  for (a = 0; a < n; a++)
  {
    for (b = 0; b < m; b++)
    {
      myArray[a][b].a = 0;
      myArray[a][b].b = 0;
      myArray[a][b].c = 0;
    }
  }

  cout << "initialized to zero successfully" << endl;

  /*
  for (int a = 0; a < n; a++)
  {
    myArray[a].a = 1;
    myArray[a].b = 2;
    myArray[a].c = 3;

  } // end outer, n
  */

/*
  for (int a = 0; a < n; a++)
  {
    for (int b = 0; b < m; b++)
    {
      myArray[a][b].a = 1;
      myArray[a][b].b = 2;
      myArray[a][b].c = 3;
    } // end inner, m

  } // end outer, n
*/


} // end main
