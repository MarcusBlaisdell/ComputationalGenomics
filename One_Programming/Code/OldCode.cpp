void runGlobal (string S1, string S2, int match, int mismatch, int g, int h,
                int *matchCount, int *mismatchCount, int *gapCount, int *openingGap)
{
  // We need a matrix:

  int i = 0, j = 0;
  int m = 0, n = 0;
  int a = 0, b = 0;
  int max = 0, subs = 0, del = 0, ins = 0;
  int maxInd = 0;

  vector <char> theS1;
  vector <char> theS2;
  vector <char> theLink;

    // m and n need to be the size of the strings + 1
    // since the zeroeth row and column are used to
    // hold the initial scores:

  n = S1.size() + 1;
  m = S2.size() + 1;

    // create a table of DP_cell's, m x n size
    // Key:
    // y = n = i = a = row
    // x = m = j = b = column

  struct DP_cell myTable[n][m];

    // initialize scores in the table:
    // T(0,0) = 0
    // for (i=1 to m):
    //  T(i, 0) = i * g
    // for (j = 1 to n):
    //  T(0,j) = j * g

    // initialize everything to zero:

  for (a = 0; a < n; a++)
  {
    for (b = 0; b < m; b++)
    {
      myTable[a][b].score = 0;
    }
  }

  //myTable[0][0].score = 0;

    // initialize the zeroeth row and column
    // to j * g and i * g, respectively

  for (i = 1; i < n; i++)
  {
    myTable[i][0].score = i * g;
  } // end initialize column i to zero

  for (j = 1; j < m; j++)
  {
    myTable[0][j].score = j * g;
  } // end initialize row j to j * g

    // calculate all scores:
    // Since row 0 and column 0 contain initializing scores,
    // we need to begin at row 1 and column 1:

  i = 1;
  j = 1;

  for (i = 1; i < n; i++)
  {
    for (j = 1; j < m; j++)
    {
        // calculate substitute score:
        // !!!remember!!! that i and j are indexes for the table positions,
        // and their complemntary positions in the strings are one less than
        // the table position!!!

      subs = ((myTable[i-1][j-1].score) + (S(S1[i-1], S2[j-1])) );
      //cout << "i: " << i << " ,j:" << j << " :S1[i-1]: " << S1[i-1] << " :S2[j-1]: " << S2[j-1] << endl;
      max = subs;

        // calculate deletion score:

      del = ((myTable[i-1][j].score) + g);

        // if del is greater than max, make it new max

      if (del > max)
      {
        max = del;

      } // end if del is greater than max, make it new max

        // calculate insertion score:

      ins = ((myTable[i][j-1].score) + g);

      // if del is greater than max, make it new max

      if (ins > max)
      {
        max = ins;

      } // end if ins is greater than max, make it new max

      myTable[i][j].score = max;

    } // end inner loop

  } // end outer loop


    // backtrace:
    // use three vectors to hold characters:
    // theS1 will hold the characters for S1,
    // theS2 will hold the characters for S2,
    // theLink will hold the "|" character or " "
    // to indicate yes or no for match between them

    // m and n are 1 + the size of S1 and S2, respectively,
    // Their indexes are 1 less than their size,

  i = n - 1;
  j = m - 1;

  cout << "Global score: " << myTable[i][j].score << endl;

  cout << "backtrace: " << endl;

  while ( (i != 0) && (j != 0) )
  //while ( max != 0 )
  {
      // the maxInd is a key to let me know which path has the highest score
      // 0 = diagonal or substitution,
      // 1 = up or deletion
      // 2 = left or insertion

    subs = myTable[i-1][j-1].score;
    max = subs;
    maxInd = 0;

    del = myTable[i][j-1].score;
    if (del > max)
    {
      max = del;
      maxInd = 1;
    } // end if del > max, update max

    ins = myTable[i-1][j].score;
    if (ins > max)
    {
      max = ins;
      maxInd = 2;

    } // end if del > max, update max

      // update the vectors appropriately:

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

      i--;
      j--;

    } // end if substitution

    if (maxInd == 1)
    {
      theS1.push_back(S1[i-1]);
      theS2.push_back('-');
      *gapCount = *gapCount += 1;

      theLink.push_back (' ');

      i--;

    } // end if deletion

    if (maxInd == 2)
    {
      theS1.push_back('-');
      theS2.push_back(S2[j-1]);
      *gapCount = *gapCount += 1;

      theLink.push_back (' ');

      j--;

    } // end if insertion

  } // end while loop to backtrace

    // reverse the vectors:

  theS1 = reverseVector (theS1);
  theLink = reverseVector (theLink);
  theS2 = reverseVector (theS2);

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

  /*
  cout << "S1 ";
  while (theS1[a])
  {
    cout << theS1[a];
    a++;

  } // end print out theS1

  cout << endl;

  a = 0;
  cout << "   ";
  while (theLink[a])
  {
    cout << theLink[a];
    a++;

  } // end print out theLink

  cout << endl;

  a = 0;
  cout << "S2 ";
  while (theS2[a])
  {
    cout << theS2[a];
    a++;

  } // end print out theS2

  cout << endl << endl;
  */

  /*

    // print the matrix (for debugging)

  for (int a = 0; a < m; a++)
  {
    for (int b = 0; b < n; b++)
    {
      cout << myTable[a][b].score << ",";
    }
    cout << endl;

  } // end for loop to print the matrix

  */

} // end function runGlobal
