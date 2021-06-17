How to compile and the program:

To compile:	g++ program1.cpp ST1.cpp

To run: 	./a.out <sequence file> <alphabet file>
Example:	./a.out test/Human_BRCA2_gene/seq test/Human_BRCA2_gene/alp

Architecture of the 'test' directory:
The 'test' directory contains 7 subdirectories associate with 7 given inputs.
In each of the subdirectory, there are:
	+ seq : file that contains the sequence
	+ alp : file that contains the alphabet
	+ expected_BWT : given in the instruction, not all subdir has it
	+ myBWT.txt : BWT produced by the program
	+ stats_time_LMR.txt : file that contains stats of the tree, tree construction time in seconds, and information of the longest exact matching repeat
	+ root_second_child_DFS.txt : node depths of the second-from-the-left-child-of-the-root tree obtained by DFS
	+ root_second_child_POT.txt : node depths of the second-from-the-left-child-of-the-root tree obtained by post-order traversal
