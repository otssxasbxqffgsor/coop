// Fast and slow runner. 
// Build a circular linked list: 

#include"stdio.h"


struct Data {
	int val;
	struct Data *next;
};


struct Data *Append(int val){

	struct Data* newNode = (struct Data*) malloc(sizeof(struct Data));
	newNode->val = val;
	newNode->next = NULL;
	return newNode;
};

struct Data *Build(int L){

	if (L){

		struct Data *Head = (struct Data*) malloc(sizeof(struct Data));
		struct Data *prt = Head;
		Head->val = L;
		Head->next = NULL;
		
		while (L && prt!=NULL){
			prt->next = Append(L);
			prt = prt->next;
			L--;
		}
		prt->next = Head;
		return Head;
	}
}



int Solution26(){

	struct Data *CirHead = Build(5);



	return 0;
}


