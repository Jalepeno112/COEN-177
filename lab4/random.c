#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char*argv[]) {
	srand(time(NULL));
	if (argc < 2) {
		printf("Not enough input arguments given!");
		exit(1);
	}
	/*FILE *f = fopen("accesses.txt","w");

	if (f == NULL) {
		printf("Could not open file!");
		exit(1);
	}*/

	int count = 0;
	int amount = atoi(argv[1]);

	int min = 1;
	int max = 10000;
	int inc = 100;
	while (count < amount/10000) {
		int internal = 0;
		while (internal < 10000)
		{	
			int r = (rand()%(max-min)) + min;
			
			printf("%d\n",r);
			internal++;
		}
		count++;
		min += inc;
	}
	
}
