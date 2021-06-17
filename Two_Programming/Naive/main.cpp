//////////////////////////////////////////////////////
//
// Marcus Blaisdell
// CptS 471
// Programming Assignment 2
// March 30, 2019
// Professor Kalyanaraman
//
//////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <chrono>
#include "header.h"

using namespace chrono;

//#define DEBUG
//#define DEBUG1
#define NAIVE

// readString function

void readFile (string fileName, string *dataName, string *theString)
{
  string line;
  int i = 1;
  //cout << "readFile called" << endl;

  ifstream inputFile (fileName);

    // first line should be information, but verify it

  getline (inputFile, line);

  if (line[0] == '>')
  {
    while (line[i] != ' ' && line[i])
    {
      *dataName += (line[i]);

      i++;

    } // end while loop to get data name

    //getline (inputFile, line);

    while (getline (inputFile, line))
    {
      theString->append (line);

    } // end read the data in

  } // end if data line

} // end function readString

// print pointers:

void printPointers()
{
  cout << "\t*** current pointers ***\n" << endl;
  cout << "\t*** curPtr->nodeID: " << curPtr->nodeID;
  cout << ", (" << curPtr->edgeLabel[0];
  cout << ", " << curPtr->edgeLabel[1] << ") ";
  cout << " : parent: " << curPtr->parent->nodeID;
  cout << ", (" << curPtr->parent->edgeLabel[0];
  cout << ", " << curPtr->parent->edgeLabel[1] << ") " << endl;
  cout << "\t*** u->nodeID: " << u->nodeID;
  cout << " : parent: " << u->parent->nodeID;
  cout << ", (" << u->parent->edgeLabel[0];
  cout << ", " << u->parent->edgeLabel[1] << ") ";
  if (u->SL != NULL)
  {
    cout << " : u->SL->nodeID: " << u->SL->nodeID;
    cout << ", (" << u->SL->edgeLabel[0];
    cout << ", " << u->SL->edgeLabel[1] << ")" << endl;
  }
  else
  {
    cout << " : SL is NULL" << endl;
  }

  cout << "\t*** u_prime->nodeID: " << u_prime->nodeID;
  cout << ", (" << u_prime->edgeLabel[0];
  cout << ", " << u_prime->edgeLabel[1] << ") ";
  cout << " : parent: " << u_prime->parent->nodeID;
  cout << ", (" << u_prime->parent->edgeLabel[0];
  cout << ", " << u_prime->parent->edgeLabel[1] << ") ";
  if (u->SL != NULL)
  {
    cout << " : u_prime->SL->nodeID: " << u_prime->SL->nodeID << endl;
    cout << ", (" << u_prime->SL->edgeLabel[0];
    cout << ", " << u_prime->SL->edgeLabel[1] << ") ";
  }
  else
  {
    cout << " : SL is NULL" << endl;
  }

  cout << "\t*** v->nodeID: " << v->nodeID;
  cout << ", (" << v->edgeLabel[0];
  cout << ", " << v->edgeLabel[1] << ") ";
  cout << " : parent: " << v->parent->nodeID;
  cout << ", (" << v->parent->edgeLabel[0];
  cout << ", " << v->parent->edgeLabel[1] << ") ";
  if (u->SL != NULL)
  {
    cout << " : v->SL->nodeID: " << v->SL->nodeID;
    cout << ", (" << v->SL->edgeLabel[0];
    cout << ", " << v->SL->edgeLabel[1] << ")" << endl;
  }
  else
  {
    cout << " : SL is NULL" << endl;
  }

  cout << "\t*** v_prime->nodeID: " << v_prime->nodeID;
  cout << ", (" << v_prime->edgeLabel[0];
  cout << ", " << v_prime->edgeLabel[1] << ") ";
  cout << " : parent: " << v_prime->parent->nodeID;
  cout << ", (" << v_prime->parent->edgeLabel[0];
  cout << ", " << v_prime->parent->edgeLabel[1] << ") ";
  if (u->SL != NULL)
  {
    cout << " : v_prime->SL->nodeID: " << v_prime->SL->nodeID;
    cout << ", (" << v_prime->SL->edgeLabel[0];
    cout << ", " << v_prime->SL->edgeLabel[1] << ")" << endl;
  }
  else
  {
    cout << " : SL is NULL" << endl;
  }

} // end printPointers function

  // findPath function:
  // accepts:
  //          pointer to a node,
  //          current string index,
  //          string length
  // returns bool, true if path is found,
  // false if path is not found

bool findPath (aNode * theNode, int i, int len)
{
  #ifdef DEBUG
  cout << "\n\t*** findPath called ***\n" << endl;
  cout << "curPtr->nodeID: " << curPtr->nodeID;
  cout << ", (" << curPtr->edgeLabel[0];
  cout << ", " << curPtr->edgeLabel[1] << ") ";
  cout << " - i: " << i << " - len: " << len << endl;
  cout << "theNode->nodeID: " << theNode->nodeID << endl;
  #endif

  //i += theNode->stringDepth;
  //len -= theNode->stringDepth;

  int j = 0, k = 0, l = 0, childNum = 0;
  int found = 0;
  bool pathFound;
  int m = i + len;

    // only run if there is a character to evaluate:
    // (if S[i])

    // get the size of the children list:

  l = curPtr->child.size ();

  if (theString[i])
  {
    if (l == 0)
    {
      return false;

    } // end if no children, return false
    else
    {

        // (pick a branch out of u that starts with S[i]:)
        // iterate through all children and check if their
        // edgeLabels begin with the character of our insert string:

      for (k = 0; k < l; k++)
      {
        if ( (theString[i]) == (theString[curPtr->child[k]->edgeLabel[0]]) )
        {
          found = 1;

          childNum = k;

          #ifdef DEBUG
          cout << "child found : child: " << childNum << endl;
          #endif

          break;
        } // end if we found a path

      } // end look for child

      // if we iterated though the children and
      // did not find one that begins with our character,
      // return false:
      // (if no branch exists, return false )

      if (found == 0)
      {
        #ifdef DEBUG
        cout << "findPath child-path not found, curPtr->nodeID: " << curPtr->nodeID << endl;
        #endif

        return false;

      } // return false if no path found
      else
      {
          // let alpha = edgeLabel (e): j = 1

        alpha[0] = curPtr->child[childNum]->edgeLabel[0];
        alpha[1] = curPtr->child[childNum]->edgeLabel[1];

          // while i <= m and alpha[j] exists:

        if (alpha[1] < len)
        {
          //while (i <= m && theString[curPtr->child[childNum]->edgeLabel[0] + j])
          for (j = 0; j < alpha[1]; j++)
          {
            #ifdef DEBUG1
            cout << "i: " << i << ", edgeLabel[0]: ";
            cout << alpha[0];
            cout << ", j: " << j << endl;
            cout << "theString[i]: " << theString[i];
            cout << "  -  theString[alpha[0] + j]]: ";
            cout << theString[alpha[0] + j] << endl;
            #endif

            if (theString[i] == theString[alpha[0] + j])
            {

              i++;
              //j++;
            } // end continue evaluating while matches
            else
            {
              #ifdef DEBUG1
              cout << "\t************* mismatch *****************" << endl;
              cout << "theString[i]: " << theString[i];
              cout << "  -  theString[alpha[0] + " << j;
              cout << "]]: " << theString[alpha[0] + j] << endl;
              #endif

              return false;

            } // end return false if mismatch

          } // end while/for to evaluate the string

          #ifdef DEBUG1
          cout << "recursion: findPath, curPtr->nodeID: " << curPtr->nodeID;
          cout << " : child: " << childNum;
          cout << ", i: " << i;
          cout << ", len: " << len;
          cout << ", alpha[1]: " << alpha[1] << endl;
          #endif

          curPtr = curPtr->child[childNum];
          //pathFound = findPath (curPtr->child[childNum], i + alpha[1], len - alpha[1]);
          pathFound = findPath (curPtr, i + alpha[1], len - alpha[1]);

          return pathFound;

        } // end if edge label is shorter than evaluation string
        // else, label is longer than evaluation string:
        else
        {
          // if the edge label is longer than evaluation string,
          // evaluate entire string, if it matches, return true,
          // if not, return false:

          j = 0;

          while (i <= m)
          {
            #ifdef DEBUG1
            cout << "theString[" << i << "]: " << theString[i];
            cout << "  -  theString[u->child[childNum]->edgeLabel[0] + j]]: ";
            cout << theString[curPtr->child[childNum]->edgeLabel[0] + j] << endl;
            #endif

            if (theString[i] == theString[curPtr->child[childNum]->edgeLabel[0] + j])
            {
              i++;
              j++;

            } // end if matches
            else
            {
              #ifdef DEBUG1
              cout << "mismatch, return false" << endl;
              #endif
              return false;

            } // end else, mismatch, return false


          } // end while loop

            // if we get here, the full string matched,

          return true;

        } // end else, label longer than string



      } // end else, evaluate the child

    } // end look for path in child list

    if (pathFound == true)
    {
      cout << "\t***\t*** Here ***\t***" << endl;
      cout << "\t***\t*** Here ***\t***" << endl;
      cout << "\t***\t*** Here ***\t***" << endl;
      u = curPtr->child[childNum];
      curPtr = curPtr->child[childNum];

      #ifdef DEBUG1
      cout << "recursive call to findPath: " << endl;
      cout << "curPtr->child.size(): " << curPtr->child.size() << endl;
      cout << "childNum: " << childNum << endl;
      cout << "curPtr->nodeID: " << curPtr->nodeID;
      cout << ", (" << i;
      cout << ", " << len - j;
      cout << ")" << endl;
      #endif
      pathFound = findPath (u, i, len - j);

    } // end if recursive call returned pathFound == true


  } // end if there is a character to evaluate

  return pathFound;

} // end findPath function

// forward declarations
void insertChild (int, int);
void insertEdge (int, int, int, int);

/////
// insertSuffix function:
// accepts:
//          pointer to a node,
//          current string index,
//          string length
// moves to the correct node insertion point,
// and calls the correct insertion function,
// insertChild, or insertEdge


void insertSuffix (aNode * theNode, int i, int len)
{
  #ifdef DEBUG
  cout << "\n\t*** insertSuffix called ***\n" << endl;
  cout << "curPtr->nodeID: " << curPtr->nodeID;
  cout << ", (" << curPtr->edgeLabel[0];
  cout << ", " << curPtr->edgeLabel[1] << ") ";
  cout << " - i: " << i << " - len: " << len << endl;
  cout << "theNode->nodeID: " << theNode->nodeID << endl;
  #endif

  //i += theNode->stringDepth;
  //len -= theNode->stringDepth;

  int j = 0, k = 0, l = 0, childNum = 0;
  int found = 0;
  bool pathFound;
  int m = i + len;

    // only run if there is a character to evaluate:
    // (if S[i])

    // get the size of the children list:

  l = curPtr->child.size ();

  if (theString[i])
  {
    if (l == 0)
    {
      insertChild (i, len);

      return;

    } // end if no children, use insertChild
    else
    {

        // (pick a branch out of u that starts with S[i]:)
        // iterate through all children and check if their
        // edgeLabels begin with the character of our insert string:

      for (k = 0; k < l; k++)
      {
        if ( (theString[i]) == (theString[curPtr->child[k]->edgeLabel[0]]) )
        {
          found = 1;

          childNum = k;

          #ifdef DEBUG
          cout << "child found : child: " << childNum << endl;
          #endif

          break;
        } // end if we found a path

      } // end look for child

      // if we iterated though the children and
      // did not find one that begins with our character,
      // use insertChild

      if (found == 0)
      {
        #ifdef DEBUG
        cout << "findPath child-path not found, curPtr->nodeID: " << curPtr->nodeID << endl;
        #endif

        insertChild (i, len);

        return;

      } // if no path found, insertChild
      else
      {
          // let alpha = edgeLabel (e):

        alpha[0] = curPtr->child[childNum]->edgeLabel[0];
        alpha[1] = curPtr->child[childNum]->edgeLabel[1];

          // while i <= m and alpha[j] exists:

        if (alpha[1] < len)
        {
          for (j = 0; j < alpha[1]; j++)
          {
            #ifdef DEBUG1
            cout << "i: " << i << ", edgeLabel[0]: ";
            cout << alpha[0];
            cout << ", j: " << j << endl;
            cout << "theString[i]: " << theString[i];
            cout << "  -  theString[alpha[0] + j]]: ";
            cout << theString[alpha[0] + j] << endl;
            #endif

            if (theString[i + j] != theString[alpha[0] + j])
            {
              #ifdef DEBUG1
              cout << "\t************* mismatch *****************" << endl;
              cout << "theString[i]: " << theString[i];
              cout << "  -  theString[alpha[0] + " << j;
              cout << "]]: " << theString[alpha[0] + j] << endl;
              cout << "i: " << i << endl;
              #endif

              insertEdge (i, len, childNum, j);

              return;

            } // end insert on mismatch

          } // end while/for to evaluate the string

          #ifdef DEBUG1
          cout << "recursion: findPath, curPtr->nodeID: " << curPtr->nodeID;
          cout << " : child: " << childNum;
          cout << ", i: " << i;
          cout << ", len: " << len;
          cout << ", alpha[1]: " << alpha[1] << endl;
          #endif

            // if we are not at the right node to insert,
            // use recursion to find the right one:

          curPtr = curPtr->child[childNum];
          //pathFound = findPath (curPtr->child[childNum], i + alpha[1], len - alpha[1]);
          insertSuffix (curPtr, i + alpha[1], len - alpha[1]);

          return;

        } // end if edge label is shorter than evaluation string
        // else, label is longer than evaluation string:
        else
        {
          // if the edge label is longer than evaluation string,
          // evaluate entire string, if it matches, return true,
          // if not, return false:

          j = 0;

          while (i <= m)
          {
            #ifdef DEBUG1
            cout << "theString[" << i << "]: " << theString[i];
            cout << "  -  theString[u->child[childNum]->edgeLabel[0] + j]]: ";
            cout << theString[curPtr->child[childNum]->edgeLabel[0] + j] << endl;
            #endif

            if (theString[i + j] == theString[curPtr->child[childNum]->edgeLabel[0] + j])
            {
              //i++;
              j++;

            } // end if matches
            else
            {
              #ifdef DEBUG1
              cout << "mismatch, return false" << endl;
              #endif

              insertEdge (i, len, childNum, j);

              return;

            } // end else, mismatch, return false


          } // end while loop

            // if we get here, the full string matched,
            // nothing to add, set current pointer
            // to the matching node, and return

          curPtr = curPtr->child[childNum];

          return;

        } // end else, label longer than string



      } // end else, evaluate the child

    } // end look for path in child list

      // shouldn't ever get to here, but,

      cout << "*** CATCHALL1 *** \t- check the insertSuffix function" << endl;

      curPtr = curPtr->child[childNum];

      return;

  } // end if there is a character to evaluate

  // shouldn't ever get to here, but,

  cout << "*** CATCHALL1 *** \t- check the insertSuffix function" << endl;

  curPtr = curPtr->child[childNum];

  return;

} // end insertSuffix function
/////

// insert Node functions
// Two cases:
// 1) insert a node as a child
//    of the current node:
//    insertChild
// 2) insert a node within the
//    edge of a child of the
//    current node:
//    insertEdge

  // insertNode function evaluates for the correct
  // condition and calls the correct function:


void insertNode (int i, int len)
{
  #ifdef DEBUG1
  cout << "\n\t\t *** insertNode called ***\n" << endl;
  cout << "curPtr->nodeID: " << curPtr->nodeID;
  cout << ", i: " << i << ", len: " << len;
  cout << ", curPtr->stringDepth: " << curPtr->stringDepth << endl;
  #endif

  i += curPtr->stringDepth;
  len -= curPtr->stringDepth;

  int j = 0, k = 0, childNum = 0;
  int found = 0;

  j = curPtr->child.size();

    // if the current node has no children,
    // just call insertChild

  if (j == 0)
  {
    insertChild (i, len);

    return;

  } // just insert child

    // else, see if there is a child
    // that begins with the character
    // our current string begins with:

  else
  {
    for (k = 0; k < j; k++)
    {
      #ifdef DEBUG1
      cout << "i: " << i << ", k: " << k << " : ";
      cout << "theString[i]: " << theString[i];
      cout << " : theString[curPtr->child[k]->edgeLabel[0]]: ";
      cout << theString[curPtr->child[k]->edgeLabel[0]] << endl;
      #endif

      if (theString[i] == theString[curPtr->child[k]->edgeLabel[0]])
      {
        found = 1;
        childNum = k;
        break;
      } // end if child path found

    } // end check all children

    if (found == 1)
    {
      #ifdef DEBUG
      cout << "insertNode, child-path found, " << childNum << endl;
      #endif
      //i += curPtr->stringDepth;
      //len -= curPtr->stringDepth;

      insertEdge (i, len, childNum, 0);

    } // end if found
    else
    {
      #ifdef DEBUG
      cout << "insertNode, no path found" << endl;
      #endif

      insertChild (i, len);

    } // end

  } // end evaluate case

} // end insertNode function

  // insertChild function:


void insertChild (int i, int len)
{
  #ifdef DEBUG1
  cout << "\n\t*** insertChild called ***\n" << endl;
  cout << "curPtr->nodeID: " << curPtr->nodeID;
  cout << ", (" << i << ", " << len << ")" << endl;
  #endif

  int j = 0, k = 0;

  aNode * newLeafNode = new aNode;

  newLeafNode->nodeID = leafID++;
  newLeafNode->parent = curPtr;
  newLeafNode->edgeLabel[0] = i;
  newLeafNode->edgeLabel[1] = len;
  newLeafNode->stringDepth = curPtr->stringDepth + len;

    // insert-in-order to children list
    // if there are currently no children, simply add it:

  if (curPtr->child.size() == 0)
  {
    curPtr->child.push_back (newLeafNode);

    curPtr = newLeafNode;

    return;

  } // end if no children just add it

  // if there are children, find the correct insert point
  else
  {
    #ifdef DEBUG
    cout << "curPtr->nodeID: " << curPtr->nodeID;
    cout << " at iterator" << endl;
    #endif

    vector <aNode *>::iterator it = curPtr->child.begin();

      // if we are inserting a '$', insert at beginning:

    if (theString[i] == '$')
    {
      curPtr->child.insert (it, newLeafNode);

      curPtr = newLeafNode;

      return;

    } // end if '$', insert at beginning
    else
    {
        // get the size of the child list as j:

      j = curPtr->child.size ();

      #ifdef DEBUG
      cout << "number of children, j: " << j << endl;
      #endif

        // iterate through child list to find insertion point:

      for (k = 0; k < j; k++)
      {
        if (theString[curPtr->child[k]->edgeLabel[0]] > theString[i])
        {
          curPtr->child.insert (it, newLeafNode);

          curPtr = newLeafNode;

          return;

        } // end insert if we found right spot

        it++;

      } // end for loop to check all children

      // if we got here, new leaf node is greater than
      // existing children, add to end:

      curPtr->child.push_back (newLeafNode);

      curPtr = newLeafNode;

      return;

    } // end else find right spot

  } // end else, insert-in-order to child list

  cout << "Something happened and insertChild did not insert a child" << endl;

  return;

} // end insertChild function

  // insertEdge function
void insertEdge (int i, int len, int childNum, int offset)
{
  #ifdef DEBUG1
  cout << "\n\t*** insertEdge called ***\n" << endl;
  cout << "\tinsert to  " << curPtr->nodeID;
  cout << ", child: " << childNum;
  cout << ", (" << curPtr->edgeLabel[0];
  cout << ", " << curPtr->edgeLabel[1] << ")";
  cout << " : i: " << i << " : len: " << len << endl;
  #endif

    // create two new nodes, one internal, one leaf:

  aNode * newInternalNode = new aNode;
  aNode * newLeafNode = new aNode;

  // set variables:

  newInternalNode->nodeID = internalID++;
  newInternalNode->parent = curPtr;
  newInternalNode->edgeLabel[0] = curPtr->child[childNum]->edgeLabel[0];
  newInternalNode->edgeLabel[1] = offset;
  newInternalNode->stringDepth = curPtr->stringDepth + offset;

    // if the internal node has a depth of 1,
    // it will not have a suffix link, except for root,
    // which should be the current nodes parent:

  if (newInternalNode->stringDepth == 1)
  {
    newInternalNode->SL = curPtr->parent;
  }

  newLeafNode->nodeID = leafID++;
  newLeafNode->parent = newInternalNode;
  newLeafNode->edgeLabel[0] = i + offset;
  newLeafNode->edgeLabel[1] = len - offset;
  newLeafNode->stringDepth = curPtr->stringDepth + len;
  #ifdef DEBUG
  cout << "i: " << i << " : offset: " << offset << " : i + offset: " << i + offset << endl;
  #endif

  curPtr->child[childNum]->edgeLabel[0] += offset;
  curPtr->child[childNum]->edgeLabel[1] -= offset;
  curPtr->child[childNum]->parent = newInternalNode;


    // insert-in-order newLeafNode and
    // curPtr->child[childNum] to
    // newInternalNode->child list:

  #ifdef DEBUG1
  cout << "theString[newLeafNode->edgeLabel[0]]: ";
  cout << theString[newLeafNode->edgeLabel[0]];
  cout << " : theString[curPtr->child[childNum]->edgeLabel[0]]: ";
  cout << theString[curPtr->child[childNum]->edgeLabel[0]] << endl;
  #endif

  if ((theString[newLeafNode->edgeLabel[0]] == '$') ||
      (theString[newLeafNode->edgeLabel[0]] <
      theString[curPtr->child[childNum]->edgeLabel[0]]) )
  {
    newInternalNode->child.push_back (newLeafNode);
    newInternalNode->child.push_back (curPtr->child[childNum]);

  } // end insert newLeafNode first
  else
  {
    newInternalNode->child.push_back (curPtr->child[childNum]);
    newInternalNode->child.push_back (newLeafNode);

  } // end else, insert curPtr->child[childNum] first

    // update curPtr->child[childNum] to point
    // to the new internal node:

  curPtr->child[childNum] = newInternalNode;

  curPtr = newLeafNode;

} // end insertEdge function

// add_v functions,
// two possibilities,
// 1) we need to add v as a child of
//    the current node,
// 2) we need to add v to the edge of a child
//    of the current node

void add_v_edge (int i, int len, int childNum)
{
  #ifdef DEBUG1
  cout << "\n\t*** add_v_edge called ***\n" << endl;
  cout << "curPtr->nodeID: " << curPtr->nodeID;
  cout << " : childNum: " << childNum << endl;
  #endif

  int j = 0, k = 0;
  int found = 0;

    // create a new internal Node:

  aNode * newInternalNode = new aNode;

  newInternalNode->nodeID = internalID++;
  newInternalNode->parent = curPtr;

    // find the correct child to add the node to:

  /*
  j = curPtr->child.size ();

  for (k = 0; k < j; k++)
  {
    if (theString[i] == theString[curPtr->child[k]->edgeLabel[0]])
    {
      found = 1;
      childNum = k;
      break;

    } // end we found the correct child

  } // end find the correct child
  */

  //if (found == 1)
  //{
      // find the edge position we need to add the
      // new internal node at:
      // iterate through the edge until we find a mismatch:

    j = 0;

    while (theString[i + j] == theString[curPtr->child[childNum]->edgeLabel[0] + j] )
    {
      #ifdef DEBUG1
      cout << "theString[i + j]: " << theString[i + j];
      cout << " : theString[curPtr->child[childNum]->edgeLabel[0] + j]: ";
      cout << theString[curPtr->child[childNum]->edgeLabel[0] + j] << endl;
      #endif

      j++;

    } // end while loop to find insert location

    #ifdef DEBUG1
    cout << "******** mismatch found ***********" << endl;
    cout << "theString[i + j]: " << theString[i + j];
    cout << " : theString[curPtr->child[childNum]->edgeLabel[0] + j]: ";
    cout << theString[curPtr->child[childNum]->edgeLabel[0] + j] << endl;
    #endif

    // now that we found the right location,
    // insert the internal node along the edge:

    newInternalNode->edgeLabel[0] = i + j;
    newInternalNode->edgeLabel[1] = len - j;
    newInternalNode->stringDepth = curPtr->stringDepth + j;
    if (newInternalNode->stringDepth == 1)
    {
      newInternalNode->SL = curPtr->parent;
    }

      // update the child edgeLabel information:

    curPtr->child[childNum]->edgeLabel[0] += j;
    curPtr->child[childNum]->edgeLabel[1] -= j;

      // point child to new internal node:

    curPtr->child[childNum]->parent = newInternalNode;

    newInternalNode->child.push_back (curPtr->child[childNum]);

    curPtr->child[childNum] = newInternalNode;

    curPtr = newInternalNode;
    v = newInternalNode;

    return;

  //} // end if we found the correct child
  /*
  else
  {
      // we shouldn't get here, print error if we do:

    cout << "error, no child found for add_v_edge" << endl;

  } // end else, no child found
  */

} // end add_v_edge function

void add_v_child (int i, int len)
{
  #ifdef DEBUG1
  cout << "\n\t*** add_v_child called ***\n" << endl;
  cout << "curPtr->nodeID: " << curPtr->nodeID << endl;
  #endif

  int j = 0, k = 0, l = 0;

    // create a new internal node:

  aNode * newInternalNode = new aNode;

  newInternalNode->nodeID = internalID++;
  newInternalNode->parent = curPtr;
  newInternalNode->edgeLabel[0] = i;
  newInternalNode->edgeLabel[1] = len;
  newInternalNode->stringDepth = curPtr->stringDepth + len;
  if (newInternalNode->stringDepth == 1)
  {
    newInternalNode->SL = curPtr->parent;
  }

  // add new internal node as a child of the curPtr node,
  // insert-in-order:

  vector <aNode *>::iterator it = curPtr->child.begin();

  if (theString[i] == '$')
  {
    curPtr->child.insert (it, newInternalNode);

    curPtr = newInternalNode;
    v = newInternalNode;

    return;

  } // end add at beginning if '$'
  else
  {
    while (it != curPtr->child.end() )
    {
      if (theString[curPtr->child[l]->edgeLabel[0]] > theString[i])
      {
        curPtr->child.insert (it, newInternalNode);

        curPtr = newInternalNode;
        v = newInternalNode;

        return;
      } // end insert in correct location

      it++;
      l++;

    } // end iterate through children

    // if we get here, add at end:

    curPtr->child.push_back (newInternalNode);

    curPtr = newInternalNode;
    v = newInternalNode;

    return;

  } // end else, iterate to correct position


} // end add_v_child function

  // NodeHopsA function:

void NodeHopsA (int i, int len, int beta[2])
{
  #ifdef DEBUG1
  cout << "\n\t*** NodeHopsA called ***\n" << endl;
  printPointers ();
  cout << ", i: " << i << ", len: " << len;
  cout << ", beta: (" << beta[0] << ", " << beta[1] << ")";
  cout << endl;
  #endif

  int j = 0, k = 0, childNum = 0;
  int found = 0;

    // 1) find a child that begins with the
    //    first character of our string:

  j = curPtr->child.size ();

  if (j == 0)
  {
    #ifdef DEBUG
    cout << "j == 0" << endl;
    #endif
    add_v_child (i, len);

    v = curPtr;
    u->SL = v;

    return;

  } // end if no children
  else
  {
    #ifdef DEBUG
    cout << "there are children: ";
    #endif
      // iterate through children to find
      // a child-path to follow:
    #ifdef DEBUG1
    for (k = 0; k < j; k++)
    {
      cout << "[" << k << "]: ";
      cout << curPtr->child[k]->nodeID << " : ";
    }
    cout << endl;
    #endif

    for (k = 0; k < j; k++)
    {
      #ifdef DEBUG1
      cout << "theString[i]: " << theString[i];
      cout << " : theString[curPtr->child[k]->edgeLabel[0]]: ";
      cout << theString[curPtr->child[k]->edgeLabel[0]] << endl;
      #endif
      if (theString[i] == theString[curPtr->child[k]->edgeLabel[0]])
      {
        found = 1;
        childNum = k;

        #ifdef DEBUG1
        cout << "NodeHopsA found a child at: " << childNum << endl;
        #endif

        break;

      } // end if we find a child

    } // end iterate through all children

    if (found == 1)
    {
      #ifdef DEBUG1
      cout << "found child: " << childNum << endl;
      #endif
      // evaluate child:
      // if it's edge length
      // is longer than the string,
      // then v does not exist
      // else, hop to child and repeat until ...

      // test if v' is root, if so, use insertEdge,

      if (v_prime->edgeLabel[0] == -1)
      {
        #ifdef DEBUG1
        //cout << "v' is root, calling add_v_edge" << endl;
        cout << "v' is root, calling findPath, and insertNode" << endl;
        #endif
        //add_v_edge (i, len, childNum); // *****
        #ifdef DEBUG1
        cout << "NodeHopsA" << endl;
        cout << "v->nodeID: " << v->nodeID;
        cout << " - i: " << i;
        cout << " - len: " << len << endl;
        cout << "calling findPath: " << endl;
        #endif
        bool pathExists = findPath (v_prime, i, len);

        #ifdef DEBUG1
        cout << "after case_IIB findPath" << endl;
        cout << "curPtr->nodeID: " << curPtr->nodeID << endl;
        #endif

        insertNode (i, len);

        v = curPtr;
        u->SL = v;

        return;
      } // end if v' is root

      else if (curPtr->child[childNum]->edgeLabel[1] > len)
      {
          // v doesn't exist, add v:
        #ifdef DEBUG1
        cout << "v does not exist, calling add_v_edge" << endl;
        #endif
        add_v_edge (i, len, childNum);

        v = curPtr;
        u->SL = v;

        return;

      } // end if edge length greater than string length
      else if (curPtr->child[childNum]->edgeLabel[1] < len)
      {
          // if the edge length is less than beta,
          // we can safely hop to the next node
          // and repeat the hop process:

          // increment i, decrement length by
          // the size of the edge:

        i += curPtr->child[childNum]->edgeLabel[1];
        len -= curPtr->child[childNum]->edgeLabel[1];

        beta[0] += curPtr->child[childNum]->edgeLabel[1];
        beta[1] -= curPtr->child[childNum]->edgeLabel[1];

          // perform the hop:
        #ifdef DEBUG1
        cout << "curPtr->nodeID: " << curPtr->nodeID << endl;
        cout << "childNum: " << childNum << endl;
        cout << "curPtr->child[childNum]->nodeID: ";
        cout << curPtr->child[childNum]->nodeID << endl;
        #endif
        curPtr = curPtr->child[childNum];

          // recursively call NodeHopsA until all node hops are complete
        #ifdef DEBUG1
        cout << "recursive call to NodeHopsA:" << endl;
        cout << "curPtr->nodeID: " << curPtr->nodeID;
        cout << " : curPtr->parent->nodeID: " << curPtr->parent->nodeID;
        cout << endl;
        #endif
        NodeHopsA (i, len, beta);

          // once we get here, we have found v,
          // point u's suffix link to v:

        v = curPtr;
        u->SL = v;

        return;

      } // end else, hop to next node

      // else, edge length matches beta:

      else
      {
        curPtr = curPtr->child[childNum];

        v = curPtr;
        u->SL = v;

        return;

      } // end else, edgeLabel length matches beta

    } // end if matching child
    // if the edge length matches beta, next node is v,
    // update pointers and return
    else
    {
        // add_v as child
      add_v_child (i, len);

      v = curPtr;
      u->SL = v;

      return;

    } // end no matching child

  } //  end else, there are children

    // if we get here, something went wrong:

  cout << "Error in NodeHopsA!" << endl;


} // end NodeHopsA function

  // NodeHopsB function:

void NodeHopsB (int i, int len, int beta[2])
{
#ifdef DEBUG1
cout << "\n\t*** NodeHopsB called ***\n" << endl;
cout << "curPtr->nodeID: " << curPtr->nodeID;
cout << " : curPtr->parent->nodeID: " << curPtr->parent->nodeID;
cout << ", i: " << i << ", len: " << len;
cout << ", beta: (" << beta[0] << ", " << beta[1] << ")";
cout << endl;
#endif

int j = 0, k = 0, childNum = 0;
int found = 0;

  // 1) find a child that begins with the
  //    first character of our string:

j = curPtr->child.size ();

if (j == 0)
{
  #ifdef DEBUG1
  cout << "j == 0" << endl;
  #endif
  add_v_child (i, len);

  v = curPtr;
  u->SL = v;

  return;

} // end if no children
else
{
  #ifdef DEBUG1
  cout << "there are children: ";

    // iterate through children to find
    // a child-path to follow:
  for (k = 0; k < j; k++)
  {
    cout << "[" << k << "]: ";
    cout << curPtr->child[k]->nodeID << " : ";
  }
  cout << endl;

  #endif

  for (k = 0; k < j; k++)
  {
    #ifdef DEBUG1
    cout << "theString[i]: " << theString[i];
    cout << " : theString[curPtr->child[k]->edgeLabel[0]]: ";
    cout << theString[curPtr->child[k]->edgeLabel[0]] << endl;
    #endif
    if (theString[i] == theString[curPtr->child[k]->edgeLabel[0]])
    {
      found = 1;
      childNum = k;

      #ifdef DEBUG1
      cout << "NodeHopsB found a child at: " << childNum << endl;
      #endif

      break;

    } // end if we find a child

  } // end iterate through all children

  if (found == 1)
  {
    #ifdef DEBUG1
    cout << "found child: " << childNum << endl;
    #endif

    // evaluate child:
    // if it's edge length
    // is longer than the string,
    // then v does not exist
    // else, hop to child and repeat until ...

    if (curPtr->child[childNum]->edgeLabel[1] > len)
    {
        // v doesn't exist, add v:
      #ifdef DEBUG1
      cout << "v does not exist, calling add_v_edge" << endl;
      #endif
      add_v_edge (i, len, childNum);

      v = curPtr;
      u->SL = v;

      return;

    } // end if edge length greater than string length
    else if (curPtr->child[childNum]->edgeLabel[1] < len)
    {
        // if the edge length is less than beta,
        // we can safely hop to the next node
        // and repeat the hop process:

        // increment i, decrement length by
        // the size of the edge:

      i += curPtr->child[childNum]->edgeLabel[1];
      len -= curPtr->child[childNum]->edgeLabel[1];

      beta[0] += curPtr->child[childNum]->edgeLabel[1];
      beta[1] -= curPtr->child[childNum]->edgeLabel[1];

        // perform the hop:
      #ifdef DEBUG1
      cout << "curPtr->nodeID: " << curPtr->nodeID << endl;
      cout << "childNum: " << childNum << endl;
      cout << "curPtr->child[childNum]->nodeID: ";
      cout << curPtr->child[childNum]->nodeID << endl;
      #endif
      curPtr = curPtr->child[childNum];

        // recursively call NodeHopsB until all node hops are complete
      #ifdef DEBUG1
      cout << "recursive call to NodeHopsB:" << endl;
      cout << "curPtr->nodeID: " << curPtr->nodeID;
      cout << " : curPtr->parent->nodeID: " << curPtr->parent->nodeID;
      cout << endl;
      #endif
      NodeHopsB (i, len, beta);

        // once we get here, we have found v,
        // point u's suffix link to v:

      v = curPtr;
      u->SL = v;

      return;

    } // end else, hop to next node

    // else, edge length matches beta:

    else
    {
      curPtr = curPtr->child[childNum];

      v = curPtr;
      u->SL = v;

      return;

    } // end else, edgeLabel length matches beta

  } // end if matching child
  // if the edge length matches beta, next node is v,
  // update pointers and return
  else
  {
      // add_v as child
    add_v_child (i, len);

    v = curPtr;
    u->SL = v;

    return;

  } // end no matching child

} //  end else, there are children

  // if we get here, something went wrong:

cout << "Error in NodeHopsB!" << endl;

} // end NodeHopsB function

int printDFS (aNode *, int, int);
int printPOT (aNode *, int);

  // four cases:

void case_IA (int i, int len)
{
  #ifdef DEBUG1
  cout << "\n\t*** case_IA called ***\n" << endl;
  cout << "i: " << i << " - len: " << len << endl;
  #endif

  bool pathExists;

    // take SL(u) to v:

  v = u->SL;

  curPtr = v;

  i += v->stringDepth;
  len -= v->stringDepth;

  pathExists = findPath (v, i, len);

  insertNode (i, len);


} // end case_IA function

void case_IB (int i, int len)
{
  #ifdef DEBUG1
  cout << "\n\t*** case_IB called ***\n" << endl;
  cout << "i: " << i << " - len: " << len << endl;
  #endif

  bool pathExists;

  v = u->SL;

  curPtr = v;

  #ifdef DEBUG1
  cout << "v->nodeID: " << v->nodeID;
  cout << " - i: " << i;
  cout << " - len: " << len << endl;
  #endif

  pathExists = findPath (v, i, len);

  #ifdef DEBUG1
  cout << "curPtr->nodeID: " << curPtr->nodeID;
  cout << " - i: " << i;
  cout << " - len: " << len << endl;
  #endif

  insertNode (i, len);

} // end case_IB function

void case_IIA (int i, int len)
{
  #ifdef DEBUG1
  cout << "\n\t*** case_IIA called ***\n" << endl;
  cout << "curPtr->nodeID: " << curPtr->nodeID;
  cout << " : i: " << i << " - len: " << len << endl;
  #endif

  bool pathExists;

    // u->edgeLabel = beta

  beta[0] = u->edgeLabel[0];
  beta[1] = u->edgeLabel[1];

    // set u' and v':
    // (u was set before this function was called)

  u_prime = u->parent;
  #ifdef DEBUG1
  cout << "u->nodeID: " << u->nodeID << endl;
  cout << "u_prime->nodeID: " << u_prime->nodeID << endl;
  cout << "u_prime->parent->nodeID: " << u_prime->parent->nodeID << endl;
  #endif

    // alpha_prime is alpha - x
    // where x is the first character of alpha:

  /*
  alpha_prime[0] = u->edgeLabel[0] - (u_prime->stringDepth - 1);
  alpha_prime[1] = u_prime->stringDepth - 1;
  */

  v_prime = u_prime->SL;
  #ifdef DEBUG1
  cout << "v_prime->nodeID: " << v_prime->nodeID << endl;
  #endif

  alpha_prime[0] = i += v_prime->stringDepth;
  alpha_prime[1] = len -= v_prime->stringDepth;

    // step 1, go to u,
    // step 2, go to u',
    // step 3, go to v',
    // can just skip to v':

  curPtr = v_prime;

  //i += alpha_prime[0];
  //len -= alpha_prime[1];

  #ifdef DEBUG1
  cout << "case_IIA calling NodeHopsA" << endl;
  #endif
  NodeHopsA (i, len, beta);

    // after NodeHops, we are pointing at v:

  u->SL = v;

  #ifdef DEBUG1
  cout << "v->nodeID: " << v->nodeID;
  cout << " - i: " << i;
  cout << " - len: " << len << endl;
  #endif

  pathExists = findPath (v, i, len);

  #ifdef DEBUG1
  cout << "curPtr->nodeID: " << curPtr->nodeID;
  cout << " - i: " << i;
  cout << " - len: " << len << endl;
  #endif

  insertNode (i, len);

} // end case_IIA function

void case_IIB (int i, int len)
{
  #ifdef DEBUG1
  cout << "\n\t*** case_IIB called ***\n" << endl;
  cout << "nodeID: " << curPtr->nodeID;
  cout << " - i: " << i << " - len: " << len << endl;
  #endif

  bool pathExists;

    // u->edgeLabel = beta
    // beta_prime is beta - x
    // where x is the first character of beta:

  beta_prime[0] = u->edgeLabel[0] + 1;
  beta_prime[1] = u->edgeLabel[1] - 1;

    // set u' and v':
    // (u was set before this function was called)

  u_prime = u->parent;
  v_prime = u_prime->SL;

    // step 1, go to u,
    // step 2, go to u',
    // step 3, go to v',
    // can just skip to v':

  curPtr = v_prime;

  #ifdef DEBUG1
  cout << "case_IIB calling NodeHopsB" << endl;
  #endif
  NodeHopsB (i, len, beta_prime);

    // after NodeHops, we are pointing at v:

  u->SL = v;

  #ifdef DEBUG1
  cout << "case_IIB" << endl;
  cout << "v->nodeID: " << v->nodeID;
  cout << " - i: " << i;
  cout << " - len: " << len << endl;
  cout << "calling findPath: " << endl;
  #endif
  pathExists = findPath (v, i, len);

  #ifdef DEBUG1
  cout << "after case_IIB findPath" << endl;
  cout << "curPtr->nodeID: " << curPtr->nodeID << endl;
  #endif

  insertNode (i, len);


} // end case_IIB function

void case_Naive (int i, int len)
{
  #ifdef DEBUG1
  cout << "\n\t*** case_Naive called ***\n" << endl;
  #endif

    // move to root:

  while (curPtr->edgeLabel[0] != -1)
  {
    curPtr = curPtr->parent;
  } // end move to root

  insertSuffix (curPtr, i, len);


} // end case_Naive function

// build a suffix tree:

aNode * buildSFTree ()
{
    // create a timer:
    auto startTime = steady_clock::now ();

    // create an integer to track the position in
    // the string and one to track the remaining
    // length of the string

  int index = 0, remLen = theString.length ();
  int newIndex = 0, newRemLen = 0;
  int trunc = 0;
  bool findStatus;


    // get the length of string:
    // lowercase n will be the size of the string,
    // uppercase N will be the number of nodes,
    // N = internal nodes + leaf nodes

  int n = theString.length();

    // To follow with the numbering convention
    // specified in lecture,
    // We will number leaf nodes up from 1:
    // to track internal nodes as distinguishable
    // from leaf nodes by nodeID,
    // We will number internal nodes up from n + 1:

  leafID = 1;
  internalID = n + 1;

    // create the root node:

  aNode * root = new aNode;

    // set root's variables:

  root->nodeID = internalID++;
  // root node is a special case that has it's
  // suffix-link point to itself:
  root->SL = root;
  root->parent = root;
  root->edgeLabel[0] = -1;
  root->edgeLabel[1] = 0;
  // root->child starts out empty
  root->stringDepth = 0;

    // set current node pointer u to point to root:

  curPtr = root;


    // create the tree


  while (remLen > 0)
  {

    #ifdef DEBUG1
    cout << endl;
    cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\tindex: " << index << " | remLen: " << remLen;
    cout << " | curPtr->nodeID: " << curPtr->nodeID;
    if (curPtr->SL != NULL)
    {
      cout << " | SL: " << curPtr->SL->nodeID;
    }
    cout << " | (" << curPtr->edgeLabel[0] << ", ";
    cout << curPtr->edgeLabel[1] << ")";
    cout << " | parent: " << curPtr->parent->nodeID;
    cout << " | grandparent: " << curPtr->parent->parent->nodeID;
    cout << endl << "\t";
    int z = curPtr->parent->child.size ();
    cout << " children: ";
    for (int y = 0; y < z; y++)
    {
      cout << " | " << curPtr->parent->child[y]->nodeID;
      cout << ", (" << curPtr->parent->child[y]->edgeLabel[0];
      cout << ", " << curPtr->parent->child[y]->edgeLabel[1];
      cout << ") ";
    }
    cout << "\n";
    cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
    #endif


    #ifdef NAIVE
    u = root;
    v = root;
    u_prime = root;
    v_prime = root;

    case_Naive (index, remLen);
    #else

      // presuming that each time we loop here,
      // we are pointing at a child node:

    u = curPtr->parent;
    #ifdef DEBUG
    cout << "u->nodeID: " << u->nodeID << endl;
    #endif // end Debug

      // determine which insert case we need to use:

    if (u->SL != NULL)
    {
      if (u->edgeLabel[0] == -1)
      {
          // case IB:

        case_IB (index, remLen);

      } // end if u is the root
      else
      {
          // case IA:

        case_IA (index, remLen);

      } // end else, u is not the root

    } // end if Suffix Link is known
    else
    {
      if (u->parent->edgeLabel[0] == -1)
      {
          // case IIB

        case_IIB (index, remLen);

      } // end if u' is the root
      else
      {
          // case IIA

        case_IIA (index, remLen);

      } // end if u' is not the root

    } // end suffix link is not known

    #endif // end Naive

    index++;
    remLen--;

  } // end insert until our string is empty

  auto endTime = steady_clock::now();
  cout << "Time to build Suffix Tree: ";
  cout << duration_cast<microseconds>(endTime - startTime).count () << " us\n" << endl;

  return root;

} // end buildSFTree function

  // printDFS function
  // print the tree using
  // depth-first-search

int printDFS (aNode * u, int count, int ifFirst)
{
  int i = 0, j = 0;

  /*
  if (u->nodeID > theString.size())
  {
    if (u->child.size () == 0)
    {
      //cout << "nodeID: " << u->nodeID;
      //cout << " is an internal node with no children" << endl;
      badInternals++;
    }
  }
  */

    // handle root node:
    // ifFirst flag is used to only do this the
    // very first time the function is called,
    // and to not repeat it on the recursive calls

  if (u->edgeLabel[0] == -1 && ifFirst == 0)
  {
    //cout << u->nodeID << " : " << u->stringDepth << endl;
    cout << u->nodeID << " : " << u->stringDepth << " * ";
    count++;
  } // end if we are at root, print that


  i = u->child.size ();

    // if no children, just print the edge label

  if (i == 0)
  {
    // Do nothing

  } // end just print edge label
  else
  {
    for (j = 0; j < i; j++)
    {
      //cout << u->child[j]->nodeID << " : " << u->child[j]->edgeLabel << endl;
      //cout << u->child[j]->nodeID << " : " << u->child[j]->stringDepth << endl;
      cout << u->child[j]->nodeID << " : " << u->child[j]->stringDepth << " * ";
      count++;
      //cout << "count: " << count << endl;
        // only print 10 elements per line
        // if we just printed the 10th element,
        // print newline, reset count to 0

      if (count == 10)
      {
        cout << endl;
        count = 0;
      } // end only print 10 elements per line

      if (u->child[j]->child.size () > 0)
      {
        count = printDFS (u->child[j], count, 1);

      } // end if node has children, recursively print them

    } // end print out all children

  } // end else, print all children

  return count;

} // end printDFS

// printPOT function
// print the tree using
// post-order traversal

int printPOT (aNode * u, int count)
{
  int i = u->child.size();
  int j = 0;

    // if there are children,
    // iterate though them one at a time,
    // start with left-most,
    // end with right-most

  if (i > 0)
  {
    for (j = 0; j < i; j++)
    {
      if (u->child[j]->child.size () > 0)
      {
        count = printPOT (u->child[j], count);

      } // end if there are more children, iterate through them
      else
      {
        cout << u->child[j]->nodeID << " : " << u->child[j]->stringDepth << " * ";
        count++;

          // if the count reaches 10,
          // print newline, reset count

        if (count == 10)
        {
          cout << endl;
          count = 0;

        } // end if count reaches 10, reset it

      } // end print leaf

    } // end iterate through all children

      // after printing children, print root node:

    cout << u->nodeID << " : " << u->stringDepth << " * ";
    count++;
      // if the count reaches 10,
      // print newline, reset count

    if (count == 10)
    {
      cout << endl;
      count = 0;

    } // end if count reaches 10, reset it

  } // end if there are children, iterate through them
  else
  {
    cout << u->nodeID << " : " << u->stringDepth << " * ";
    count++;
      // if the count reaches 10,
      // print newline, reset count

    if (count == 10)
    {
      cout << endl;
      count = 0;

    } // end if count reaches 10, reset it

  } // end if no children, we are at a leaf node

  return count;

} // end printPOT

// printTree function
// print the tree

void printTree (aNode * u)
{
  int i = 0, j = 0, k = 0;

  cout << "id: " << u->nodeID;
  cout << ", (" << u->edgeLabel[0] << ", ";
  cout << u->edgeLabel[1] << ") " << "   parent: " << u->parent->nodeID << "   SL: ";

  if (u->SL != NULL)
  {
    cout << u->SL->nodeID;
  }
  else
  {
    cout << 0;
  }

  cout << "   depth: " << u->stringDepth << "   children: ";


  // print all children

  i = u->child.size ();

    // if no children, just print the edge label

  if (i == 0)
  {
    return;

  } // end just print edge label
  else
  {
    for (j = 0; j < i; j++)
    {
      cout << u->child[j]->nodeID << " ";
    } // end print out all children

    cout << endl;

    for (j = 0; j < i; j++)
    {
      //cout << u->child[j]->nodeID << " ";

        printTree (u->child[j]);
        cout << endl;

    } // end print out all children

  } // end else, print all children

  cout << endl;

} // end printTree


// printBWT function
// print only the
// leaf nodes of the tree

void printBWT (aNode * u, string * s)
{
  int i = 0, j = 0, k = 0;

  i = u->child.size ();

    // if no children, it is a leaf node,
    // print the index and the corresponding
    // character in the original string

  if (i == 0)
  {
    // do nothing

  } // end just print edge label
  else
  {
    for (j = 0; j < i; j++)
    {

      if (u->child[j]->child.size() == 0)
      {
        k = (u->child[j]->nodeID) - 2;
        if (k < 0)
        {
          cout << (*s)[s->length () - 1] << endl;
        }
        else
        {
          cout << (*s)[k] << endl;
        }

      }

      if (u->child[j]->child.size () > 0)
      {
        printBWT (u->child[j], s);

      } // end if node has children, recursively print them

    } // end print out all children

} // end else, print all children

} // end printBWT


// getStats function
// iterate through the tree
// and gather statistical data

  // forward declaration:

void getStatsHelper (aNode *, int);

void getStats (aNode * u)
{
  getStatsHelper (u, 0);

  cout << "\n\nStatistics:\n" << endl;
  cout << "numInternalNodes: " << numInternalNodes << endl;
  cout << "numLeaves: " << numLeaves << endl;
  totalNodes += numInternalNodes + numLeaves;
  cout << "totalNodes: " << totalNodes << endl;
  cout << "tree size: " << sizeof (u) * totalNodes << endl;
  cout << "average string-depth of internal nodes: " << depthSum / float (numInternalNodes) << endl;
  cout << "string-depth of deepest internal node: " << deepest << endl;
  cout << "\n" << endl;

} // end getStats function

  // getStatsHelper function

void getStatsHelper (aNode * u, int ifFirst)
{
  int i = 0, j = 0;
  int theDepth;

    // handle root node:
    // ifFirst flag is used to only do this the
    // very first time the function is called,
    // and to not repeat it on the recursive calls

  if (u->edgeLabel[0] == -1 && ifFirst == 0)
  {
    numInternalNodes++;

  } // end if we are at root, print that


  i = u->child.size ();

    // if no children, do nothing

  //if (i == 0)
  //{
    // Do nothing

  //} // end no children, do nothing
  //else
  if (i > 0)
  {
    for (j = 0; j < i; j++)
    {
      //if (u->child[j]->nodeID < stringSize + 1)
      if (u->child[j]->nodeID <= theString.size ())
      {
        numLeaves++;
      } // end it is a leaf
      else
      {
        theDepth = u->child[j]->stringDepth;
        depthSum += theDepth;
        numInternalNodes++;

        if (theDepth > deepest)
        {
          deepest = theDepth;

        } // end update deepest
      } // end else it is internal

      if (u->child[j]->child.size () > 0)
      {
        getStatsHelper (u->child[j], 1);

      } // end if node has children, recursively print them

    } // end print out all children

  } // end else, print all children

} // end getStatsHelper

int main (int argc, char * argv[])
{
  string fileName;
  string dataName;
  string theAlphabet;
  aNode * root;

  cout << "\n\n\t\t\t*******************************************" << endl;
  cout << "\t\t\t************* Program Running *************" << endl;
  cout << "\t\t\t*******************************************" << endl;

    // If no input file was provided,
    // prompt user for one:

  if (argc == 1)
  {
    // prompt user for input file:
    cout << "Enter an input file name: " << endl;
    cin >> fileName;
    cout << "> " << fileName << endl;

  } // end if no argument provided, ask for a file name

  else if (argc == 2)
  {
    // prompt user for input file:
    cout << "Enter an alphabet file name: " << endl;
    cin >> theAlphabet;
    cout << "> " << theAlphabet << endl;

  } // end if no alphabet provided, prompt for one

  else
  {
    fileName = argv[1];
    theAlphabet = argv[2];

  } // end if there is an argument, assume it is the input file name

    // read the data from the file:

  readFile (fileName, &dataName, &theString);

    // append terminating symbol to string:

  theString += '$';
  stringSize = theString.length ();

    // create the tree and
    // return a pointer to the root node:

  root = buildSFTree ();

  // only print the tree if a flag is set:
  // -DFS will print the DFS tree,
  // -BWT will print the BWT tree

  if (argc == 4)
  {

    if (strcmp(argv[3], "-DFS") == 0)
    {
      int count = printDFS (root, 0, 0);
      cout << endl;
      //cout << "badInternals: " << badInternals << endl;

    } // end printDFS if flagged

    else if (strcmp(argv[3], "-BWT") == 0)
    {
      printBWT (root, &theString);
    } // end printBWT if flagged

    else if (strcmp(argv[3], "-POT") == 0)
    {
      int count = printPOT (root, 0);

    } // end printPOT if flagged
    else if (strcmp(argv[3], "-TREE") == 0)
    {
      printTree (root);
    } // end printTREE

  } // end if 4 args

  getStats (root);


} // end main function
