#include "stdlib.h"

struct Data{
	int value;
	struct Data *next;
};


struct Data *CreateAHeader(){
	struct Data *localHeader = (struct Data*)malloc(sizeof(struct Data));

	if (localHeader != NULL)
	{
		localHeader->value = 0;
		localHeader->next = NULL;
	}

	return localHeader;
};

void Add(int val, struct Data *header){
	if (val)
	{

		struct Data *_newNode = (struct Data*) malloc(sizeof(struct Data));
		_newNode->value = val;
		_newNode->next = NULL;
		struct Data *prt = header;

		while (prt->next != NULL)
			prt = prt->next;
		prt->next = _newNode;

	}
};


struct Data *FindKth(int k, struct Data *header){
	if (header == NULL)
		return NULL;

	struct Data *prt = header;
	int l = 0;
	int i = 0;
	//while (prt != NULL || prt->next != NULL){ //
	while (prt != NULL){
		i = i + 1;
		prt = prt->next;
	}
	l = i;
	if (k > l)
		return NULL;
	prt = header;

	while (prt != NULL){
		for (i = 0; i<l; i++){

			if (i == (l - k))
				return prt;

			else
				prt = prt->next;
		}
	}

};

struct Data *KthIteration(int k, struct Data *header){
	struct Data *prt1 = header;
	struct Data *prt2 = prt1;

	for (int i = 0; i <= k - 1; i++)
		if (prt2 != NULL)prt2 = prt2->next;
	while (prt2 != NULL)
	{
		prt1 = prt1->next;
		prt2 = prt2->next;
	}

	return prt1;

};

void DeleteMiddle(struct Data *node){

	struct Data *temp = node->next;
	node->value = node->next->value;
	node->next = node->next->next;
	free(temp);

}




struct Data *PartitionList(struct Data *_head, int x){
	struct Data *BeforeHead = NULL;
	struct Data *BeforeTail = NULL;
	struct Data *AfterTail = NULL;
	struct Data *AfterHead = NULL;

	struct Data *prt = _head;

	int i = 0;
	int IsValus = 0;
	while (prt != NULL){
		i++;
	// if prt->value<x
		if (prt->value < x){

			// i=0; 
			if (BeforeHead == NULL){
				BeforeHead = prt;
				BeforeTail = BeforeHead;
			}
			// i>0
			else {
				BeforeTail->next = prt;
				BeforeTail = prt;
				struct Data *Temp = BeforeTail;
				 IsValus = Temp->value;
			}

		}
	
	
	//if prt->value>x OR else 
		else{
		
		}



		prt = prt->next;
	
	}
		if (AfterHead == NULL)
		return BeforeHead;

	// merge
	BeforeTail->next = AfterHead;
	return BeforeTail;
	 


};


int Aolution22(){

	struct Data *_head = CreateAHeader();

	Add(3, _head);
	Add(2, _head);
	Add(8, _head);
	Add(5, _head);
	Add(2, _head);
	Add(1, _head);
	Add(7, _head);
	struct Data *FindKthNode = FindKth(7, _head);
	struct Data *F2 = KthIteration(7, _head);
	DeleteMiddle(F2);

	struct Data *PartitionedList = PartitionList(_head, 4);
	return 0;
}