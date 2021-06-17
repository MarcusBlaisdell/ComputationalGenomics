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


  // findPath function:
  // accepts:
  //          pointer to a start node,
  //          starting index,
  //          string length,
  //          distance travelled so far
  // Once it find a location,
  // it stores the current node as the global u,
  // and the distance along that edge as edgePos
  // and returns distance travelled so far
  // so that can be truncated from the string
  // for insertNode

int findPath (aNode * parent, int startIndex, int stringLength,
              int distSoFar)
{
  #ifdef DEBUG
  cout << "~ ~ ~ findPath: parent->nodeID: " << parent->nodeID << endl;
  cout << "~ ~ ~ findPath: startIndex: " << startIndex << endl;
  cout << "~ ~ ~ findPath: stringLength: " << stringLength << endl;
  cout << "~ ~ ~ findPath: distSoFar: " << distSoFar << endl;
  #endif

  // recursive base case:
  // if stringLength is zero,
  // then this node we are at now, is an exact
  // pathLabel match to the string,

  if (stringLength == 0)
  {
    u = parent;
    edgePos = startIndex;

    return distSoFar;
  } // end if we found a child node

  // test if '$', if so, return all current info:
  if (theData[startIndex] == '$')
  {
    u = parent;
    edgePos = 0;
    return distSoFar;
  } // end return on terminal character

  // i is an index for our position
  // in the children list
  // j is the distance we have travelled so far
  // on an edge
  // k is the size of an edgeLabel


  int i = 0, j = 0, k = 0;

    // found is a flag to indicate if a child was found
    // that begins with the first character of the string
    // we are searching

  int found = 0;

  // create an iterator to iterate through child list:

  vector <aNode *>::iterator it = parent->child.begin();

    // Look for a child node that begins
    // with the first character of our suffix:

    while (it != parent->child.end() )
    {
      if (theData[parent->child[i]->edgeLabel[0]] == theData[startIndex])
      {
        // once we find the child, set the found flag
        // and, break out of while
        found = 1;
        childNum = i;
        break;
      } // endl;

      it++;
      i++;

    } // end while not in right position

      // if we found a path among the children,
      // follow it as far as we can:

    if (found == 1)
    {
      // k = size of edgeLabel

      k = parent->child[i]->edgeLabel[1];

      for (j = 0; j < k; j++)
      {
        // Two checks:
        // One, if the string length has been exhausted,
        // Two, if we have found a mismatch
        #ifdef DEBUG
        cout << "node " << parent->child[i]->edgeLabel[0] + j;
        cout << " : " << theData[parent->child[i]->edgeLabel[0] + j];
        cout << " - string " << startIndex + j;
        cout << ": " << theData[startIndex + j] << endl;
        #endif

        if ((theData[parent->child[i]->edgeLabel[0] + j]
            != theData[startIndex + j]) || ((stringLength - j) == 0))
        {
          u = parent->child[i];
          edgePos = j;
          int newDistSoFar = distSoFar + j;

          #ifdef DEBUG
          cout << "distSoFar: " << distSoFar;
          cout << " - j: " << j << endl;
          cout << "newDistSoFar: " << newDistSoFar << endl;
          #endif

          return newDistSoFar;

        } // end if a mismatch is found or stringLength is exhausted


      } // end for loop

      // If we get out of the for loop,
      // the edgeLabel is exhausted but the string is not
      // and we've matched all characters in the edgeLabel
      // recursively call findPath:


      startIndex += j;
      stringLength -= j;
      distSoFar += j;

      int trunc = 0;
      trunc = findPath (parent->child[i], startIndex, stringLength, distSoFar);

      distSoFar += trunc - 1;

    } // end if we found a path
    else
    {
      edgePos = 0;
      return 0;
    } // end no path was found, add new child

    #ifdef DEBUG
    cout << "the last distSoFar: " << distSoFar << endl;
    cout << "u->nodeID: " << u->nodeID << endl;
    #endif

  return distSoFar;

} // end findPath function

// forward declaration:
void insertNode (aNode * , int, int, int);

  // NodeHops function:

/*
void NodeHops (int beta[2], aNode * u_prime, int startIndex,
                int stringLength, string * theData)
*/
void NodeHops (int beta[2], aNode * u_prime, int startIndex,
                int stringLength)
{
  int trunc = 0;

  if (theData[startIndex] == '$')
  {
    insertNode (u, 0, startIndex, stringLength);
    return;

  } // end if terminal character, just add it and quit

  int i = 0, j = 0;

  #ifdef DEBUG
  cout << "\t\t\tNodeHops was called" << endl;
  cout << "beta[0]: " << beta[0] << endl;
  #endif

    // take SL(u') to v':
    // generalized, will work for case IIA, and IIB:

  u = u_prime->SL;

    // using a suffix link allows us to skip some characters:

  //startIndex += u->stringDepth;
  //stringLength -= u->stringDepth;


    // take correct path out of v':

  i = u->child.size ();

  #ifdef DEBUG
    // print the child list for debugging

  for (j = 0; j < i; j++)
  {
    cout << "\t\t\t\tu->child[j]->: " << u->child[j]->nodeID << endl;
  }

  cout << "theData[beta[0]]: " << theData[beta[0]] << endl;
  #endif

  for (j = 0; j < i; j++)
  {
    #ifdef DEBUG
    cout << "theData[u->child[j]->edgeLabel[0]]: " << theData[u->child[j]->edgeLabel[0]] << endl;
    #endif

    if (theData[u->child[j]->edgeLabel[0]] == theData[beta[0]])
    {
      childNum = j;
      #ifdef DEBUG
      cout << "j: " << j << endl;
      #endif
        // once we find the right path, check it's length,
        // if it is greater than beta, then v doesn't exist,
        // we will use findPath and add V
        //
        // if it is less than beta, we don't know if it
        // exists or not but we can safely hop to the child
        // and re-evaluate once we get there
        //
        // if child edgeLabel is equal to beta, then
        // v exists and we can safely hop to the child

      if (beta[1] == u->child[j]->edgeLabel[1] )
      {
        u = u->child[j];
        SLHolder->SL = u;
        startIndex += u->stringDepth;
        stringLength -= u->stringDepth;
        trunc = findPath (u, startIndex, stringLength, 0);
        insertNode (u, edgePos, startIndex + trunc, stringLength - trunc);

        return;

      } // end if edgeLabel matches beta

      else if (beta[1] > u->child[j]->edgeLabel[1] )
      {
        while (beta[1] > u->child[j]->edgeLabel[1])
        {
          beta[0] += u->child[j]->edgeLabel[1];
          beta[1] -= u->child[j]->edgeLabel[1];
          //startIndex += u->child[j]->edgeLabel[1];
          //stringLength -= u->child[j]->edgeLabel[1];

          u = u->child[j];

          // find the next correct child:
          for (j = 0; j < u->child.size (); j++)
          {
            if (theData[u->child[j]->edgeLabel[0]] == theData[beta[0]])
            {
              break;
            } // end if we found the right child

          } // end for loop to find the right child

        } // end hop until edge length is not less than beta length

        startIndex += u->stringDepth;
        stringLength += u->stringDepth;

        trunc = findPath (u, startIndex, stringLength, 0);
        insertNode (u, edgePos, startIndex + trunc, stringLength - trunc);

        /*
          // re-evaluate if the next node is our endpoint

        if (beta[1] == u->child[j]->edgeLabel[1] )
        {
          u = u->child[j];
          SLHolder->SL = u;

          return;

        } // end if edgeLabel matches beta

        else
        {
          int trunc;

          trunc = findPath (u, startIndex, stringLength, 0);
          insertNode (u, edgePos, startIndex + trunc, stringLength - trunc);

          SLHolder->SL = u;

          return;

        } // end if beta greater than edgeLabel
        */

      } // end beta greater than edgeLabel size
      // else, edgeLabel is greater than Beta so
      // v doesn't exist

      else
      {
        startIndex += u->stringDepth;
        stringLength -= u->stringDepth;

        trunc = findPath (u, startIndex, stringLength, 0);
        insertNode (u, edgePos, startIndex + trunc, stringLength - trunc);

        SLHolder = u;

        return;

      } // end else, edgeLabel > beta

    } // end find correct child


  } // end iterate through all children

} // end NodeHops function


int printDFS (aNode *, int, int);
int printPOT (aNode *, int);

  // insertNode function

void insertNode (aNode * theNode, int insPos, int startIndex, int stringLength)
{
  int i = 0, j = 0, k = 0;
  // Two conditions, insert within an edgeLabel,
  // or, insert-in-order as a child of a node

  #ifdef DEBUG
  cout << "create as new child of " << u->nodeID << endl;
  cout << "theNode->nodeID: " << theNode->nodeID << endl;
  #endif

  if (insPos > 0)
  {
    #ifdef DEBUG
    cout << "\t\t\tinsPos > 0" << endl;
    #endif

    // insert within an edge:

    // create new internal node and new leaf node:
    aNode * newInternalNode = new aNode;
    aNode * newLeafNode = new aNode;

      // set the variables for the new internal node:

    newInternalNode->nodeID = internalID++;
    newInternalNode->parent = theNode->parent;
    newInternalNode->edgeLabel[0] = theNode->edgeLabel[0];
    newInternalNode->edgeLabel[1] = insPos;
    newInternalNode->stringDepth = theNode->parent->stringDepth + insPos;

      // If this is an internal node with a string depth of 1,
      // it's suffix link must point to the root:

    if (newInternalNode->stringDepth <= 1)
    {
      newInternalNode->SL = newInternalNode->parent;
    } // end point to root if size == 1

      // set the parents, child pointer to point
      // to the new internal node:
    #ifdef DEBUG
    cout << "childNum: " << childNum << endl;
    cout << "theNode->parent->child[childNum]->nodeID: " << theNode->parent->child[childNum]->nodeID << endl;
    #endif
    theNode->parent->child[childNum] = newInternalNode;
    #ifdef DEBUG
    cout << "theNode->parent->child[childNum]->nodeID: " << theNode->parent->child[childNum]->nodeID << endl;
    #endif

      // set the variables for the new leaf node:

    newLeafNode->nodeID = leafID++;
    newLeafNode->parent = newInternalNode;
    newLeafNode->edgeLabel[0] = startIndex;
    newLeafNode->edgeLabel[1] = stringLength;
    newLeafNode->stringDepth = newInternalNode->stringDepth + stringLength;

      // adjust the data for the node we just
      // inserted above:

    theNode->parent = newInternalNode;
    theNode->edgeLabel[0] += insPos;
    theNode->edgeLabel[1] -= insPos;

      // insert-in-order the newLeafNode and original Node
      // as children of the newInternalNode:

    #ifdef DEBUG
    cout << "= = = theData[newLeafNode->edgeLabel[0]]: ";
    cout << newLeafNode->edgeLabel[0] << " : ";
    cout << theData[newLeafNode->edgeLabel[0]] << endl;
    cout << "= = = theData[theNode->edgeLabel[0]]: ";
    cout << theNode->edgeLabel[0] << " : ";
    cout << theData[theNode->edgeLabel[0]] << endl;
    #endif

    if ((theData[newLeafNode->edgeLabel[0]] == '$')
        || (theData[newLeafNode->edgeLabel[0]]
          <= theData[theNode->edgeLabel[0]]) )
    {
      newInternalNode->child.push_back (newLeafNode);
      newInternalNode->child.push_back (theNode);
    } // end if newLeafNode edgeLabel is lexicographically lower
    else
    {
      newInternalNode->child.push_back (theNode);
      newInternalNode->child.push_back (newLeafNode);

    } // end newLeafNode edgeLabel is lexicographically lower

      // set our current pointer to our new leaf node

    u = newLeafNode;

  } // end insert within an edge
  else
  {
    #ifdef DEBUG
    cout << "\t\t\tinsPos = 0" << endl;
    #endif

    // create new leaf node:
    aNode * newLeafNode = new aNode;

    // set the variables:

    newLeafNode->nodeID = leafID++;
    newLeafNode->parent = theNode;
    newLeafNode->edgeLabel[0] = startIndex;
    newLeafNode->edgeLabel[1] = stringLength;
    newLeafNode->stringDepth = theNode->stringDepth + stringLength;

    u = newLeafNode;

      // create an iterator to search through the children:

    vector <aNode *>::iterator it = theNode->child.begin();

      // If it is the terminating character,
      // add in front

    if (theData[startIndex] == '$')
    {
      theNode->child.insert (it, newLeafNode);
    } // end if $, insert at front
    else
    {
      while (it != theNode->child.end() )
      {
        if (theData[theNode->child[i]->edgeLabel[0]] > theData[startIndex])
        {
          theNode->child.insert (it, newLeafNode);
          #ifdef DEBUG
          cout << "\t\t\t\t% % % insertNode - nodeID: " << u->nodeID << endl;
          cout << "\t\t\t\t% % % insertNode - parent: " << u->parent->nodeID << endl;
          #endif

          i = u->parent->child.size();

          #ifdef DEBUG
          for (j = 0; j < i; j++)
          {
            cout << "\t\t\tu->parent->child[" << j;
            cout << "]: " << u->parent->child[j]->nodeID;
            cout << " : " << theData[u->parent->child[j]->edgeLabel[0]] << endl;
          }
          #endif

          return;
          //break;

        } // end insert within the child list
        it++;
        i++;

      } // end iterate through children list

      // if we get here, we are lexicographically larger
      // than everything in the list, so, insert at end

      theNode->child.push_back (newLeafNode);

    } // end else, insert in order

  } // end insert-in-order as new child

  #ifdef DEBUG
  cout << "\t\t\t\t% % % insertNode - nodeID: " << u->nodeID << endl;
  cout << "\t\t\t\t% % % insertNode - parent: " << u->parent->nodeID << endl;
  #endif

  i = u->parent->child.size();

  #ifdef DEBUG
  for (j = 0; j < i; j++)
  {
    cout << "\t\t\tu->parent->child[" << j;
    cout << "]: " << u->parent->child[j]->nodeID;
    cout << " : " << theData[u->parent->child[j]->edgeLabel[0]] << endl;
  }
  #endif


} // end insertNode function


// build a suffix tree:

aNode * buildSFTree (string *theData)
{
    // create a timer:
    auto startTime = steady_clock::now ();

    // create an integer to track the position in
    // the string and one to track the remaining
    // length of the string

  int index = 0, remLen = theData->length ();
  int newIndex = 0, newRemLen = 0;
  int trunc = 0;
  // beta, beta_prime has a start index and length:
  int beta[2];
  int beta_prime[2];


    // get the length of string:
    // lowercase n will be the size of the string,
    // uppercase N will be the number of nodes,
    // N = internal nodes + leaf nodes

  int n = theData->length();

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

    // int nodeID;
    // struct node * SL;
    // struct node * parent;
    // string edgeLabel;
    // vector <struct node * > child;
    // int stringDepth;

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

  u = root;


    // create the tree
    // using a while loop that advances the
    // first character index and shortens
    // the string length on
    // each iteration until we reach the end

    // use a variable, trunc, to record how much of our string
    // to truncate as a result of findPath

  //int trunc = 0;

  while (remLen > 0)
  {
    // After we insert a node, our node pointer is
    // pointing to the last inserted leaf node
    // move to its parent, u, to begin our evaluation:
    #ifdef DEBUG
    cout << "inWhile: u->nodeID: " << u->nodeID << endl;
    cout << "inWhile: u->parent->nodeID: " << u->parent->nodeID << endl;
    cout << "inWhile: u->parent->parent->nodeID: " << u->parent->parent->nodeID << endl;
    cout << "inWhile: u->child.size(): " << u->child.size () << endl << endl;
    #endif

    // test without Suffix links:
    // move to the root to begin insertion from beginning:
    //while (u->edgeLabel[0] != -1)
    //{
      //u = u->parent;
    //}
    //int trunc = 0;
    //trunc = findPath (u, index, remLen, 0);
    //cout << "index: " << index << endl;
    //cout << "trunc: " << trunc << endl;
    //insertNode (u, edgePos, index + trunc, remLen - trunc);

    u = u->parent;

    // There are four possibilities and each need
    // to be handled separately,
    // test to find out which situation we are in:

    if (u->SL != NULL)
    {
      if (u->edgeLabel[0] == -1 )
      {
        #ifdef DEBUG
        cout << "\t\t*** IB ***" << endl;
        #endif
        // case IB
        // SL(u) is known, and u is the root:
        // we need only find the path and insert the Node:

        trunc = findPath (u, index, remLen, 0);
        insertNode (u, edgePos, index + trunc, remLen - trunc);

      } // end if u is root
      else
      {
        #ifdef DEBUG
        cout << "\t\t*** IA ***" << endl;
        #endif
        // case IA
        // SL(u) is known, and u is not the root:
        // take SL(u) to v,
        // adjust our indexes to take advantage
        // of the SL savings, then call findPath and insertNode:

          // I am using u as a universal, current node pointer
          // but in this case, u is v:

        u = u->SL;

          // advance index by the path size of v:

        newIndex = index + u->stringDepth;
        newRemLen = remLen - u->stringDepth;

        trunc = findPath (u, newIndex, newRemLen, 0);
        insertNode (u, edgePos, newIndex + trunc, newRemLen - trunc);

      } // end else, IA

    } // end if Suffix Link is known
    else
    {
      if (u->parent->edgeLabel[0] == -1)
      {
        #ifdef DEBUG
        cout << "\t\t*** IIB ***" << endl;
        #endif
        // case IIB
        // SL(u) is not known, and u' is the root:

        beta_prime[0] = u->edgeLabel[0] + 1;
        beta_prime[1] = u->edgeLabel[1] - 1;
        //beta_prime[0] = u->edgeLabel[0];
        //beta_prime[1] = u->edgeLabel[1];

        // store a pointer to our current node,
        // we will use this to update the suffix link
        // when we find v:

        SLHolder = u;

        // move to u', which is the root node:

        u = u->parent;

        //NodeHops (beta_prime, u, index, remLen, theData);
        #ifdef DEBUG
        cout << "calling NodeHops with beta_prime: ";
        cout << beta_prime[0] << ", " << beta_prime[1];
        cout << endl;
        #endif
        NodeHops (beta_prime, u, index, remLen);

      } // end u' is the root
      else
      {
        #ifdef DEBUG
        cout << "\t\t*** Case IIA ***" << endl;
        #endif
        // case IIA
        // SL(u) is not known, u' is not the root

        beta[0] = u->edgeLabel[0];
        beta[1] = u->edgeLabel[1];

        // store a pointer to our current node,
        // we will use this to update the suffix link
        // when we find v:

        SLHolder = u;

        // move to u', which is not the root node:

        u = u->parent;

        //NodeHops (beta, u, index, remLen, theData);
        NodeHops (beta, u, index, remLen);

      } // end u' is not the root

    } // end Suffix Link is not known

    #ifdef DEBUG
    cout << "index: " << index << endl;
    #endif

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
      //cout << u->child[j]->nodeID << " : " << u->child[j]->edgeLabel << endl;
      //cout << u->child[j]->nodeID << " : " << u->child[j]->stringDepth << endl;
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

    // if no children, just print the edge label

  if (i == 0)
  {
    // Do nothing

  } // end just print edge label
  else
  {
    for (j = 0; j < i; j++)
    {
      if (u->child[j]->nodeID < stringSize + 1)
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
  //string theData;
  string dataCopy;
  string theAlphabet;
  aNode * root;

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

  readFile (fileName, &dataName, &theData);

    // append terminating symbol to string:

  theData += '$';
  dataCopy = theData;
  stringSize = theData.length ();

    // create the tree and
    // return a pointer to the root node:

  root = buildSFTree (&theData);

  // only print the tree if a flag is set:
  // -DFS will print the DFS tree,
  // -BWT will print the BWT tree

  if (argc == 4)
  {

    if (strcmp(argv[3], "-DFS") == 0)
    {
      int count = printDFS (root, 0, 0);
      cout << endl;

    } // end printDFS if flagged

    else if (strcmp(argv[3], "-BWT") == 0)
    {
      printBWT (root, &dataCopy);
    } // end printBWT if flagged

    else if (strcmp(argv[3], "-POT") == 0)
    {
      int count = printPOT (root, 0);

    } // end printPOT if flagged

  } // end if 4 args

  getStats (root);


} // end main function
