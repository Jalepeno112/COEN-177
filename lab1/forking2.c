/*
 * Giovanni Briggs
 * COEN 177L
 * Lab 1
 * 9/29/14
 *
 * File:	forking2.c
 * Description:	Create 7 processes, where each process creates two other processes.
 * 		The first process splits off into two, and then each of those children splits off into so many children.
 * 		The resulting tree looks like this
 * 		  main
 * 		 /    \
 * 		c1    c2
 * 	       / \    / | \
 * 	      c3 c4  c5 c6 c7
 * 	      The second child that is created creates three children in order to give us a total of 7 children
 *
 * This file completes Part 2 ("The Extra Challenge") of lab 1
 *
 * Output:
 * 	The main function outputs text to the terminal window.  Each line includes the PID of the process, and the PID of it's parent.
 * 	It looks like this:
 * 		I am a process: PID *myPID* (child of PID *parentPID*)
 * 	*myPID* is the process's PID, and *parentPID* is the parent's PID.  
 * 	If you look at the output you will see that at least 2 processes, and no more than 3, are children of the same parent.
 *
 * 	The main process is differentiated (it recieves a special output) and is not considered one of the 7 processes created by this program
 */


#include <unistd.h>
#include <stdio.h>
/*
 * Function:	main
 * Description:	main function.  Creates 7 processes using the fork() function in a loop.
 * 		After a child is created, the loop will modify the loop parameters *i* and *N* so that the child creates a certain number of children.
 * 		*i* is the loop counter, and *N* is the number of children that the process should create. 
 */
int main(void) {

	printf("I am the main process: PID %d\n",getpid());
	int i;
	i = 0;
	/*keep track of how low in the "tree" we are (height of tree)*/
	int level = 1;
	int max_height = 3;
	int N = 2;	

	for (i = 0; i < N; i++) {
		int myID = fork();
		/*if the fork is a child, reset the loop parameters so it will create 2 new processes*/
		if (myID == 0) {
			printf("I am a process: PID %d (child of PID %d)\n", getpid(), getppid());
			/*if i == 1, then we have create our second child, but we want that second child to create 3 children
			we set it's loop paramaters differently.
			*/
			if (i == 1) {
				N = 3;
			}
			else {
				N = 2;
			}
			/*set i = to -1 so that for the child, the loop will increase i to be 0*/
			i = -1;
			/*increase the level counter because we are now one level lower in the tree*/
			level++;
		}
		/*if a child process is spawned but it has "level" greater than max_height, then it will NOT spawn a new child process.
		We want to create a tree of height max_height, but we don't want the processes on height max_height to create more children
		*/
		if (level >= max_height ) {
			break;
		}
	}
}
