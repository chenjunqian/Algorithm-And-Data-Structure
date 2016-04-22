//
//  bistree.h
//  List
//
//  Created by BigHead_Chen on 4/13/16.
//  Copyright © 2016 Eason. All rights reserved.
//

#ifndef bistree_h
#define bistree_h

#include <stdio.h>
#include "bitree.h"

typedef int Type;

typedef struct BisTreeNode{
    Type key;//The value of the node
    struct BisTreeNode *leftNode;
    struct BisTreeNode *rightNode;
    struct BisTreeNode *parentNode;
}Node,*BisTree;

void preOrderBisTree(BisTree tree);
void inOrderBisTree(BisTree tree);
void postOrderBisTree(BisTree tree);

Node* SearchBisTree(BisTree tree,Type key);
Node* BisTreeMinimun(BisTree tree);
Node* BisTreeMax(BisTree tree);
Node* insertBisTreeNodeWithKey(BisTree tree,Type key);
Node* BisTreeMinimun(BisTree tree);
Node* BisTreeMax(BisTree tree);
Node* bisTreeSuccesor(Node *targetNode);
Node* bisTreePredecessor(Node *targetNode);
Node* deleteBistree(BisTree tree,Type key);
void destroyTree(BisTree tree);
void printBisTree(BisTree tree, Type key,int location);
#endif /* bistree_h */
