/*
 *File:         deque.c
 *
 *Description:  This file contains the functions needed to implement a linked list as
 *				a queue in order to complete a series of tasks
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "deque.h"

struct node {
	int data;		//data
	int used;		//how many times the page has been used
	int time;		//at what clock cycle the page was added to the list
	int referenced;		//1 if the page has been referenced, 0 otherwise.
	struct node *prev;	//point to previous node
	struct node *next;	//point to next node
}; 

struct deque {
	NODE *sentinel;
	NODE *clock;
	int count;
};

/*
 * Function: 	createSet
 * Description: create and return a pointer to a DEQUE with a sentinel node
 * Runtime:		O(1) 
 */
DEQUE *createDeque(void) {
	DEQUE *dp = (DEQUE *)malloc(sizeof(DEQUE));
	assert(dp != NULL);
	dp->sentinel = malloc(sizeof (NODE));
	assert(dp->sentinel != NULL);
	/*Link the sentinel node to itself */
	dp->sentinel->next = dp->sentinel;
	dp->sentinel->prev = dp->sentinel;

	//set the clock pointer to equal the sentinel node
	dp->clock = dp->sentinel;

	/*Sentinel node contains no data, so it does not count towards count*/
	dp->count = 0;
	return dp;
}//end createDeque
/*
 * Function: 	destroySet
 * Description: traverse through the linked list and free all of the memory that has been allocated
 * Runtime:		O(n), where n is the length of the list
 */
void destroyDeque(DEQUE *dp) {
	assert(dp != NULL);
	NODE * head = dp->sentinel->next;
	NODE * temp;
	/* 
	 * If dp->sentinel->next == NULL, then dp->sentinel is the only thing to free and the while loop wont run
	 * Want the while loop to go through the list and delete all nodes until it circles back and hits the sentinel, as that marks the end of the circle
	 * Free the sentinel outside of the loop and then free the deque
	*/
	while (head != NULL && head != dp->sentinel) {
		temp = head;
		head = head->next;
		free(temp);
	}//end while
	free(dp->sentinel);
	free(dp);
	return;
}//end destroyDeque

/*
 * Function: 	numItems
 * Description: return the number of items in the deque
 * Runtime:		O(1)
 */
int numItems(DEQUE * dp) {
	return dp->count;
}//end numItems

/*
 * Function: 	addFirst
 * Description: add the data into a node at the beginning of a given list.  Allocate memory for the node, and assign pointers accordingly
 * Runtime:		O(1)
 */
void addFirst (DEQUE *dp, int x) {
	assert(dp != NULL);
	/*Allocate memory for a new node and then assert that it was allocated correctly*/
	NODE * np = malloc(sizeof(NODE));
	assert(np != NULL);
	np->data = x;
	//when a node is first added, it has been referenced
	np->referenced = 1; 
	np->used = 0;
	np->time = 0;
	/* Insert the new node into the circular doubly linked list directly after the sentinel(sentinel->next = np).*/
	dp->sentinel->next->prev = np;
	np->next = dp->sentinel->next;
	np->prev = dp->sentinel;
	dp->sentinel->next = np;
	dp->count++;
}//end addFirst


/*
 * Function: 	addLast
 * Description: add the data into a node at the end of a given list.  Allocates memory for the node and assigns pointers accordingly
 * Runtime:		O(1)
 */
void addLast(DEQUE *dp, int x) {
	assert(dp != NULL);
	NODE * np = malloc(sizeof(NODE));
	assert(np != NULL);
	np->data = x;
	//when a node is first added, it has been referenced
	np->referenced = 1; 
	np->used = 0;
	np->time = 0;
	/*Insert the new node after the sentinel (sentinel->prev = np)*/
	dp->sentinel->prev->next = np;
	np->prev = dp->sentinel->prev;
	np->next = dp->sentinel;
	dp->sentinel->prev = np;
	dp->count++;
}//end addLast

/*
 * Function: 	removeFirst
 * Description: returns the data of the first node in the list, reassigns pointers to keep the list together, and then removes the first node
 * Runtime:		O(1)
 */
int removeFirst(DEQUE *dp) {
	assert(dp != NULL);
	/*If the sentinel is the only node in the deque, then there is nothing to remove and return*/
	if (dp->count == 0)
		return -1;
	/*Return the data (int) from the node after sentinel (sentinel->next) and reassign pointers*/
	int data = dp->sentinel->next->data;
	NODE *np = dp->sentinel->next; //temporary copy
	dp->sentinel->next = np->next;
	np->next->prev = dp->sentinel;
	free(np);
	dp->count--;
	return data;
}//end removeFirst

/*
 * Function: 	removeLast
 * Description: returns the data of the last node in the list, reassigns pointers to keep list together and then removes the last node
 * Runtime:		O(1)
 */
int removeLast(DEQUE *dp) {
	assert(dp != NULL);
	/*If the sentinel is the only node in the deque, then there is nothing to remove and return*/
	if (dp->sentinel->next == NULL)
		return - 1;
	/*Return the data (int) from the node before sentinel (sentinel->prev) and reassign pointers*/
	int data = dp->sentinel->prev->data;
	NODE *np = dp->sentinel->prev; //temporary copy
	dp->sentinel->prev = np->prev;
	np->prev->next = dp->sentinel;
	free(np);
	dp->count--;
	return data;
}//end removeLast

/*
 * Function: 	getFirst
 * Description: return the data from the first node in the list, but does not remove it
 * Runtime:	O(1)
 */
int getFirst (DEQUE *dp) {
	assert(dp != NULL);
	if (dp->sentinel->next == NULL)
		return -1;
	return dp->sentinel->next->data;
}//end getFirst

int getFirstRef(DEQUE *dp) {
	assert(dp != NULL);
	if (dp->sentinel->next == NULL)
		return -1;
	return dp->sentinel->next->referenced;
	
}


/*
 * Function: 	getLast
 * Description: returns the data from the last node in the list, but does not remove it
 * Runtime:		O(1)
 */
 int getLast (DEQUE *dp) {
	assert(dp != NULL);
	if (dp->sentinel->next == NULL)
		return -1;
	return dp->sentinel->prev->data;
 }//end getLast

/*
 * Function: 	isIn
 * Description:	returns 1 if a node contains the value x, 0 otherwise
 *
 */

int isIn(DEQUE *dp, int x) {
	NODE* np = findNode(dp, x);
	if (np != NULL) {
		return 1;
	}
	return 0;
}

void setRef(DEQUE *dp, int x) {
	NODE* np = findNode(dp, x);
	np->referenced = 1;	
}

void setTime(DEQUE *dp, int x, int time) {
	NODE* np = findNode(dp, x);
	np->time = time;
	np->used++;
}


/*
 * Set the time of the last node in the list
 */
void setLastTime(DEQUE *dp, int time) {
	assert(dp != NULL);	
	dp->sentinel->prev->time = time;
	dp->sentinel->prev->used++;
}

/*
 * Function:	findNode
 * Description:	find the node with the given value x (assumes all values are unique)
 *		if the value is found, return a pointer to the node that holds it
 */
NODE* findNode(DEQUE *dp, int x) { 
	int found = 0;
	NODE* np = dp->sentinel->next;
	while (np != dp->sentinel) {
		if (np->data == x) {
			//if the page is already in the list, do nothing
			found = 1;
			break;
		}
		np = np->next;
	}
	if (found == 1)
		return np;
	else
		return NULL;
}

/*
 * Function:	moveToFront
 * Description:	move a given node to the front of the deque
 */
void moveToFront(DEQUE *dp, int x) {
	assert(dp != NULL);
			
	/*If the sentinel is the only node in the deque, then there is nothing to remove and return*/
	if (dp->sentinel->next == NULL)
		return;

	//find the node
	NODE* n = findNode(dp,x);
	if (n == NULL)
		return;

	//break the list chain around n
	n->prev->next = n->next;
	n->next->prev = n->prev;
	
	//insert n in the front of the list
	n->prev = dp->sentinel;
	n->next = dp->sentinel->next;
	dp->sentinel->next->prev = n;
	dp->sentinel->next = n;
	return;	
}


void moveToBack(DEQUE *dp, int x) {
	assert(dp != NULL);

			
	/*If the sentinel is the only node in the deque, then there is nothing to remove and return*/
	if (dp->sentinel->next == NULL)
		return;
	
	//find the node
	NODE* n = findNode(dp,x);
	if (n == NULL)
		return;
	//if the node is already at the back, return
	if (n == dp->sentinel->prev) {
		n->referenced = 0;
		return;	
	}
	//break the list chain around n
	n->prev->next = n->next;
	n->next->prev = n->prev;
	
	//insert n in the front of the list
	n->next = dp->sentinel;
	n->prev = dp->sentinel->prev;
	dp->sentinel->prev->next = n;
	dp->sentinel->prev = n;

	n->referenced = 0;	
	return;	

}

void removeOldestTime(DEQUE* dp) {
        assert(dp != NULL);

        if (dp->sentinel->next == NULL)
                return;

        NODE* np = dp->sentinel->next;
        NODE* least = np;
	//search for lowest time
        while (np != dp->sentinel) {
                if (np->time < least->time) {
                        least = np;
                }
		np = np->next;
        }
	//remove lowest time
        least->prev->next = least->next;
        least->next->prev = least->prev;
        free(least);
        dp->count--;
}

void printDeque(DEQUE *dp) {
	NODE* np = dp->sentinel->next;

	while (np != dp->sentinel) {
		printf("data:%d; ref: %d; time: %d\n",np->data, np->referenced, np->time);
		np = np->next;
	}
	printf("------------------------------\n");
}

void removeLeastUsed(DEQUE *dp) {

	assert(dp!=NULL);
	if (numItems(dp) == 0)
		return;

	
	NODE* np = dp->sentinel->next;
	NODE* least = np;
	
	//search for node with the lowest "used" counter.
	//if there is a tie, remove the one used furthest in the past
	while (np != dp->sentinel) {
		if (np->used < least->used) {
			least = np;
		}
		else if (np->used == least->used) {
			if (np->time < least->time) {
				least = np;
			}
		}
		np = np->next;
	}
	//remove lowest time
        least->prev->next = least->next;
        least->next->prev = least->prev;
        free(least);
        dp->count--;

}

void updateUsed(DEQUE *dp, int x) {
	assert(dp!=NULL);
	NODE* np = findNode(dp, x);
	np->used = np->used + 1;
}

//update the used variable of the last node in the deque
void updateBackUsed(DEQUE *dp) {
	assert(dp!=NULL);
	dp->sentinel->prev->used = dp->sentinel->prev->used + 1;
}

void clockSearchRemove(DEQUE* dp) {
	assert(dp != NULL);
	if (numItems(dp) == 0) {
		return;
	}	
	
	//if the clock is pointing to the sentinel node, point it to the next node
	if (dp->clock == dp->sentinel)
		dp->clock = dp->sentinel->next;
	
	NODE* temp = dp->clock;
	
	//search for a node with a referenced value of 0.  If temp is currently pointing to the sentinel node, allow it through and jump over it
	while (temp->referenced != 0 || temp == dp->sentinel) {
		//skip over sentinel node
		if (temp == dp->sentinel) {
			temp = dp->sentinel->next;
			continue;
		}
		
		//set the referenced value to 0
		temp->referenced = 0;
		temp = temp->next;
	}
	
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	//reset the clock
	dp->clock = temp->next;

	//free the node 
	free(temp);
	dp->count--;
}
