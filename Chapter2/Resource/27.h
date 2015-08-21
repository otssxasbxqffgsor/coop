#include "stdlib.h"
#include "stdio.h"

struct Data{
	int value;
	struct Data* next;
};

int Append(int val, struct Data* head){

	struct Data* prt = head;

	if ( head != NULL){
		struct Data* node = (struct Data*) malloc(sizeof(struct Data));
		node->value = val;
		node->next = NULL;
			while (prt->next != NULL)
				prt = prt->next;
		prt->next = node;

		return 1;

	}
	return 0;

};




// find Max
struct Data* FindMax(struct Data* head){
	struct Data *prt = head;
	struct Data *max = (struct Data*) malloc(sizeof(struct Data));
	max->value = 0;
	max ->next = NULL;

	while (prt->next != NULL){
		if (prt->value > max->value)
			max = prt;
		prt = prt->next;
	}

	if (max != NULL)
		return max;

	return NULL;

};

int ChekPandolimon(struct Data *L1, struct Data *L2){

	struct Data* prt1 = L1;
	struct Data* prt2 = L2;

	while (prt1->next != NULL || prt2->next != NULL)
	{

		if (prt1->value == prt2->value)
		{
			prt1 = prt1->next;
			prt2 = prt2->next;
		}
		else return 0;

	}
	return 1;

}


	struct Data* Reverse(struct Data *head){

		struct Data* prt = head;
		struct Data* TempHead = head;
		while (TempHead->next != head){
			// iterate through the linked list
			while (prt->next != NULL)
				prt = prt->next;

			prt->next = TempHead;
			TempHead = TempHead->next;
			prt->next->next = NULL;
			prt = TempHead;
		}
		return TempHead->next;

};


int Solution27(){

	struct Data* head = (struct Data*) malloc(sizeof(struct Data));

	head->value = 0;
	head->next = NULL;

	Append(1, head);
	Append(3, head);
	Append(2, head);
	Append(1, head);
	Append(0, head);



	
	//int r = CheIfPanidlomn(head, FindMax(head));
	struct Data* NewHead = Reverse(head);
	
	int r = ChekPandolimon(NewHead, head);
	
	return 0;
};

