//
//  bistree.c
//  List
//
//  Created by BigHead_Chen on 4/13/16.
//  Copyright © 2016 Eason. All rights reserved.
//

#include "bistree.h"
#include <stdlib.h>
#include <string.h>

static Node* createBisTreeNode(Type key,Node *parent,Node *left,Node *right){
    Node *newNode;
    
    if ((newNode = (Node *)malloc(sizeof(Node)))==NULL) {
        return NULL;
    }
    
    newNode->key = key;
    newNode->parentNode = parent;
    newNode->leftNode = left;
    newNode->rightNode = right;
    
    return newNode;
}

/*
 *Insert a node into a tree
 */
static Node* insertBisTreeNode(BisTree tree,Node *newNode){
    Node *parent = NULL;
    Node *tempTree = tree;
    
    //find a postion for newNode
    while (tempTree!=NULL) {
        parent = tree;//store the parent
        if (newNode->key<tempTree->key) {
            tempTree = tempTree->leftNode;
        }else{
            tempTree = tempTree->rightNode;
        }
    }
    
    newNode->parentNode = parent;
    if (tempTree==NULL) {
        tempTree = newNode;
    }else if (newNode->key<parent->key) {
        parent->leftNode = newNode;
    }else{
        parent->rightNode = newNode;
    }
    
    return tempTree;
}

Node* insertBisTreeNodeWithKey(BisTree tree,Type key){
    Node *newNode;
    
    if ((newNode = createBisTreeNode(key, NULL, NULL, NULL))==NULL) {
        return tree;
    }
    
    return insertBisTreeNode(tree, newNode);
}

void preOrderBisTree(BisTree tree){
    
    if (tree!=NULL) {
        printf("%d",tree->key);
        preOrderBisTree(tree->leftNode);
        preOrderBisTree(tree->rightNode);
    }
}

void inOrderBisTree(BisTree tree){
    if (tree!=NULL) {
        inOrderBisTree(tree->leftNode);
        printf("%d",tree->key);
        inOrderBisTree(tree->rightNode);
    }
}

void postOrderBisTree(BisTree tree){
    if (tree!=NULL) {
        postOrderBisTree(tree->rightNode);
        postOrderBisTree(tree->leftNode);
        printf("%d",tree->key);
    }
}

Node* SearchBisTree(BisTree tree,Type key){
    
    if (tree == NULL || tree->key==key) {
        return tree;
    }
    
    if (key<tree->key) {
        return SearchBisTree(tree->leftNode, key);
    }else{
        return SearchBisTree(tree->rightNode, key);
    }
    
}

Node* BisTreeMinimun(BisTree tree){
    if (tree==NULL) {
        return NULL;
    }
    
    while (tree->leftNode !=NULL) {
        tree = tree->leftNode;
    }
    
    return tree;
}

Node* BisTreeMax(BisTree tree){
    if (tree==NULL) {
        return NULL;
    }
    
    while (tree->leftNode !=NULL) {
        tree = tree->rightNode;
    }
    
    return tree;
}

/*find a node whitch is the minimun in the nodes but bigger than target node*/
Node* bisTreeSuccesor(Node *targetNode){
    
    //if target node has right child , than find the minumun node in the right branch
    if (targetNode->rightNode!=NULL) {
        return BisTreeMinimun(targetNode);
    }
    
    //if target node has no right child
    //1) target node is its parent's left child , then the node whitch we find is its parent
    //2) target node is its parent's right child , find the target node's lowest parent node and the lowest parent node has left child
    Node *parent = targetNode->parentNode;
    while ((parent!=NULL)&&(targetNode = parent->rightNode)) {
        targetNode = parent;
        parent = parent->parentNode;
    }
    
    return parent;
}

Node* bisTreePredecessor(Node *targetNode){
    
    if (targetNode->leftNode!=NULL) {
        return BisTreeMax(targetNode);
    }
    
    Node *parent = targetNode->parentNode;
    if ((parent!=NULL)&&(targetNode = parent->leftNode)) {
        targetNode = parent;
        parent = parent->parentNode;
    }
    
    return parent;
}

static Node* bisTreeDelete(BisTree tree, Node *targetNode){
    
    Node *x = NULL;
    Node *y = NULL;
    
    if (targetNode->leftNode == NULL || targetNode->rightNode == NULL) {
        y = targetNode;
    }else{
        y = bisTreeSuccesor(targetNode);
    }
    
    if (y->leftNode!=NULL) {
        x = y->leftNode;
    }else{
        x = y->rightNode;
    }
    
    if (x != NULL) {
        x->parentNode = y->parentNode;
    }
    
    if (y->parentNode == NULL) {
        tree = x;
    }else if (y == y->parentNode->leftNode) {
        y->parentNode->leftNode = x;
    }else{
        y->parentNode->rightNode = x;
    }
    
    if (y!=targetNode) {
        targetNode->key = y->key;
    }
    
    if (y!=NULL) {
        free(y);
    }
    
    return tree;
}

Node* deleteBistree(BisTree tree,Type key){
    
    Node *tempNode;
    
    if ((tempNode = SearchBisTree(tree, key))!=NULL) {
        tree = bisTreeDelete(tree, tempNode);
    }
    
    return tree;
}

void destroyTree(BisTree tree){
    if (tree == NULL) {
        return;
    }
    
    if (tree->leftNode !=NULL) {
        destroyTree(tree->leftNode);
    }
    
    if (tree->rightNode !=NULL) {
        destroyTree(tree->rightNode);
    }
    
    free(tree);
}

/*
    location = 0 -> node is root 
    location = 1 -> node is right child
    location = -1 -> node is left child
 */
void printBisTree(BisTree tree, Type key,int location){
    if (tree!=NULL) {
        if (location == 0) {
            printf("%2d is root \n",tree->key);
        }else{
            printf("%2d is %2d's %6s child \n ",tree->key,key,location == 1?"right":"left");
        }
        
        printBisTree(tree->leftNode, tree->key, -1);
        printBisTree(tree->rightNode, tree->key, 1);
    }
}


