/*
* README.txt
*
* Marcus Blaisdell
*
*/

I have a directory that I have put my code in and divided it into
two subdirectories:
Code
Data

The Code folder contains the source code and executable,
The Data folder contains the data files.

I am using indirect referencing to load the data file from the "Data" directory.
e.g. ../Data/Opsin1_colorblindness_gene.fasta.txt

I am currently getting "Segmentation Fault: 11" when I try to run this.
I know that this means I am running out of memory and I need to change the way
I am using my 2-d matrix that stores my structs that hold the scores for each
cell.
I did all of my testing using the small, "test.txt" file and that was functioning
as expected. I am inexperienced with working with large datasets and need to learn
more about this.

I plan to correct this and resubmit Wednesday so if you are reading this,
I was not able to fix the error.
