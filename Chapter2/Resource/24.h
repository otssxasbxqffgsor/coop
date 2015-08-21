#include <stdio.h>
#include <stdlib.h>

struct Data{
	int value;
	struct Data *next;
};

struct Data *Initializer(){
	struct Data *head = (struct Data*) malloc(sizeof(struct Data));
	head->value = 0;
	head->next = NULL;
	return head;
}

void Add(int a, struct Data *head){

	//if Head is not NULL
	if (head != NULL){

		// Create a new Node
		struct Data *nNode = (struct Data*)malloc(sizeof(struct Data));
		nNode->value = a;
		nNode->next = NULL;
		struct Data *prt = head;

		while (prt->next!=NULL)
		prt = prt->next;
		prt->next = nNode;
	}
}


struct Data* Par(int x){
	if (x != NULL){
		struct Data *beforeHead = NULL;
		struct Data *beforeEnd = NULL;
		struct Data *afterHead = NULL;
		struct Data *afterEnd = NULL;
		struct Data* head = (struct Data*) malloc(sizeof(struct Data*));
		struct Data *prt = head;
		struct Data *next = prt->next;
		while (prt != NULL){
			if (prt->value < x){

				// First HalfCut
				if (beforeHead == NULL)
				{// i=0;
					beforeHead = prt;
					beforeEnd = head;
				}
				else
				{// user pointer to pointer to get to the end of the linked list 

					beforeHead = prt;
					beforeEnd->next = prt;
				}
				// End of first half cut
			}
			else
			{
				if (afterHead = NULL){
					afterEnd->next = afterHead;
					afterEnd = prt;
				}
				else
				{
					afterEnd->next = prt;
					afterEnd = prt;
				}
			}
		prt = next;
	}
	if (afterHead == NULL)
		return beforeHead;
	// merge
	beforeHead->next = afterHead;
	return beforeHead;
}


}


int Solution24(){

	struct Data *_header = (struct Data*)Initializer();

	Add(5, _header);
	Add(1, _header);
	Add(3, _header);
	Add(5, _header);
	Add(6, _header);
	Add(2, _header);
	Add(7, _header);
	Add(8, _header);

	struct Data *P = Par(9, _header);
	
	return 0;

}

