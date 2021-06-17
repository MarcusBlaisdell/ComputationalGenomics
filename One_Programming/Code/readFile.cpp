#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main (int argc, char *argv[])
{
  string theLine;
  string match, mismatch, g, h;
  int matchVal, mismatchVal, gVal, hVal;
  string theString, theVal;
  int theNumericalVal;
  string inputFile;

  if (argc > 1)
  {
    inputFile = argv[1];
  } // end read specified file
  else
  {
    inputFile = "parameters.config";
  } // end default file

  ifstream inFile (inputFile);

  while (getline (inFile, theLine))
  {
    int i = 0;

    if (theLine.length() == 0)
    {
      break;
    }

    while (theLine[i] != ' ' && theLine[i] != '\t')
    {
      i++;

    } // end split into two strings

    //cout << "i: " << i << endl;

    theString.append(theLine, 0,i);
    theVal.append(theLine, i+1,theLine.length());


    theNumericalVal = stoi (theVal);

    //cout << "theString: " << theString << " - theVal: " << theVal << endl;
    //cout << "theNumericalVal: " << theNumericalVal << " - theNumericalVal + 3: " << theNumericalVal + 3 << endl;

    if (theString == "match")
    {
      matchVal = theNumericalVal;
    }

    if (theString == "mismatch")
    {
      mismatchVal = theNumericalVal;
    }

    if (theString == "g")
    {
      gVal = theNumericalVal;
    }

    if (theString == "h")
    {
      hVal = theNumericalVal;
    }

    theString = "";
    theVal = "";
  } // end while



  cout << "match: " << matchVal << endl;
  cout << "mismatch: " << mismatchVal << endl;
  cout << "g: " << gVal << endl;
  cout << "h: " << hVal << endl;

} // end readFile function 
