#include <unistd.h>
#include <stdio.h>

int main (void) {
	
	int i;	//loop counter
	int childCounter = 0;//keep track of how many children we have created
	
	/*create a new process*/
	int childID;
	childID = fork();
	
	while (childCounter < 7){		
		/*if the process is the parent*/
		if (childID > 0 ){
			break;
		}	
		/*if it is the child, allow it to spawn new children. Increment counter keeping track of the number of spawned children*/
		else if (childID == 0){
			printf("I am a child of parent: %d (myPID %d)\n", getppid(), getpid());
			childID = fork();
			childCounter++;
		}
		else
			return 1;
	}
	if (childCounter == 7)
		printf("Total children %d\n", childCounter);
}
int spawnChildren(int numberOfChildren, int count) {
        /*Creates a chain of processes.  Each child process creates one other child until *numberOfChildren* number of processes are created*/
        if (count == numberOfChildren)
                return count;

        /*create a new process*/
        int myID = fork();
        /*if I am a child, recursively create a new process*/
        if (myID == 0) {
                printf("I am child of parent %d (my PID is %d)\n",getppid(), getpid());
                //printf("Spawning new child")
                count++;
                spawnChildren(numberOfChildren, count)
	}
}
                
