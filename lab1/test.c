#include <unistd.h>
#include <stdio.h>

int main (void) {
	int myID;
	myID = fork();
	if (myID)
		printf("parent: %d\n",myID);
	else
		printf("child: %d\n",myID); 
}	
