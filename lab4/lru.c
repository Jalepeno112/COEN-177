#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "deque.h"

#define BUFFER_SIZE 1024

int main (int argc, const char* argv[]) {
        /*
 *         * argc should be 2
 *                 * arvg[1] is the size of the page table/ amount of memory avaiable/ the number of page frames
 *                         */

        if (argc != 2) {
                fprintf(stderr, "Not enough input arguments\n");
                return 1;
        }

        int page_frames = atoi(argv[1]);
        char buffer[BUFFER_SIZE];

	int clock_cycles = 0;		//used for "time" at which the page entered memory
        int page_faults = 0;            //counter of page faults
        int memory_accesses = 0;        //counter of memory accesses (lines in file)


        //create DEQUE
	DEQUE* page_table = createDeque();


	//loop through the file and grab the numbers in there
	while (fgets(buffer, BUFFER_SIZE, stdin) != NULL ) {
		int access;
		//find the first integer in the line and store in x
		int n = sscanf(buffer, "%d", &access);
		if (n > 0) {
			
			clock_cycles++;
			memory_accesses++;
			if (findNode(page_table,access) != NULL) {
				//if page is already in the list
				//fprintf(stderr, "Updating page\n");
				setTime(page_table,access,clock_cycles);
			}
			else if(numItems(page_table) ==  page_frames) {
				/*Find page to replace*/
				removeOldestTime(page_table);
				addLast(page_table,access);
				setLastTime(page_table,clock_cycles);
				page_faults++;
				//fprintf(stderr, "PAGE FAULT: %d\n", access);
				printf("%d\n", access);
			}
			else {
				//first time adding page
				//fprintf(stderr, "Adding page\n");
				addLast(page_table,access);
				setLastTime(page_table,clock_cycles);
				page_faults++;
				printf("%d\n", access);
			}
		}

	}
	//printf("memory accesses: %d\n",memory_accesses);
	//printf("page faults: %d\n",page_faults);
} 

