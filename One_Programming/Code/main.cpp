/*
* Marcus Blaisdell
* Cpt_S 471
* Programming Assignment #1
* February 12, 2019
* Professor Kalyanaraman
*/

#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct DP_cell
{
  int score;
};

struct ADP_cell
{
  int sub_score;
  int del_score;
  int ins_score;
};

  // cleanString function:
  // removes trailing whitespace from a string

string cleanString (string line)
{

  while (line.back() == ' ')
  {
    line.pop_back ();
  } // end remove any trailing spaces

  return line;

} // end cleanString function

  // reverseString

string reverseString (string theString)
{
  char holdChar;
  int i = 0;
  int j = theString.length () - 1;

  while (i < j)
  {
    holdChar = theString[i];
    theString[i] = theString[j];
    theString[j] = holdChar;

    i++;
    j--;

  } // end swap chars

  return theString;

} // end reverseString function

// reverseString

vector <char> reverseVector (vector <char> theVector)
{
char holdChar;
int i = 0;
int j = theVector.size () - 1;

while (i < j)
{
  holdChar = theVector[i];
  theVector[i] = theVector[j];
  theVector[j] = holdChar;

  i++;
  j--;

} // end swap chars

return theVector;

} // end reverseVector function

  // S function: (calculate a match score for S1 and S2)

int S (char S1, char S2, int match, int mismatch)
{
  //int match = 1;
  //int mismatch = -2;

  if (S1 == S2)
  {
    return match;
  } // end if match, return value assigned to "match"
  else
  {
    return mismatch;
  } // end else, return the mismatch value

} // end S function

  // runGlobal function - runs the global alignment test

/////
int runGlobal (string S1, string S2, int match, int mismatch, int g, int h,
                int *matchCount, int *mismatchCount, int *gapCount, int *openingGap)
{
  // We need a matrix:

  int i = 0, j = 0, maxI = 0, maxJ = 0;
  int m = 0, n = 0;
  int a = 0, b = 0;
  int max = 0, subs = 0, del = 0, ins = 0;
  int maxInd = 0, lastPos, localMax = 0;
  int globalScore;

  vector <char> theS1;
  vector <char> theS2;
  vector <char> theLink;

    // m and n need to be the size of the strings + 1
    // since the zeroeth row and column are used to
    // hold the initial scores:

  n = S1.size() + 1;
  m = S2.size() + 1;
  cout << "n: " << n << endl;
  cout << "m: " << m << endl;

    // create a table of DP_cell's, n x m size
    // Key:
    // y = n = i = a = row
    // x = m = j = b = column

  // myT = (struct ADP_cell **) malloc (sizeof(ADP_cell *)*n));
  //struct ADP_cell myTable[n][m];
  //struct myStruct **myArray = (struct ADP_cell **) malloc (sizeof(ADP_cell *) * n);
  //struct myStruct myArray[n];

  //struct ADP_cell **myTable = new struct ADP_cell * [m];
  struct ADP_cell **myTable = (struct ADP_cell **) malloc (sizeof(ADP_cell *) * n);

  for (int z = 0; z < n; z++)
  {
    myTable[z] = new struct ADP_cell [m];
    //myTable[z] = (struct ADP_cell **) malloc (sizeof(ADP_cell *) [m]);
  } // end fill up the rows
cout << "Matrix created successfully" << endl;
  //struct ADP_cell **myTable = new struct ADP_cell * [n];
  /*
  for (a = 0; a < m; a++)
  {
    myTable[a] = new struct ADP_cell [m];
  } // end initialize matrix
  */

    // initialize scores in the table:
    // T(0,0): S(0,0) = 0, D(0,0) = 0, I(0,0) = 0
    // for (i=1 to m):
    //  T(i, 0): S(i,0) = -infinity, D(i,0) = h + i * g, I(i,0) = -infinity
    // for (j = 1 to n):
    //  T(0,j): S(0,j) = -infinity, D(0,j) = -infinity, I(0,j) = h + j * g

    // initialize everything to zero:

  for (a = 0; a < n; a++)
  {
    for (b = 0; b < m; b++)
    {
      myTable[a][b].sub_score = 0;
      myTable[a][b].del_score = 0;
      myTable[a][b].ins_score = 0;
    } // end inner loop (columns)
  } // end outer loop (rows)
cout << "All scores initialized to zero successfully" << endl;

    // initialize the zeroeth row and column
    // I can't initialize to negative infinity so,
    // I'm using max negative integer value -32,767 instead

  for (i = 1; i < n; i++)
  {
    myTable[i][0].sub_score = -32767;
    myTable[i][0].del_score = (h + (i * g) );
    myTable[i][0].ins_score = -32767;

  } // end initialize column i to zero

  for (j = 1; j < m; j++)
  {
    myTable[0][j].sub_score = -32767;
    myTable[0][j].del_score = -32767;
    myTable[0][j].ins_score = (h + (j * g) );

  } // end initialize row j to j * g
cout << "Row / Column initialization successful" << endl;
    // calculate all scores:
    // Since row 0 and column 0 contain initializing scores,
    // we need to begin at row 1 and column 1:

    // For local algorithm, we need to know the position of the highest score
    // so, track scores as they are calculated, tracking the position of the
    // highest score and use that to begin the backtrace

  i = 1;
  j = 1;

  for (i = 1; i < n; i++)
  {
    for (j = 1; j < m; j++)
    {
        // calculate scores:

        // substition:

      subs = ((myTable[i-1][j-1].sub_score));
      //cout << "i: " << i << " ,j:" << j << " :S1[i-1]: " << S1[i-1] << " :S2[j-1]: " << S2[j-1] << endl;
      max = subs;

        // calculate deletion score:

      del = ((myTable[i-1][j-1].del_score));

        // if del is greater than max, make it new max

      if (del > max)
      {
        max = del;

      } // end if del is greater than max, make it new max

        // calculate insertion score:

      ins = ((myTable[i-1][j-1].ins_score));

      // if ins is greater than max, make it new max

      if (ins > max)
      {
        max = ins;

      } // end if ins is greater than max, make it new max

      myTable[i][j].sub_score = max + ( S(S1[i-1], S2[j-1], match, mismatch) );

      // Deletion

      subs = myTable[i-1][j].sub_score + h + g;

      max = subs;

      del = myTable[i-1][j].del_score + g;

      if (del > max)
      {
        max = del;
      }

      ins = myTable[i-1][j].ins_score + h + g;

      if (ins > max)
      {
        max = ins;
      }

      myTable[i][j].del_score = max;

      // Insertion

      subs = myTable[i][j-1].sub_score + h + g;

      max = subs;

      del = myTable[i][j-1].del_score + h + g;

      if (del > max)
      {
        max = del;
      }

      ins = myTable[i][j-1].ins_score + g;

      if (ins > max)
      {
        max = ins;
      }

      myTable[i][j].ins_score = max;

    } // end inner loop

  } // end outer loop

  // end calculate scores

cout << "Scores successfully calculated" << endl;
    // backtrace:
    // use three vectors to hold characters:
    // theS1 will hold the characters for S1,
    // theS2 will hold the characters for S2,
    // theLink will hold the "|" character or " "
    // to indicate yes or no for match between them

    // print the size of the table:

  cout << "matrix size: " << sizeof(myTable) << endl;

    // For Global search, start at the last position in the table:

  i = n - 1;
  j = m - 1;

    // print out the max score, find the highest
    // score in the last cell:

    subs = myTable[i][j].sub_score;
    max = subs;

    del = myTable[i][j].del_score;
    if (del > max)
    {
      max = del;
    }

    ins = myTable[i][j].ins_score;
    if (ins > max)
    {
      max = ins;
    }

    //cout << "Global Score: " << max << endl;
    globalScore = max;

    // now run backtrace until max == 0

  //cout << "backtrace: " << endl;

  while ( max != 0 )
  //while ( (i > -1) && (j > -1) )
  {
      // check substitution:

    subs = myTable[i-1][j-1].sub_score;
    localMax = subs;
    del = myTable[i-1][j-1].del_score;
    if (del > localMax)
    {
      localMax = del;
    }
    ins = myTable[i-1][j-1].ins_score;
    if (ins > localMax)
    {
      localMax = ins;
    }
    //cout << "subs: " << subs;
    max = localMax;
    // the maxInd is a key to let me know which path has the highest score
    // 0 = diagonal or substitution,
    // 1 = up or deletion
    // 2 = left or insertion
    maxInd = 0;

    // check deletion:

    subs = myTable[i-1][j].sub_score;
    localMax = subs;
    del = myTable[i-1][j].del_score;
    if (del > localMax)
    {
      localMax = del;
    }
    ins = myTable[i-1][j].ins_score;
    if (ins > localMax)
    {
      localMax = ins;
    }
    //cout << "subs: " << subs;
    max = localMax;

    //cout << "   - del: " << del;
    if (localMax > max)
    {
      max = localMax;
      maxInd = 1;

    } // end if del > max, update max

    // check insertion:

    subs = myTable[i][j-1].sub_score;
    localMax = subs;
    del = myTable[i][j-1].del_score;
    if (del > localMax)
    {
      localMax = del;
    }
    ins = myTable[i][j-1].ins_score;
    if (ins > localMax)
    {
      localMax = ins;
    }
    //cout << "subs: " << subs;

    //cout << "   - ins: " << ins << endl;
    if (localMax > max)
    {
      max = localMax;
      maxInd = 2;

    } // end if del > max, update max

    // update the vectors appropriately:
    //

    if (maxInd == 0)
    {
      theS1.push_back(S1[i-1]);
      theS2.push_back(S2[j-1]);
      if (S1[i-1] == S2[j-1])
      {
        theLink.push_back ('|');
        *matchCount = *matchCount + 1;
      } // end if match
      else
      {
        theLink.push_back (' ');
        *mismatchCount = *mismatchCount + 1;
      } // end else, no match

        // since this is a substitution,
        // if our last move was a gap, this is
        // an opening gap:

      if ((lastPos == 1) || (lastPos == 2) )
      {
        *openingGap = *openingGap + 1;
      } // end if our last move was a gap

      i--;
      j--;

    } // end if substitution

    if (maxInd == 1)
    {
      theS1.push_back(S1[i-1]);
      theS2.push_back('-');

      theLink.push_back (' ');
      *gapCount = *gapCount + 1;

      i--;

    } // end if deletion

    if (maxInd == 2)
    {
      theS1.push_back('-');
      theS2.push_back(S2[j-1]);

      theLink.push_back (' ');

      j--;

    } // end if insertion

    lastPos = maxInd;

  } // end while loop to backtrace

    // reverse the strings:

  theS1 = reverseVector (theS1);
  theLink = reverseVector (theLink);
  theS2 = reverseVector (theS2);
  //cout << "theS1: " << theS1.size () << " - theLink: " << theLink.size() << " - theS2: " << theS2.size() << endl;

/////

    // Print out results:

  int total = theLink.size ();
  int S1Index = 0, S2Index = 0, linkIndex = 0;
  int charCount = 0;
  int rowSize = 60, rowStart = 0;

  while (linkIndex < total)
  {
    if ((total - linkIndex) < 60)
    {
      rowSize = total - linkIndex;
    }

    ////////////////////////////////////////////
      // S1
    cout << "S1 " << setw(5) << S1Index << " ";
    for (rowStart = 0; rowStart < rowSize; rowStart++)
    {
      if (theS1[linkIndex + rowStart] != '-')
      {
        S1Index++;
      } // end increment S1Index

      cout << theS1[linkIndex + rowStart];
    } // end for loop to print 60 (or fewer) characters from theS1

    cout << setw(5) << S1Index << endl;
    S1Index++;
    ////////////////////////////////////////////
    cout << setw(10);
    for (rowStart = 0; rowStart < rowSize; rowStart++)
    {
      cout << theLink[linkIndex + rowStart];

    } // end for loop to print 60 (or fewer) characters from theS1

    cout << endl;
    ////////////////////////////////////////////
    cout << "S2 " << setw(5) << S2Index << " ";
    for (rowStart = 0; rowStart < rowSize; rowStart++)
    {
      if (theS2[linkIndex + rowStart] != '-')
      {
        S2Index++;
      } // end increment S2Index

      cout << theS2[linkIndex + rowStart];

    } // end for loop to print 60 (or fewer) characters from theS1

    cout << setw(5) << S2Index << endl << endl;
    S2Index++;
    ////////////////////////////////////////////

    linkIndex += rowSize;

  } // end while to print all characters
/////

  /*
    // Print out results:

  a = 0;

  while (theS1[a])
  {
    cout << theS1[a];
    a++;

  } // end print out theS1

  cout << endl;

  a = 0;

  while (theLink[a])
  {
    cout << theLink[a];
    a++;

  } // end print out theLink

  cout << endl;

  a = 0;
cout << theS2[a];
a++;
  while (theS2[a])
  {
    cout << theS2[a];
    a++;

  } // end print out theS2

  cout << endl;
  */

  /*
    // print the matrix

  for (int a = 0; a < n; a++)
  {
    for (int b = 0; b < m; b++)
    {
      cout << myTable[a][b].score << ",";
    }
    cout << endl;

  } // end for loop to print the matrix
  */

  return globalScore;

} // end function runGlobal
/////


  // runLocal function - runs the local alignment test

int runLocal (string S1, string S2, int match, int mismatch, int g, int h,
                int *matchCount, int *mismatchCount, int *gapCount, int *openingGap)
{
  // We need a matrix:

  int i = 0, j = 0, maxI = 0, maxJ = 0, highScore = 0;
  int m = 0, n = 0;
  int a = 0, b = 0;
  int max = 0, subs = 0, del = 0, ins = 0;
  int maxInd = 0, lastPos, localMax = 0;

  vector <char> theS1;
  vector <char> theS2;
  vector <char> theLink;

    // m and n need to be the size of the strings + 1
    // since the zeroeth row and column are used to
    // hold the initial scores:

  n = S1.size() + 1;
  m = S2.size() + 1;
  cout << "n: " << n << endl;
  cout << "m: " << m << endl;

    // create a table of DP_cell's, n x m size
    // Key:
    // y = n = i = a = row
    // x = m = j = b = column

  //struct ADP_cell myTable[n][m];
  struct ADP_cell **myTable = new struct ADP_cell * [n];

  for (int z = 0; z < n; z++)
  {
    myTable[z] = new struct ADP_cell [m];
  } // end fill up the rows

    // initialize scores in the table:
    // T(0,0): S(0,0) = 0, D(0,0) = 0, I(0,0) = 0
    // for (i=1 to m):
    //  T(i, 0): S(i,0) = -infinity, D(i,0) = h + i * g, I(i,0) = -infinity
    // for (j = 1 to n):
    //  T(0,j): S(0,j) = -infinity, D(0,j) = -infinity, I(0,j) = h + j * g

    // initialize everything to zero:

  for (a = 0; a < n; a++)
  {
    for (b = 0; b < m; b++)
    {
      myTable[a][b].sub_score = 0;
      myTable[a][b].del_score = 0;
      myTable[a][b].ins_score = 0;
    } // end inner loop (columns)
  } // end outer loop (rows)

    // initialize the zeroeth row and column
    // I can't initialize to negative infinity so,
    // I'm using max negative integer value -32,767 instead

  for (i = 1; i < n; i++)
  {
    /*
    myTable[i][0].sub_score = -32767;
    myTable[i][0].del_score = (h + (i * g) );
    myTable[i][0].ins_score = -32767;
    */
    myTable[i][0].sub_score = 0;
    myTable[i][0].del_score = 0;
    myTable[i][0].ins_score = 0;

  } // end initialize column i to zero

  for (j = 1; j < m; j++)
  {
    /*
    myTable[0][j].sub_score = -32767;
    myTable[0][j].del_score = -32767;
    myTable[0][j].ins_score = (h + (i * g) );
    */
    myTable[0][j].sub_score = 0;
    myTable[0][j].del_score = 0;
    myTable[0][j].ins_score = 0;
  } // end initialize row j to j * g


    // calculate all scores:
    // Since row 0 and column 0 contain initializing scores,
    // we need to begin at row 1 and column 1:

    // For local algorithm, we need to know the position of the highest score
    // so, track scores as they are calculated, tracking the position of the
    // highest score and use that to begin the backtrace

  i = 1;
  j = 1;

  for (i = 1; i < n; i++)
  {
    for (j = 1; j < m; j++)
    {
        // calculate scores:

        // substition:

      subs = ((myTable[i-1][j-1].sub_score));
      //cout << "i: " << i << " ,j:" << j << " :S1[i-1]: " << S1[i-1] << " :S2[j-1]: " << S2[j-1] << endl;
      max = subs;

        // calculate deletion score:

      del = ((myTable[i-1][j-1].del_score));

        // if del is greater than max, make it new max

      if (del > max)
      {
        max = del;

      } // end if del is greater than max, make it new max

        // calculate insertion score:

      ins = ((myTable[i-1][j-1].ins_score));


      // if ins is greater than max, make it new max

      if (ins > max)
      {
        max = ins;

      } // end if ins is greater than max, make it new max

      //myTable[i][j].sub_score = max + ( S(S1[i-1], S2[j-1], match, mismatch) );

      max += ( S(S1[i-1], S2[j-1], match, mismatch) );

      if (max < 0)
      {
        max = 0;
      } // end no negative scores

      myTable[i][j].sub_score = max;


      // Deletion

      subs = myTable[i-1][j].sub_score + h + g;

      max = subs;

      del = myTable[i-1][j].del_score + g;

      if (del > max)
      {
        max = del;
      }

      ins = myTable[i-1][j].ins_score + h + g;

      if (ins > max)
      {
        max = ins;
      }

      if (max < 0)
      {
        max = 0;
      } // end no negative scores

      myTable[i][j].del_score = max;

      // Insertion

      subs = myTable[i][j-1].sub_score + h + g;

      max = subs;

      del = myTable[i][j-1].del_score + h + g;

      if (del > max)
      {
        max = del;
      }

      ins = myTable[i][j-1].ins_score + g;

      if (ins > max)
      {
        max = ins;
      }

      if (max < 0)
      {
        max = 0;
      } // end no negative scores

      myTable[i][j].ins_score = max;

      if (max > highScore)
      {
        highScore = max;
        maxI = i;
        maxJ = j;
        //cout << max << " : " << maxI << ", " << maxJ << endl;
      } // end if we have found a higher score, record its position

    } // end inner loop

  } // end outer loop

  // end calculate scores


  //cout << "highScore: " << highScore << endl;
  //cout << maxI << ", " << maxJ << endl;


    // backtrace:
    // use three vectors to hold characters:
    // theS1 will hold the characters for S1,
    // theS2 will hold the characters for S2,
    // theLink will hold the "|" character or " "
    // to indicate yes or no for match between them


    // For local search, start at the position of the highest score:

  i = maxI;
  j = maxJ;

  // If there is an offset, fill the empty spaces:

  if (maxI > maxJ)
  {
    int offset = maxI - maxJ;
    int theI = n - 2, theJ = m - 2;

    for (int o = 0; o < offset; o++)
    {
      theS1.push_back ('-');
      theS2.push_back (S2[theJ]);
      theJ--;
    } // end do fill of I

  } // end if maxI > maxJ

  if (maxJ > maxI)
  {
    int offset = maxJ - maxI;
    int theI = n - 2, theJ = m - 2;

    for (int o = 0; o < offset; o++)
    {
      theS1.push_back (S1[theI]);
      theS2.push_back ('-');
      theI--;
    } // end do fill of J

  } // end if maxI < maxJ

    // now run normal backtrace until either i, or j == 0

  //cout << "backtrace: " << endl;

  while ( max != 0 )
  //while ( (i > -1) && (j > -1) )
  {
      // check substitution:

    subs = myTable[i-1][j-1].sub_score;
    localMax = subs;
    del = myTable[i-1][j-1].del_score;
    if (del > localMax)
    {
      localMax = del;
    }
    ins = myTable[i-1][j-1].ins_score;
    if (ins > localMax)
    {
      localMax = ins;
    }
    //cout << "subs: " << subs;
    max = localMax;
    // the maxInd is a key to let me know which path has the highest score
    // 0 = diagonal or substitution,
    // 1 = up or deletion
    // 2 = left or insertion
    maxInd = 0;

    // check deletion:

    subs = myTable[i-1][j].sub_score;
    localMax = subs;
    del = myTable[i-1][j].del_score;
    if (del > localMax)
    {
      localMax = del;
    }
    ins = myTable[i-1][j].ins_score;
    if (ins > localMax)
    {
      localMax = ins;
    }
    //cout << "subs: " << subs;
    //max = localMax;

    //cout << "   - del: " << del;
    if (localMax > max)
    {
      max = localMax;
      maxInd = 1;

    } // end if del > max, update max

    // check insertion:

    subs = myTable[i][j-1].sub_score;
    localMax = subs;
    del = myTable[i][j-1].del_score;
    if (del > localMax)
    {
      localMax = del;
    }
    ins = myTable[i][j-1].ins_score;
    if (ins > localMax)
    {
      localMax = ins;
    }
    //cout << "subs: " << subs;

    //cout << "   - ins: " << ins << endl;
    if (localMax > max)
    {
      max = localMax;
      maxInd = 2;

    } // end if del > max, update max

    // update the vectors appropriately:
    //

    if (maxInd == 0)
    {
      theS1.push_back(S1[i-1]);
      theS2.push_back(S2[j-1]);
      if (S1[i-1] == S2[j-1])
      {
        theLink.push_back ('|');
        *matchCount = *matchCount + 1;
      } // end if match
      else
      {
        theLink.push_back (' ');
        *mismatchCount = *mismatchCount + 1;
      } // end else, no match

        // since this is a substitution,
        // if our last move was a gap, this is
        // an opening gap:

      if ((lastPos == 1) || (lastPos == 2) )
      {
        *openingGap = *openingGap + 1;
      } // end if our last move was a gap

      i--;
      j--;

    } // end if substitution

    if (maxInd == 1)
    {
      theS1.push_back(S1[i-1]);
      theS2.push_back('-');

      theLink.push_back (' ');
      *gapCount = *gapCount + 1;

      i--;

    } // end if deletion

    if (maxInd == 2)
    {
      theS1.push_back('-');
      theS2.push_back(S2[j-1]);

      theLink.push_back (' ');

      j--;

    } // end if insertion

    lastPos = maxInd;

  } // end while loop to backtrace

    // fill in remainder:
  if (i == 0)
  {
    while (j > -1)
    {
      theS1.push_back ('-');
      theS2.push_back (S2[j]);
      j--;
    } // end fill in remaining S1's with -

  } // end if S1 reached zero first

  if (j == 0)
  {
    while (i > -1)
    {
      theS1.push_back (S1[i]);
      theS2.push_back ('-');
      j--;
    } // end fill in remaining S2's with -

  } // end if S2 reached zero first

    // reverse the strings:

  theS1 = reverseVector (theS1);
  theLink = reverseVector (theLink);
  theS2 = reverseVector (theS2);

  //cout << "theS1: " << theS1.size () << " - theLink: " << theLink.size() << " - theS2: " << theS2.size() << endl;

/////

    // Print out results:

  int total = theLink.size ();
  int S1Index = 0, S2Index = 0, linkIndex = 0;
  int charCount = 0;
  int rowSize = 60, rowStart = 0;

  while (linkIndex < total)
  {
    if ((total - linkIndex) < 60)
    {
      rowSize = total - linkIndex;
    }

    ////////////////////////////////////////////
      // S1
    cout << "S1 " << setw(5) << S1Index << " ";
    for (rowStart = 0; rowStart < rowSize; rowStart++)
    {
      if (theS1[linkIndex + rowStart] != '-')
      {
        S1Index++;
      } // end increment S1Index

      cout << theS1[linkIndex + rowStart];
    } // end for loop to print 60 (or fewer) characters from theS1

    cout << setw(5) << S1Index << endl;
    S1Index++;
    ////////////////////////////////////////////
    cout << setw(10);
    for (rowStart = 0; rowStart < rowSize; rowStart++)
    {
      cout << theLink[linkIndex + rowStart];

    } // end for loop to print 60 (or fewer) characters from theS1

    cout << endl;
    ////////////////////////////////////////////
    cout << "S2 " << setw(5) << S2Index << " ";
    for (rowStart = 0; rowStart < rowSize; rowStart++)
    {
      if (theS2[linkIndex + rowStart] != '-')
      {
        S2Index++;
      } // end increment S2Index

      cout << theS2[linkIndex + rowStart];

    } // end for loop to print 60 (or fewer) characters from theS1

    cout << setw(5) << S2Index << endl << endl;
    S2Index++;
    ////////////////////////////////////////////

    linkIndex += rowSize;

  } // end while to print all characters
/////

  /*
    // Print out results:

  a = 0;

  while (theS1[a])
  {
    cout << theS1[a];
    a++;

  } // end print out theS1

  cout << endl;

  a = 0;

  while (theLink[a])
  {
    cout << theLink[a];
    a++;

  } // end print out theLink

  cout << endl;

  a = 0;
cout << theS2[a];
a++;
  while (theS2[a])
  {
    cout << theS2[a];
    a++;

  } // end print out theS2

  cout << endl;
  */

  /*
    // print the matrix

  for (int a = 0; a < n; a++)
  {
    for (int b = 0; b < m; b++)
    {
      cout << myTable[a][b].score << ",";
    }
    cout << endl;

  } // end for loop to print the matrix
  */

  return highScore;

} // end function runLocal

void readFile (string inputFile, int *matchVal,
                int *mismatchVal, int *gVal, int *hVal)
{
  string theLine;
  string match, mismatch, g, h;
  string theString, theVal;
  int theNumericalVal;


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
      *matchVal = theNumericalVal;
    }

    if (theString == "mismatch")
    {
      *mismatchVal = theNumericalVal;
    }

    if (theString == "g")
    {
      *gVal = theNumericalVal;
    }

    if (theString == "h")
    {
      *hVal = theNumericalVal;
    }

    theString = "";
    theVal = "";

  } // end while

} // end readFile function
/////

int main (int argc, char * argv [])
{
  int match = 0;
  int mismatch = 0;
  int h = 0;
  int g = 0;
  int matchCount = 0, mismatchCount = 0, gapCount = 0, openingGap = 0;
  int globalScore, localScore;
  string whichAlg;
  //string dataFile = "../Data/";
  //dataFile.append(argv[1]);
  string dataFile = argv[1];

  ifstream inFileOne (dataFile);
  if (!inFileOne)
  {
    cout << "Unable to open file - exiting !!!" << endl;
    return 0;
  }

  ifstream inFileTwo (dataFile);
  if (!inFileTwo)
  {
    cout << "Unable to open file - exiting !!!" << endl;
    return 0;
  }

  whichAlg = argv[2];
  cout << "use: " << whichAlg << endl;

  string lineOne, lineTwo;
  string seqNameOne, seqNameTwo;
  string S1, S2, readS1, readS2;

  string inputFile;

  if (argc > 3)
  {
    inputFile = argv[3];
  } // end read specified file
  else
  {
    inputFile = "parameters.config";
  } // end default file

  readFile (inputFile, &match, &mismatch, &g, &h);

  cout << endl << "\t *** Parameter configuration values ***" << endl << endl;
  cout << "\tmatch:    " << match << endl;
  cout << "\tmismatch: " << mismatch << endl;
  cout << "\tg:        " << g << endl;
  cout << "\th:        " << h << endl;
  cout << endl;

    // read the data file(s):

  getline (inFileOne, lineOne);

    // if the line begins with '>', it is a label line,
    // all characters up to the first space ' ', are
    // part of the label

  if (lineOne[0] == '>')
  {
    int i = 1;

    while (lineOne[i] && lineOne[i] != ' ')
    {
      i++;
    } // end while loop

    seqNameOne.append (lineOne, 1,i - 1);

  } // end if header, get sequence name

    // The second set of data appears after the first one,
    // read the first line, then skip over it and read the
    // second line, then, read until we find another '>'
    // for the second label line and capture it's label:

  getline (inFileTwo, lineTwo);
  int flag = 0;
  while (flag == 0)
  {
    getline (inFileTwo, lineTwo);
    if (lineTwo[0] == '>')
    {
      flag = 1;
    } // end set flag when second label line found

  } // end find second label line

  int i = 1;

  while (lineTwo[i] && lineTwo[i] != ' ')
  {
    i++;
  }
  seqNameTwo.append (lineTwo, 1,i - 1);

    // read line by line from each file
    // and send each line to runGlobal

  getline (inFileOne, lineOne);

  while (lineOne[0] != '>')
  {
    S1.append (cleanString (lineOne) );
    getline (inFileOne, lineOne);
  } // end read all of first data section

  while (getline (inFileTwo, lineTwo) )
  {
    S2.append (cleanString (lineTwo) );
  } // end while loop to get second data section

  /*
  while (getline (inFileOne, lineOne) && getline (inFileTwo, lineTwo) )
  {

    S1.append (cleanString (lineOne) );
    S2.append (cleanString (lineTwo) );

  } // end while loop to get file text input
  */

  cout << "Sequence 1 = \"" << seqNameOne << "\", length = " << S1.length () << " characters" << endl;
  cout << "Sequence 2 = \"" << seqNameTwo << "\", length = " << S2.length () << " characters" << endl;

  if (strcmp (argv[2], "0") == 0 )
  {
    cout << endl << "Running Global . . . " << endl << endl;
    globalScore = runGlobal (S1, S2, match, mismatch, g, h,
                              &matchCount, &mismatchCount,
                              &gapCount, &openingGap);
    cout << endl << "Global optimal score = " << globalScore << endl << endl;
  } // end if 0, runGlobal
  else if (strcmp (argv[2], "1") == 0)
  {
    cout << endl << "Running Local . . . " << endl << endl;
    localScore = runLocal (S1, S2, match, mismatch, g, h,
              &matchCount, &mismatchCount, &gapCount, &openingGap);
    cout << endl << "Local optimal score = " << localScore << endl << endl;
  } // end else if 1, runLocal
  else
  {
    cout << endl << "Paramater not recognized" << endl;
    cout << "Running default Global function:" << endl << endl;
    globalScore = runGlobal (S1, S2, match, mismatch, g, h,
                              &matchCount, &mismatchCount,
                              &gapCount, &openingGap);
  } // end catch-all

  inFileOne.close ();
  inFileTwo.close ();

  cout << "Report:";

  //cout << endl << "Global optimal score = " << globalScore << endl << endl;

  //cout << "sequence 1: " << seqNameOne << endl;
  //cout << "sequence 2: " << seqNameTwo << endl;

  cout << "matches: " << matchCount << endl;
  cout << "mismatches: " << mismatchCount << endl;
  cout << "gaps: " << gapCount << endl;
  cout << "openingGaps: " << openingGap << endl;

  cout << "Identities = " << matchCount << "/" << S1.length();
  cout << "(" << ( (100) * (float (matchCount) / S1.length() ) ) << "%), Gaps = ";
  cout << gapCount << "/" << S1.length() << "(";
  cout << ( (100) * (float (gapCount) / S1.length() ) ) << "%)" << endl << endl;

} // end main function
