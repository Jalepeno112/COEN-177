#include <unistd.h>
#include <stdio.h>

int main (void) {
	int i;
	int childCounter = 0;
	
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

