/*
* Marcus Blaisdell
* Cpt_S 471
* Programming Assignment #1
* February 12, 2019
* Professor Kalyanaraman
*
* alignParams.h
*
* This class handles loading the alignment parameters from file
*
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class alignParams
{
  public:
  int match;
  int mismatch;
  int h;
  int g;

  // accessors

  int getMatch ()
  {
    return match;
  } // end getMatch accessor

  int getMismatch ()
  {
    return mismatch;
  } // end getMismatch accessor

  int getH ()
  {
    return h;
  } // end getH accessor

  int getG ()
  {
    return g;
  } // end getG accessor

  // mutators

  void setMatch (int theMatch)
  {
    cout << "setting match to " << theMatch << endl;
    match = theMatch;
  } // end setMatch mutator

  void setMismatch (int theMismatch)
  {
    mismatch = theMismatch;
  } // end setMismatch mutator

  void setH (int theH)
  {
    h = theH;
  } // end setH mutator

  void setG (int theG)
  {
    g = theG;
  } // end setG mutator

  void readLines (string theFile)
  {
    ifstream inFile (theFile, ios::in);

    if (!inFile)
    {
      cout << "Unable to open file\n";
    } // end if open file fails
    else
    {
      string theLine;

      while (getline (inFile, theLine) )
      {
        //cout << theLine << endl;

          // set the parameters we read from the file:

        string word, theWord;
        int theVal;
        int i = 0, j = 0;

        while (theLine[i])
        {
          if (theLine[i] == '\t' || theLine[i] == ' ')
          {
            theWord = word;
            word = "";

          } // end if we found our delimiter
          else
          {
            word.append(theLine, i,i+1);
            cout << "word so far: " << word << endl;
          } // end else, append character to word

          i++;
          j++;

        } // end while loop

        cout << "about to convert " << word << endl;
        if (word.length () > 0)
        {
          theVal = stoi (word);
        }
        else
        {
          theVal = 0;
        }

        cout << "theWord: " << theWord << endl;
        cout << "theVal = " << theVal << endl;

        if (theWord == "match")
        {
          setMatch (theVal);
        }

        if (theWord == "mismatch")
        {
          setMismatch (theVal);
        }

        if (theWord == "h")
        {
          setH (theVal);
        }

        if (theWord == "g")
        {
          setG (theVal);
        }

      } // end loop through each line in the file

    } // end else, read each line from the file

  } // end readLines function

} ;
