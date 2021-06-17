/* Author: Marcus Blaisdell, Ngoc Duong
 * Date: 04/21/2019
 * This program tests ST1.cpp
 */
 
#include "ST1.h"
#include <fstream>
#include <ctime>

string help_message = "To execute: $<test executable> <input file containing sequences> <input alphabet file>";

int main(int argc, char *argv[])
{
	//catch: missing arguments
	if (argc < 3)
	{
		cout << endl << "Error: missing arguments" << endl;
		cout << help_message << endl << endl;
		return 0;
	}
	
	//*assume at this point, argv[1] and argv[2] are valid inputs
	
	//read argv to create an input string
	string line;
	string input_string;
	ifstream seq_file(argv[1]);
	
	getline(seq_file, line); //discard the first line
	while(getline(seq_file, line))
	{
		if (*line.rbegin() == '\n')
		{
			line.erase(line.size()-1);
		}
		input_string += line;
	}
	
	seq_file.close();
	
	//read argv to create an alphabet
	char c;
	vector<char> alphabet;
	ifstream alp_file(argv[2]);
	
	while(alp_file.get(c))
	{
		if (c != ' ')
		{
			alphabet.push_back(c);
		}
	}
	
	alp_file.close();
	
	//build the ST
	//time_t time1 = time(NULL);
	ST tree(input_string, alphabet);
	//time_t time2 = time(NULL);

	
	/*
	fstream outfile;
        const size_t ind = string(argv[1]).rfind('/');
        string wdir = string(argv[1]).substr(0,ind);

	//print basic stats of the tree
	outfile.open((wdir + string("/stats_time_LMR.txt")).c_str(), ios::out);
        streambuf* stream_buffer_file = outfile.rdbuf();
        cout.rdbuf(stream_buffer_file);

	tree.display_stats();
	
	cout << endl << "Time to construct the tree: " << int(time2) - int(time1) << " seconds." << endl << endl;	

	tree.LMR();
	outfile.close();	

	//handpick some random nodes' children lists then execute traversals
	  //DFS
	outfile.open((wdir + string("/root_second_child_DFS.txt")).c_str(), ios::out);
        stream_buffer_file = outfile.rdbuf();
        cout.rdbuf(stream_buffer_file);
	tree.DFS_tree(tree.root.children[1]);
	outfile.close();
	  //post-order traversal
	outfile.open((wdir + string("/root_second_child_POT.txt")).c_str(), ios::out);
	stream_buffer_file = outfile.rdbuf();
	cout.rdbuf(stream_buffer_file);
	tree.POT_tree(tree.root.children[1]);
	outfile.close();
	
	//print out BWT to an outfile
	outfile.open((wdir + string("/myBWT.txt")).c_str(), ios::out);
	stream_buffer_file = outfile.rdbuf();
	cout.rdbuf(stream_buffer_file);
	tree.display_BWT_index();
	outfile.close();
	*/
	tree.prepareST(0);
	display_tree(tree);
	
	cout << "-------------prepare for FinLoc-------------" << endl;
	vector<int> A = tree.display_BWT_index();
	
	cout << "-----------Call FindLoc---------------" << endl;
	vector<int> Li = my_find_loc(&(tree.root), "AGTAGTACGTCGTACTGCATGTCATGTTGATCGATCGTACGTAGCTAGC", &A, 4);
	vector<int>::iterator it;
	for (it = Li.begin(); it < Li.end(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}
