#include"stdio.h"

// Data Structure
struct Data{
	int val;
	struct Data* next;
};

struct Data *Append(int val){

	struct Data *newNode = (struct Data*) malloc(sizeof(struct Data));
	newNode->val = val;
	newNode->next = NULL;
	return newNode;

};

// Get  linkedList from a series of digits
// Parsing a long digit to to LinkedList
// using a randomn system to assing values to a linked list. 
struct Data* Parse(int l){

	if (l){
		struct Data* head = (struct Data*) malloc(sizeof(struct Data));
		head->val = 0;
		head->next = NULL;
		struct Data *prt = head;

		while (l){
			prt->next = Append(l);
			prt = prt->next;
			l--;
		}
		prt->next = NULL;
		return head;
	};


	return NULL;
};

// return f(x) -> L1 and L2
// -1 for L1<L2 
// 0 for L1==L2
// 1 for L1>L2
int Fx(struct Data *prtL1 , struct Data* prtL2){
	// Initialize values; 
	int L1 = 0;
	int L2 = 0;
	while (prtL1 != NULL){
		prtL1 = prtL1->next;
		L1++;
	}
	while (prtL2 != NULL){
		prtL2 = prtL2->next;
		L2++;
	}
	if (L1 > L2)
		return 1;
	if (L1 < L2)
		return -1;
	else return 0;
};




void *SolveIt(int Fx, struct Data *prtl1, struct Data *prtl2){
	struct Data *prt = prtl1;
	struct Data *prt2 = prtl2;
	int Add = 0;
	struct Data *Header = (struct Data*) malloc(sizeof(struct Data));
	struct Data * prtH = Header;
	Header->val = 0;
	Header->next = NULL;


	if (!Fx){
		while (prtl1 != NULL){
			int sum = prtl1->val + prtl2->val;
			Header->next = Append((sum + Add));
			if (sum > 10)
				Add = 1;
				Add = 0;
				
				Header = Header->next;
				prtl1 = prtl1->next;
				prtl2 = prtl2->next;
		}

		return prtH;
	}
};



	int Solution25(){

		struct Data* prtl1 = Parse(4);
		struct Data* prtl2 = Parse(4);
		struct Data* total = SolveIt(Fx(prtl1, prtl2), prtl1, prtl2);
		return 0;
	};


