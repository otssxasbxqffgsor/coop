

//
//  three.h
//  101Tree
//
//  Created by Kian Davoudi-Rad on 2015-12-11.
//  Copyright © 2015 Kian Davoudi. All rights reserved.
//
#include "tree.h"

// Initate a balances Tree
int InitTree(int type, Node *_root)
{
	TreeType  *prtR = _root;
	//prtR = (TreeType*)malloc(sizeof(TreeType));

	if (type == Balanced)
	{
		int a = 1;
	//prtR->Right = &a;
		_root->Left = 2;
		strcpy(_root->t, "Kin");


		/*    root->Left = 2;
		root->next = NULL;
		root->prev = NULL;

		for (int i=0;i<11){
		prtR->next = (struct Node*)malloc(sizeof(struct Node));
		prtR->next->Right = i;
		i++;
		prtR=prtR->next;
		}


		return true;
		}

		*/

		return 50;
	}
}

