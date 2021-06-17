////////////////////////////////////////
//
// Marcus Blaisdell
// CptS 471
// Programming Assignment 2
// March 30, 2019
// Professor Kalyanaraman
//
// header.h
//
////////////////////////////////////////

#include <string.h>
#include <vector>

using namespace std;

typedef struct node
{
  int nodeID;
  struct node * SL = NULL;
  struct node * parent;
  //string edgeLabel;
  int edgeLabel[2];
  vector <struct node * > child;
  int stringDepth;

} aNode;

// global variables

// store the data we read
// in from the file as a
// global string
// We will need to access
// this from many functions

string theData;

// We will number leaf nodes up from 0:
// We will number internal nodes up from n:

int leafID;
int internalID;

// create a global pointer to an aNode
// to track nodes that need to have the suffix link updated:

aNode * SLHolder;

// create a pointer to a node to store our current location:

aNode * u;

// create a global integer to store a position:

int edgePos;

// create a global integer to store a child number:

int childNum;

// create global integers to store our current
// string position and length:

int curPos;
int curLen;


  // statistics:

int numInternalNodes;
int numLeaves;
int totalNodes;
int byteSize;
float avgStringDepth;
int depthSum;
int stringSize;
int deepest;
