#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "deque.h"

#define BUFFER_SIZE 1024

int main (int argc, const char* argv[]) {
	/*
 	* argc should be 2 
 	* arvg[1] is the size of the page table/ amount of memory avaiable/ the number of page frames
	*/

	if (argc != 2) {
		fprintf(stderr, "Not enough input arguments\n");
		return 1;
	}

	int page_frames = atoi(argv[1]);
	char buffer[BUFFER_SIZE];

	
	int page_faults = 0;		//counter of page faults
	int memory_accesses = 0;	//counter of memory accesses (lines in file)
	

	//create DEQUE
	DEQUE* page_table = createDeque();
	

	//loop through the file and grab the numbers in there
	while (fgets(buffer, BUFFER_SIZE, stdin) != NULL ) {
		int access;
		//find the first integer in the line and store in x
		int n = sscanf(buffer, "%d", &access);
		//only try and access the page if the value is a number
		if (n > 0){
			memory_accesses++;
			//if this page is already in the table, set its ref to 1 
			if (findNode(page_table, access) != NULL) {
				setRef(page_table,access);
			}
			//try and add the this page to the queue (oldest in front, newest in back)
			//if the queue is already at capacity, search for a page that we can remove
			else if (numItems(page_table) ==  page_frames) {
				/*FIND AND REPLACE PAGE USING CLOCK ALGORITHM*/
				clockSearchRemove(page_table);	
				//add the new node at the end of the queue
				addLast(page_table, access);
				page_faults++;	
				printf("%d\n", access);
			}
			//if the page is not already in the list and there is room to add it, place it at the end of the list
			else {
				addLast(page_table, access);
				page_faults++;	
				printf("%d\n", access);
			}
		}
	}
	//printf("memory accesses: %d\n",memory_accesses);
	//printf("page faults: %d\n",page_faults);	
}
