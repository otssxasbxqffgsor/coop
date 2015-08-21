#include <stdio.h>
#include <stdlib.h>
/*
Day1:
Write a function to remove duplicated items from linked lists:
Method 1: Use two loops, use a hashtable, use a sort algorithm:
*/

// structure of data
struct Data{
	int value;
	struct Data *next;
};
/*

// Initialize a linked header with zero valu
struct Data *InitializeLinkedList(){

	struct Data *Header = (struct Data*)malloc(sizeof(Data));
	if (Header)
	{
		Header->value = 0;
		Header->next = NULL;
	}
	return Header;
};


bool Add(int value, struct Data *header){
	if (value != NULL && header != NULL){
		struct Data *newNode = (struct Data*) malloc(sizeof(Data));
		newNode->value = value;
		newNode->next = NULL;
		struct Data *prt = header;
		while (prt->next != NULL)
			prt = prt->next;
		prt->next = newNode;
		return true;
	}
	else 
		return false; 
	
	
	}


void removeDuplicate(struct Data *header)
{
	struct Data *prt1, *prt2, *dup;
	prt1 = header;

	while (prt1->next != NULL && prt1 != NULL){
		prt2 = prt1;

			// Compair
			while (prt2!=NULL &&prt2->next != NULL){
				struct Data *PrtPrev = prt2;
				
				if (prt2->next->value == prt1->value){
					dup = prt2->next;
					prt2->next = prt2->next->next;
					free(dup);

				}
				prt2 = prt2->next;
					
			}

		prt1 = prt1->next;

	}
}


int main(){

	struct Data *myList = InitializeLinkedList();
	Add(1, myList);
	Add(2, myList);
	Add(3, myList);
	Add(4, myList);
	Add(5, myList);
	Add(3, myList);
	Add(7, myList);
	removeDuplicate(myList);

	
	
	return 0;



};*/