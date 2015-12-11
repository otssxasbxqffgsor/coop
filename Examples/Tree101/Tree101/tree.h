
//  tree.h
//  101Tree
//
//  Created by Kian Davoudi-Rad on 2015-12-11.
//  Copyright © 2015 Kian Davoudi. All rights reserved.
//

#ifndef tree_h
#define tree_h


// This is the data holder for the right and left
typedef struct node{
	int Right;
	int Left;
	char t[10];
	struct node *next;
	struct node *prev;
}Node;

typedef enum { Balanced = 0, Unbalanced = 1 } TreeType;

// Initate a balances Tree
int InitTree(int type, Node *root);

// Find the length of the left branch
int LenTreeLeft(Node *root);

// Find the length of the right branch
int LenTreeRight(Node *root);

#endif /* tree_h */
