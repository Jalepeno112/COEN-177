#include <unistd.h>
#include <stdio.h>
/* Giovanni Briggs
 * 10/6/14
 * COEN 177
 * Lab 1 Part 1
 *
 * File: forking.c
 *
 * Description: create 7 processes.  Each child process creates another child until a total of 7 have been created.
 * 		This file completes Part 1 of the lab. 
 * Output:
 * 	This file outputs text to the terminal window.  The printf function lives in the recursive *spawnChildren* function.
 * 	The output looks like this:
 * 		My PID is *myPID* (I am a child of *parentPID*)
 * 	*myPID* is the process's PID and *parentPID* is the parent's PID.
 * 	If you look at the output, you will see that every PID is a descandant of the PID before it, and that there are 7 total processes.
 * 	Every process only produces one child.
 * 	
 * 	The main process is distinguished as being different, and is not considered one of the 7 processes created by this program.
 */
int main (void) {
	printf("I am the main process: PID %d\n",getpid());

	int totalNumberOfChildren = 7; 	//the total number of children you want to create
	spawnChildren(7,0);
}


/*
 * Function:	spawnChildren
 *
 * Description: recursively create a certain number of processes.  
 * Each child process is allowed to re-enter the recursive function, but parents stop after they fork.
 *
 * param numberOfChildren:	the total number of children you want to create
 * param count:			the current number of children that have been created.  When using the function, this number should always be 0.
 */
int spawnChildren(int numberOfChildren, int count) {
        /*Creates a chain of processes.  Each child process creates one other child until *numberOfChildren* number of processes are created*/
        if (count == numberOfChildren)
                return count;

        /*create a new process*/
        int myID = fork();
        /*if I am a child, recursively create a new process*/
        if (myID == 0) {
                printf("My PID is %d (I am a child of %d)\n",getpid(), getppid());
                //increase the number of children we have created
		count++;
                spawnChildren(numberOfChildren, count);
	}
}
                
