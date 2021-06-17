/* Author: Ngoc Duong
 * Date: 03/12/2019
 * This file contains API that defines the suffix tree data structure
 */
#ifndef ST_H
#define ST_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //lexicographical_compare

using namespace std;

extern int NEXT_ID;

struct node //internal node + leaf
{
	int id; //explanation below
	node* SL; //SL of an in_node is always an in_node
	node* parent;
	string p_edgelabel; //edgelabel comes from parent to itself
	int depth; //total length of all edgelabels from root
	vector<node*> children; //in lexicographic order of edge label
	int start_leaf_index;
	int end_leaf_index;

	node()
	{
		SL = NULL;
		parent = NULL;
		start_leaf_index = -1;
		end_leaf_index = -1;
	}

	/* id explanation:
	 * if there are total N nodes = n internal nodes + m leaves,
	 * id of each leaf will be in [0, m-1],
	 * id of each internal node will be in [m,N-1]
	 */
};

class ST
{
	public:
	node root;
	string input_string;

	/* constructor: contruct a ST tree from the inputs
	 * Input: an input string and alphabet
	 */
	ST(string s, vector<char> alphabet);

	/* method: display children of a node from left to right
	 * Input: a pointer to a node in the tree
	 */
	void display_children(node* u);

	/* method: enumerate all nodes in the tree using DFS traversal, display string depth of each node
	 * Input: a pointer to a parent node
	 */
	void DFS_tree(node* u);

	/* method: enumberate all nodes in the tree using post-order traversal, display string depth of each node
	 * Input: a pointer to a parent node
	 */
	void POT_tree(node* u);

	/* method: print the BWT index for the input string
	 * Input: none
	 * Return: BWT index list
	 */
	vector<int> display_BWT_index();

	/* method: display basic stats of the tree */
	void display_stats();

	/* method: display info of the longest exact matching repeat */
	void LMR();

	/* method: compute leaf list corresponding to each internal node and leaf whose string depth at least lambda */
	void prepareST(int lambda);
};

//////////////OTHER FUNCTIONS///////////////////////

/* This is a helper function for ST::prepareST() */
void DFS_PrepareST(node* proot, vector<int>* A,
					int* nextIndex, int lambda);

/* This function gets stats of a tree */
void get_stats(node* root, int* n_total_nodes, int* n_leaves, int* n_in_nodes, int* tree_size, float* ave_depth_in_node, int* max_depth_in_node);

/* This function builds a BWT_index
 * Inputs: 	u = the visiting node
 *			BWT_index = the BWT index vector that u may be added to
 *			BWT = the above but in int form (?)
 * 			s = the input string
 * Return: None
 */
void build_BWT_index(node *u, vector<char>* BWT_index, vector<int>* BWT, string s);

/* This is a helper fucntion to DFS_tree() */
void help_DFS_tree(node* u);

/* This is a helper function to POT_tree() */
void help_POT_tree(node* u);

/* This is a helper function to LMR() */
void help_LMR(node u, int* max, vector<int>* coordinates);

/* This function assigns the right id to a given internal node */
void assign_node_id(node* u);

/* This function creates a leaf with only id and depth
 * Inputs:	cur_suffix = the string we want to make the leaf for
 * 			suffix_index = index of the string in the original string
 * Return: a pointer to the leaf
 */
node* create_leaf(string cur_suffix, int suffix_index);

/* This function executes the case IB
 * Inputs:	u = parent of the leaf i-1
 *			cur_suffix = the string we want to insert
 *			index_suffix = index of cur_suffix in the original string
 * Return: parent node of the inserted leaf
 */
node* execute_IB(node* u, string cur_suffix, int index_suffix);

/* This function executes the case IIB
 * Inputs:	u = parent of the leaf i-1
 *			cur_suffix = the string we want to insert
 *			index_suffix = index of cur_suffix in the original string
 * Return: parent node of the inserted leaf
 */
node* execute_IIB(node* u, string cur_suffix, int index_suffix);

/* This function executes the case IIA
 * Inputs:	u = parent of the leaf i-1
 *			cur_suffix = the string we want to insert
 *			index_suffix = index of cur_suffix in the original string
 * Return: parent node of the inserted leaf
 */
node* execute_IIA(node* u, string cur_suffix, int index_suffix);

/* This function executes the case IA
 * Inputs:	u = parent of the leaf i-1
 *			cur_suffix = the string we want to insert
 *			index_suffix = index of cur_suffix in the original string
 * Return: parent node of the inserted leaf
 */
node* execute_IA(node* u, string cur_suffix, int index_suffix);

/* This function does node hopping child to child until the given string is exhausted
 * Inputs:  up = the node to hop from
 *			s = the string that will be hopped over
 * Return the end node (v) where s is exhausted.
 *		  If the end node does not exist, create and return it.
 *		  If the edge is not long enough to cover s, return NULL
 */
node* NodeHops(string s, node* up);

/* This function finds the path starting at the specified node argument that spells out the longest possible prefix of the specified string argument, and then insert the next suffix
 * Inputs:	u = the node to start finding path
 *			s = the string to append to u
 *			suf_i = intended id if the leaf
 * Return: parent node of the inserted leaf
 * Post-condition: the string is appended to the node by following ST rules
 */
node* FindPath(node* u, string s, int suf_i);

/*
*   This is a helper function for FindLoc,
*   It finds the path along an edge that maches ri
*   and returns a pointer to the last-visited-node, u,
*   and the number of characters travelled down a path, r
*   inputs:   node * T is a pointer to a start node
*             string ri is the 'read'
*             int read_ptr is the index in ri we are currently pointing to
*             node * u is  a pointer to a node we can ...
*             int * r is the number of characters we have travelled down an edge
*/

node* miniFindPath (node * T, string ri, int read_ptr, int * r);

/* This function finds the path starting at the specified
 *    node argument that spells out the longest possible
 *    prefix of the specified string argument,
 *    and then insert the next suffix
 * Inputs:	u = the node to start finding path
 *			ri = the read, r_i, that is being evaluated
 *      xi = the minimum length of path we are looking for
 *      deepestSoFar = pointer to the deepest
 *        node we've encountered so far,
 *        if our current node is deeper than that,
 *        set it to be the deepestNode
 *      Li = pointer to a vector of candidate leaf indexes
 * Return:
 * Post-condition: candidate list of genomic positions L_i is updated
 */

vector<int> FindLoc (node * T, string ri, int xi, vector <int> * A);

/* This function inserts a child to a parent's children in lexicographic order
 * Inputs:	u = parent node
 *			child = the child node of u
 * Return: none
 */
void insert_child(node* u, node* child);

/* This function finds a branch from a given node that starts with a given char
 * Inputs: 	u = the node to search for the branch
 *			c = the character that the branch starts at
 * Return index of the branch in u's children
 * If the branch does not exist, return -1
 */
int find_branch(node *u, char c);

/* This function breaks down an edge to insert a node
 * Inputs: 	u = the node that has the edge to break
 *			e = index of the branch in the u's children
 *			break_ind = index on the edge after which the edge will be broken
 * Return: pointer to the new node
 */
node* insert_middle(node* u, int e, int break_ind);

/* This function displays a ST */
void display_tree(ST tree);

/* This is a helper funtion to display_tree() */
void help_display_tree(node* u);




vector<int> my_find_loc(node * T, string ri, vector<int>* A, int xi);
node* my_find_path(node* T, string s, int* cur_len);
#endif
