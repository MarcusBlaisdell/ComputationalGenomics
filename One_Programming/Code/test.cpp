
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

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

void myFuncTest (int *theVar)
{
  *theVar = *theVar + 2;

}

int main (int argc, char * argv[])
{
  int n = 3, m = 4, i = 0, j = 0;
  int myTable[n][m];
  int theVar = 1;
  string thisString = "thisString";

  cout << "thisString.size(): " << thisString.size() << endl;

  cout << "theVar before: " << theVar << endl;
  myFuncTest (&theVar);
  cout << "theVar after: " << theVar << endl;

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < m; j++)
    {
      myTable[i][j] = 0;
    }
  }

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < m; j++)
    {
      cout << myTable[i][j] << " - ";
    }
    cout << endl;
  }

  for (i = 0; i < n; i++)
  {
    myTable[i][0] = i;
  }
  cout << endl;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < m; j++)
    {
      cout << myTable[i][j] << " - ";
    }
    cout << endl;
  }

  for (j = 0; j < m; j++)
  {
    myTable[0][j] = 4 - j;
  }
  cout << endl;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < m; j++)
    {
      cout << myTable[i][j] << " - ";
    }
    cout << endl;
  }

  for (int z = 0; z < 5; z++)
  {
    cout << "z: " << z << endl;
  }
  /*
  ifstream inFile ("parameters.config");

  string str;
  string toNum = "7";
  string theString = "abcdef";
  int theNum;
  theNum = stoi (toNum);
  cout << "theNum: " << theNum << endl;
  cout << "theNum + 12 = " << theNum + 12 << endl;

  theString = reverseString (theString);
  cout << "theString: " << theString << endl;

  int d = 0, e = 0;
  int myTable[3][4];

  for (d = 0; d < 3; d++)
  {
    for (e = 0; e < 4; e++)
    {
      myTable[d][e] = 0;
    }

  }

  myTable[0][1] = 1;
  myTable[2][2] = 2;

  for (d = 0; d < 3; d++)
  {
    for (e = 0; e < 4; e++)
    {
      cout << myTable[d][e];
    }
    cout << endl;

  } // end for loop


  getline (inFile, str);

  int i = 0, j = 0;
  string word, theWord, test = "abc";

  word.append(test, 0,2);

  cout << "word: " << word << endl;

  if (word == "ab")
  {
    cout << "matched\n";
  }

  vector <char> testVector;
  testVector.push_back ('a');
  testVector.push_back ('b');
  testVector.push_back ('c');

  i = 0;
  cout << "testVector: ";
  while (testVector[i])
  {
    cout << testVector[i];
    i++;
  }

  cout << endl;
  */

  /*
  while (str[i])
  {
    if (str[i] == '\t' || str[i] == ' ')
    {
      word[j] = '\0';
      cout << "closing word as: " << word[0] << word[j - 1] << endl;
      theWord = word;
      j = 0;
      word = "";
      cout << "tab!\n";
    }
    else
    {
      word[j] = str[i];
      cout << "str[" << i << "]: " << str[i] << endl;
      //cout << "word[" << j << "]: " << word[j] << endl;

    }
    i++;
    j++;

  }

  cout << "theWord: " << theWord << endl;
  if (theWord == "match")
  {
    cout << "match matches\n";
  }
  */

  /*
  stringstream strstr(str);

  istream_iterator<string> it(strstr);
  istream_iterator<string> end;
  vector <string> results (it, end);

  cout << "results[0]: " << results[0] << endl;
  cout << "results[1]: " << results[1] << endl;

  */

  /*
  // char testThis[] = "match  7";
  string testThisx = "match  7";

  char * lineList[2];

  char * token = strtok (testThis, " ");

  int i = 0;

  while (token != NULL)
  {
    lineList[i++] = token;
    cout << "token: " << token << endl;
    token = strtok (NULL, " ");
  }

  cout << "token[0]: " << lineList[0] << endl;
  cout << "token[1]: " << lineList[1] << endl;

  if (strcmp(lineList[0], "match") == 0)
  {
    cout << "match found, value = " << lineList[1] << endl;
  }
  */
}
