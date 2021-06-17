/* Author: Ngoc Duong
 * Date: 03/12/2019
 * This program defines all methods of ST class and other relevant functions
 */

#include "ST1.h"

int NEXT_ID;

/* constructor: contruct a ST tree from the inputs
* Input: an input string and alphabet
*/
ST::ST(string s, vector<char> alphabet)
{
	input_string = s;
	s.push_back('$'); //append '$' at the end of the string
	int n_leaves = s.length(); //number leaves
	NEXT_ID = n_leaves; //init value

	//initialize the root
	assign_node_id(&root);
	root.SL = &root; //SL(root) is root
	root.parent = &root; //parent of root is root
	root.p_edgelabel = "";
	root.depth = 0;

	int suffix_index = 0;
	string cur_suffix = s;
	node* u = NULL; //suffix leaf i-1 parent
	node* up = NULL; //parent of u

	//append the first suffix to the root (suffix_index = 0)
	node* new_leaf = create_leaf(cur_suffix, suffix_index);
	new_leaf->p_edgelabel = s;
	new_leaf->parent = &root;
	root.children.push_back(new_leaf);

	u = &root;
	up = u->parent;
	//append the rest of suffixes to the root
	for (suffix_index = 1; suffix_index < s.length(); suffix_index++)
	{
		cur_suffix = s.substr(suffix_index);

		//classify to one of 4 cases
		if (u->SL != NULL && u != &root) //case IA
		{
			u = execute_IA(u, cur_suffix, suffix_index);
		}
		else if (u->SL != NULL && u == &root) //case IB
		{
			u = execute_IB(u, cur_suffix, suffix_index);
		}
		else if (u->SL == NULL && up != &root) //case IIA
		{
			u = execute_IIA(u, cur_suffix, suffix_index);
		}
		else if (u->SL == NULL && up == &root) //case IIB
		{
			u = execute_IIB(u, cur_suffix, suffix_index);
		}
		else
		{
			cout << "undefined case, error" << endl;
		}
		up = u->parent;
	}
}

/* method: display children of a node from left to right
 * Input: a pointer to a node in the tree
 */
void ST::display_children(node* u)
{
	cout << "Children of node id=" << u->id << " from left to right" << endl;
	vector<node*>::iterator it;
	for(it = (u->children).begin(); it < (u->children).end(); it++)
	{
		cout << (*it)->id << "   ";
	}
	cout << endl;
}

/* method: enumerate all nodes in the tree using DFS traversal, display string depth of each node
 * Input: a pointer to a parent node
 */
void ST::DFS_tree(node* u)
{
	cout << "DFS the tree and display string depth of each node" << endl;
	help_DFS_tree(u);
	cout << endl;
}

/* method: enumerate all nodes in the tree using post-order traversal, display string depth of each node
 * Input: a pointer to a parent node
 */
void ST::POT_tree(node* u)
{
	cout << "Post-order traversing the tree and display string depth of each node" << endl;
	help_POT_tree(u);
	cout << endl;
}

/* method: print the BWT index for the input string
 * Input: none
 */
void ST::display_BWT_index()
{
	//build BWT index
	vector<char> BWT_index;
	build_BWT_index(&root, &BWT_index, input_string);

	//display the BWT_index
	cout << "Display the BWT index for the input string" << endl;
	vector<char>::iterator it;
	for (it = BWT_index.begin(); it < BWT_index.end(); it++)
	{
		cout << *it << endl;
	}
}

/* method: display basic stats of the tree */
void ST::display_stats()
{
	int n_total_nodes = 0;
	int n_leaves = 0;
	int n_in_nodes = 0;
	int tree_size = 0;
	float ave_depth_in_node = 0.0;
	int max_depth_in_node = 0;

	get_stats(&root, &n_total_nodes, &n_leaves, &n_in_nodes, &tree_size, &ave_depth_in_node, &max_depth_in_node);

	ave_depth_in_node /= n_in_nodes;

	cout << "------STATS----------" << endl << endl;
	cout << "Total number of nodes: " << n_total_nodes << endl;
	cout << "Number of internal nodes: " << n_in_nodes << endl;
	cout << "Number of leaves: " << n_leaves << endl;
	cout << "Size of the tree <bytes>: " << tree_size << endl;
	cout << "Average string depth of an internal node: " << ave_depth_in_node << endl;
	cout << "String depth of the deepest internal node: " << max_depth_in_node << endl;
}

/* method: find the longest exact matching repeat */
void ST::LMR()
{
	int max_length = 0;
	vector<int> coordinates;

	help_LMR(root, &max_length, &coordinates);
	cout << "Longest exact matching repeat:" << endl;
	cout << "\tLength = " << max_length << endl;
	cout << "\tStarting positions: ";
	vector<int>::iterator it;
	for (it = coordinates.begin(); it < coordinates.end(); it++)
	{
		cout << *it << "\t";
	}
	cout << endl;
}

/* method: compute leaf list corresponding to each internal node and leaf whose string depth at least lambda */
void ST::prepareST(int lambda)
{
	//create an array of size |s| + 1
	vector<int> A(input_string.length() + 1,-1);
	int nextIndex = 0;
	vector<int>::iterator it;
	DFS_PrepareST(&root, &A, &nextIndex, lambda);
	for (it = A.begin(); it < A.end(); it++)
	{
		cout << *it << "\t";
	}
	cout << endl;
}

//////////////OTHERS FUNCTIONS///////////////////////

/* This is a helper function for ST::prepareST() */
void DFS_PrepareST(node* proot, vector<int>* A,
					int* nextIndex, int lambda)
{
	if (proot == NULL)
	{
		return;
	}

	node* u_left = NULL;
	node* u_right = NULL;
	//compute leaf list of the tree
	vector<node*>::iterator it;
	if (proot->children.size() == 0) //leaf
	{
		(*A)[*nextIndex] = proot->id;
		if(proot->depth >= lambda)
		{
			proot->start_leaf_index = *nextIndex;
			proot->end_leaf_index = *nextIndex;
		}
		(*nextIndex)++;
		return;
	}
	else //internal node
	{
		for (it = (proot->children).begin(); it < (proot->children).end(); it++)
		{
			DFS_PrepareST(*it, A, nextIndex, lambda);
		}
	}

	//set the leaf interval for the tree
	if (proot->depth >= lambda)
	{
		u_left = proot->children[0];
		u_right = proot->children.back();
		proot->start_leaf_index = u_left->start_leaf_index;
		proot->end_leaf_index = u_right->end_leaf_index;
	}
}

/* This function gets stats of a tree */
void get_stats(node* root, int* n_total_nodes, int* n_leaves, int* n_in_nodes, int* tree_size, float* ave_depth_in_node, int* max_depth_in_node)
{
	(*n_total_nodes)++;
	if (root->children.size() == 0) //leaf
	{
		(*n_leaves)++;
	}
	else //internal node
	{
		(*n_in_nodes)++;
		(*ave_depth_in_node) += root->depth;
		if ((*max_depth_in_node) < root->depth)
		{
			(*max_depth_in_node) = root->depth;
		}
	}
	(*tree_size) += sizeof(*root);
	vector<node*>::iterator it;
	for (it = (root->children).begin(); it < (root->children).end(); it++)
	{
		get_stats(*it, n_total_nodes, n_leaves, n_in_nodes,  tree_size, ave_depth_in_node, max_depth_in_node);
	}
}

/* This function builds a BWT_index
 * Inputs: 	u = the visiting node
 *			BWT = the BWT index vector that u may be added to
 * 			s = the input string
 * Return: None
 */
void build_BWT_index(node *u, vector<char>* BWT, string s)
{
	if (u->children.size() == 0)//u if a leaf
	{
		if (u->id == 0)
		{
			BWT->push_back('$');
		}
		else
		{
			BWT->push_back(s[u->id-1]);
			}
	}
	vector<node*>::iterator it;
	for (it = (u->children).begin(); it < (u->children).end(); it++)
	{
		build_BWT_index(*it, BWT, s);
	}
}

/* This is a helper funtion to DFS_tree() */
void help_DFS_tree(node* u)
{
	if (u == NULL)
	{
		return;
	}
	cout <<  u->depth << endl;
	vector<node*>::iterator it;
	for (it = (u->children).begin(); it < (u->children).end(); it++)
	{
		help_DFS_tree(*it);
	}
}

/* This is a helper function to POT_tree() */
void help_POT_tree(node *u)
{
	if (u == NULL)
	{
		return;
	}
	vector<node*>::iterator it;
	for (it = (u->children).begin(); it < (u->children).end(); it++)
	{
		help_POT_tree(*it);
	}
	cout << u->depth << endl;
}

/* This is a helper function for LMR() */
void help_LMR(node u, int* max, vector<int>* coordinates)
{
	node up = *(u.parent);
	if (up.depth > *max)
	{
		*max = up.depth;
		coordinates->clear();
		coordinates->push_back(u.id + 1);
	}
	else if (up.depth == *max)
	{
		coordinates->push_back(u.id + 1);
	}
	vector<node*>::iterator it;
	for (it = (u.children).begin(); it < (u.children).end(); it++)
	{
		help_LMR(**it, max, coordinates);
	}
}

/* This function assigns the right id to a given internal node */
void assign_node_id(node* u)
{
	u->id = NEXT_ID;
	NEXT_ID++;
}

/* This function creates a leaf with only id and depth
 * Inputs:	cur_suffix = the string we want to make the leaf for
 * 			suffix_index = index of the string in the original string
 * Return: a pointer to the leaf
 */
node* create_leaf(string cur_suffix, int suffix_index)
{
	node* new_leaf = new node;
	new_leaf->id = suffix_index;
	new_leaf->depth = cur_suffix.length();
	return new_leaf;
}

/* This function executes the case IB
 * Inputs:	u = parent of the leaf i-1
 *			cur_suffix = the string we want to insert
 *			index_suffix = index of cur_suffix in the original string
 * Return: parent node of the inserted leaf
 */
node* execute_IB(node* u, string cur_suffix, int index_suffix)
{
	node* v = u->SL;
	return FindPath(v, cur_suffix, index_suffix);
}

/* This function executes the case IIB
 * Inputs:	u = parent of the leaf i-1
 *			cur_suffix = the string we want to insert
 *			index_suffix = index of cur_suffix in the original string
 * Return: parent node of the inserted leaf
 */
node* execute_IIB(node* u, string cur_suffix, int index_suffix)
{
	node* up = u->parent;
	node* vp = up->SL;
	string betap = u->p_edgelabel.substr(1);
	node* v = NodeHops(betap, up);
	if (v == NULL)
	{
		return FindPath(up, cur_suffix, index_suffix);
	}
	else
	{
		u->SL = v;
		return FindPath(v, cur_suffix.substr(betap.length()), index_suffix);
	}
}

/* This function executes the case IIA
 * Inputs:	u = parent of the leaf i-1
 *			cur_suffix = the string we want to insert
 *			index_suffix = index of cur_suffix in the original string
 * Return: parent node of the inserted leaf
 */
node* execute_IIA(node* u, string cur_suffix, int index_suffix)
{
	node* up = u->parent;
	node* vp = up->SL;
	string beta = u->p_edgelabel;
	node* v = NodeHops(beta, vp);

	if (v == NULL)
	{
		return FindPath(vp, cur_suffix.substr(vp->depth), index_suffix);
	}
	else
	{
		u->SL = v;
		return FindPath(v, cur_suffix.substr(v->depth), index_suffix);
	}
}

/* This function executes the case IA
 * Inputs:	u = parent of the leaf i-1
 *			cur_suffix = the string we want to insert
 *			index_suffix = index of cur_suffix in the original string
 * Return: parent node of the inserted leaf
 */
node* execute_IA(node* u, string cur_suffix, int index_suffix)
{
	node* v = u->SL;
	return FindPath(v, cur_suffix.substr(v->depth), index_suffix);
}

/* This function does node hopping child to child until the given string is exhausted
 * Inputs:  up = the node to hop from
 *			s = the string that will be hopped over
 * Return the end node (v) where s is exhausted.
 *		  If the end node does not exist, create and return it.
 *		  If the edge is not long enough to cover s, return NULL
 */
node* NodeHops(string s, node* up)
{
	if (s.length() == 0)
	{
		return up;
	}

	int e = find_branch(up, s[0]);
	string cur_edgelabel = up->children[e]->p_edgelabel;

	if (e == -1) //the branch does not exist
	{
		return NULL;
	}

	//at this point, the branch may or may not exist
	if (s.length() < cur_edgelabel.length())
	{
		if (cur_edgelabel.substr(0,s.length()) == s) //create v
		{
			return insert_middle(up, e, s.length()-1);
		}
		else
		{
			return NULL;
		}
	}

	else if (s.length() > cur_edgelabel.length())
	{
		if (s.substr(0,cur_edgelabel.length()) == cur_edgelabel) //hop
		{
			return NodeHops(s.substr(cur_edgelabel.length()), up->children[e]);
		}
		else
		{
			return NULL;
		}
	}

	else //same length
	{
		if (cur_edgelabel == s) //found v
		{
			return up->children[e];
		}
		else
		{
			return NULL;
		}
	}
}

/* This function finds the path starting at the specified node argument that spells out the longest possible prefix of the specified string argument, and then insert the next suffix
 * Inputs:	u = the node to start finding path
 *			s = the string to append to u
 *			suf_i = intended id if the leaf
 * Return: parent node of the inserted leaf
 * Post-condition: the string is appended to the node by following ST rules
 */
node* FindPath(node* u, string s, int suf_i)
{
	node* new_leaf = NULL;
	node* temp = NULL;
	int i = 0;
	int m = 0;
	string cur_edgelabel = "";

	//pick the branch e of u that starts with s[0]
	int e = find_branch(u, s[0]); //index of the branch e in the parent's children

	if (e == -1) //no branch found => make a new branch from u to append s
	{
		new_leaf = new node;
		new_leaf->id = suf_i;
		new_leaf->parent = u;
		new_leaf->p_edgelabel = s;
		new_leaf->depth = u->depth + s.length();
		insert_child(u, new_leaf);
		return u;
	}
	else //if the branch e exists, move down into the branch
	{
		cur_edgelabel = u->children[e]->p_edgelabel;
		i = 0;
		m = cur_edgelabel.length();
		if (s.length() < m)
		{
			m = s.length();
		}

		while (i < m)
		{
				if (cur_edgelabel[i] != s[i])
				{
					break;
				}
				i++;
		}
		//at this point, i can be either (1) index of the first different char pair or (2) length of the shorter string

		//case (1) => break the cur_edge right before i,
		//insert a new node to the branch,
		//insert a new edge from the new node for the rest of s
		if (i < m)
		{
			temp = insert_middle(u, e, i-1);
			new_leaf = new node;
			new_leaf->id = suf_i;
			new_leaf->parent = temp;
			new_leaf->p_edgelabel = s.substr(i);
			new_leaf->depth = u->depth + s.length();
			insert_child(temp, new_leaf);
			return temp;
		}
		//case (2) => this can only happen when s.length() > cur_edgelabel.length(); i = m = cur_edgelabel.length()
		else
		{
			return FindPath(u->children[e], s.substr(i), suf_i);
		}
	}
}


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

node* FindLoc(node* u, string ri, int *deepestSoFar, node * deepestNode, vector <int> *Li)
{
	int i = 0;
	int m = 0;
	string cur_edgelabel = "";

  while (ri)
  {
    //pick the branch e of u that starts with s[0]
    //index of the branch e in the parent's children

 	int e = find_branch(u, ri[0]);

     // no branch found, we are as far down as we can go
     // test node depth for deepest-So-Far:
     //
     // If we are here because of a recursive call, then if no e is found,
     // then there is no path below the current node, but there was a
     // matching path on the previous node, so, we have found case A, where
     // the mismatch occurs at a node, so return last visited node, which is u:

 	if (e == -1)
 	{
       // test if depth >= xi,
       // test if depth is deepest so far,
       // if both conditions are met, set
       // deepestNode pointer to u:

     if ((u->depth >= xi) && (u->depth > deepestSoFar) )
     {
       deepestNode = u;
     } // end if node depth >= lambda

 	} // end if e == -1

     //if the branch e exists, move down into the branch

 	else
 	{
 		cur_edgelabel = u->children[e]->p_edgelabel;
 		i = 0;
 		m = cur_edgelabel.length();

       // if the string length is less than the edge label,
       // we will have matched up to the current node and
       // if we were to follow the edge, whether there is a
       // matching path or not, the current node will be the
       // last visited node
       // so, take current node suffix link and start again:

 		if (s.length() < m)
 		{
       if ((u->depth >= xi) && (u->depth > deepestSoFar) )
       {
         deepestNode = u;
       } // end if node depth >= lambda

       u = u->SL;

       FindLoc(u->children[e], ri.substr(i), deepestSoFar, deepestNode, Li);

 		} // end if s.length() < m

       // if string length is greater than, or equal to
       // the edge label, test the path:

 		while (i < m)
 		{
           // if a mismatch is found:
           // Two cases:
           // case A:
           //    matching path terminates at a node:
           // case B:
           //    matching path terminates along an edge:

 				if (cur_edgelabel[i] != ri[i])
 				{
           FindLoc(u->children[e], ri.substr(i), deepestSoFar, deepestNode, Li);
 					break;

 				} // end if cur_edgelabel[i] != ri[i]

 				i++;

 		} // end while i < m

 		  //at this point, i can be either (1) index of the first different char pair or (2) length of the shorter string

   		//case (1) => break the cur_edge right before i,
   		//insert a new node to the branch,
   		//insert a new edge from the new node for the rest of ri

 		if (i < m)
 		{

 			//return temp;

 		} // end i < m

 		//case (2) => this can only happen when s.length() > cur_edgelabel.length(); i = m = cur_edgelabel.length()
 		else
 		{
 			FindLoc(u->children[e], ri.substr(i), deepestSoFar, deepestNode, Li);

 		} // end else ri.length > cur_edgelabel.length

 	} // end else

  ri = ri.substr(i);

  } // end while there are characters to evaluate



  Li.push_back (deepestNode->start_leaf_index);
  Li.push_back (deepestNode->end_leaf_index);

} // end FindLoc function


/* This function inserts a child to a parent's children in lexicographic order
 * Inputs:	u = parent node
 *			child = the child node of u
 * Return: none
 */
void insert_child(node* u, node* child)
{
	string this_edge = child->p_edgelabel;
	string sib_edge;
	int i = -1;
	vector<node*>::iterator it;
	for (it = (u->children).begin(); it < (u->children).end(); it++)
	{
		i++;
		sib_edge = (*it)->p_edgelabel;
		if (lexicographical_compare(this_edge.begin(), this_edge.end(), sib_edge.begin(), sib_edge.end()))
		{
			break;
		}
	}

	if (i==-1) {i = 0;} //if i==-1 then u has no children

	string last_sib_edge = u->children.back()->p_edgelabel;
	if (lexicographical_compare(last_sib_edge.begin(), last_sib_edge.end(), this_edge.begin(), this_edge.end())) {i++;} //need to i++ when this_edge is the max

	u->children.insert(u->children.begin()+i, child);
}

/* This function finds a branch from a given node that starts with a given char
 * Inputs: 	u = the node to search for the branch
 *			c = the character that the branch starts at
 * Return index of the branch in u's children
 * If the branch does not exist, return -1
 */
int find_branch(node *u, char c)
{
	int i = 0;
	vector<node*>::iterator it;
	for (it = (u->children).begin(); it < (u->children).end(); it++)
	{
		if ((*it)->p_edgelabel[0] == c)
		{
			return i;
		}
		i++;
	}

	return -1;
}

/* This function breaks down an edge to insert a node
 * Inputs: 	u = the node that has the edge to break
 *			e = index of the branch in the u's children
 *			break_ind = index on the edge after which the edge will be broken
 * Return: pointer to the new node
 */
node* insert_middle(node* u, int e, int break_ind)
{
	string edgelabel = u->children[e]->p_edgelabel;
	//break down the edgelabel
	string upper_edgelabel = edgelabel.substr(0, break_ind+1);
	string lower_edgelabel = edgelabel.substr(break_ind+1);

	//make the new node
	node* new_node = new node;
	assign_node_id(new_node);
	new_node->SL = NULL;
	new_node->parent = u;
	new_node->depth = u->depth + break_ind + 1;
	new_node->p_edgelabel = upper_edgelabel;
	new_node->children.push_back(u->children[e]);

	//update new_node->children //which is only one
	new_node->children[0]->parent = new_node;
	new_node->children[0]->p_edgelabel = lower_edgelabel;

	//insert the new_node to the tree (update u)
	u->children.erase(u->children.begin() + e);
	insert_child(u, new_node);
	return new_node;
}

/* This function displays a ST */
void display_tree(ST tree)
{
	cout << "-----------------------------------" << endl;
	cout << "tree" << endl << endl;
	cout << "root=" << tree.root.id << endl;
	help_display_tree(&(tree.root));
}

/* This is a helper funtion to display_tree() */
void help_display_tree(node* u)
{
	int SL = 0;
	if (u->SL != NULL)
	{
		SL = u->SL->id;
	}
	cout << "id=" << u->id <<"\tparent=" << u->parent->id << "\tp_label=" << u->p_edgelabel << "\tSL=" << SL << "\tdepth=" << u->depth << "\t[" << u->start_leaf_index << "," << u->end_leaf_index << "]" << "\tchildren=";
	vector<node*>::iterator it;
	for (it = (u->children).begin(); it < (u->children).end(); it++)
	{
		cout << (*it)->id << "  ";
	}
	cout << endl;
	for (it = (u->children).begin(); it < (u->children).end(); it++)
	{
		help_display_tree(*it);
	}
}
