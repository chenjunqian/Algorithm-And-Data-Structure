//
//  bitree.c
//  List
//  二叉树的实现和分析
//  Created by BigHead_Chen on 3/10/16.
//  Copyright © 2016 Eason. All rights reserved.
//

#include "bitree.h"
#include <stdlib.h>
#include <string.h>

/*初始化二叉树
 *只需要将树的成员size 设为0，根节点设为null，destroy成员设为相应的析构函数即可
 *该方法的时间复杂度为O(0)，因为所以的初始化过程能够在恒定的时间内完成
 */
void bitree_init(BiTree *tree,void (*destroy)(void *data)){
    tree->size = 0;
    tree->root = NULL;
    tree->destroy = destroy;
}

/*删除二叉树
 *主要是将二叉树中所有的子节点都移除，时间复杂度为O(n),这里的n为二叉树中的节点数，因为调用的bitree_rem_left的负责度为O(0)。
 */
void bitree_destroy(BiTree *tree){
    bitree_rem_left(tree, NULL);
    
    memset(tree, 0, sizeof(BiTree));
    return;
}

/*插入二叉树左节点
 *实现方法：将新节点的数据域指向调用者传入的数据，通过将节点node的left指针指向待插入的新节点来实现连接,如果传入的node为null，且树为空，则将树的root成员设置为新的节点
 *时间复杂度为O(0)因为插入的过程能在恒定的时间内完成
 */
int bitree_ins_left(BiTree *tree,BiTreeNode *node,const void *data){
    
    BiTreeNode *new_node , **position;
    
    /*判断节点node插入的位置*/
    if (node==NULL) {
        /*如果节点node为空，则插入二叉树的根节点*/
        if (bitree_size(tree)>0) {
            return -1;
        }
        
        position = &tree->root;
    }else{
        /*正常情况下，插入到左分支的末尾*/
        if (bitree_left(node)!=NULL) {
            return -1;
        }
        
        position = &node->left;
    }
    
    if ((new_node = (BiTreeNode*)malloc(sizeof(BiTreeNode)))==NULL) {
        return -1;
    }
    
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = (void *)data;
    /*将新的节点插入二叉树*/
    *position = new_node;
    
    tree->size++;
    
    return 0;
}

/*插入二叉树右节点,原理和上面插入左节点是一样的*/
int bitree_ins_right(BiTree *tree,BiTreeNode *node,const void *data){
    BiTreeNode *new_node , **position;
    
    /*判断节点node插入的位置*/
    if (node==NULL) {
        /*如果节点node为空，则插入二叉树的根节点*/
        if (bitree_size(tree)>0) {
            return -1;
        }
        
        position = &tree->root;
    }else{
        /*正常情况下，插入到左分支的末尾*/
        if (bitree_left(node)!=NULL) {
            return -1;
        }
        
        position = &node->right;
    }
    
    if ((new_node = (BiTreeNode*)malloc(sizeof(BiTreeNode)))==NULL) {
        return -1;
    }
    
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = (void *)data;
    /*将新的节点插入二叉树*/
    *position = new_node;
    
    tree->size++;
    return 0;
}

/*删除节点的左节点
 *将以指定的节点的左子节点为根的子树移除，移除顺序按照后序遍历从参数node的左子节点开始依次移除，然后在移除右子节点,如果node为null，就从树的根节点root开始。
 *时间复杂度为O(n)因为这是根据指定节点的子节点数决定的，需要遍历整个指定节点。
 */
int bitree_rem_left(BiTree *tree,BiTreeNode *node){
    BiTreeNode **position;
    
    if (bitree_size(tree)==0) {
        return -1;
    }
    
    if (node==NULL) {
        position = &tree->root;
    }else{
        position = &node->left;
    }
    
    if (*position!=NULL) {
        /*判断需要删除节点的位置*/
        bitree_rem_left(tree,*position);
        bitree_rem_right(tree,*position);
        
        if (tree->destroy!=NULL) {
            tree->destroy((*position)->data);
        }
        
        free(*position);
        *position = NULL;
        
        tree->size--;
    }
    
    return 0;
}

/*删除节点的右节点，原理与上述删除左节点相似*/
int bitree_rem_right(BiTree *tree,BiTreeNode *node){
    BiTreeNode **position;
    
    if (bitree_size(tree)==0) {
        return -1;
    }
    
    /*判断需要删除节点的位置*/
    if (node==NULL) {
        position = &tree->root;
    }else{
        position = &node->right;
    }
    
    if (*position!=NULL) {
        /*删除目标节点的左右节点*/
        bitree_rem_left(tree,*position);
        bitree_rem_right(tree,*position);
        
        if (tree->destroy!=NULL) {
            tree->destroy((*position)->data);
        }
        
        free(*position);
        *position = NULL;
        
        tree->size--;
    }
    
    return 0;
}

/*合并两个二叉树
 *先初始化一个新的二叉树merge，然后将data插入合并后的树中作为它的根节点，使用bitree_ins_left（或者bitree_ins_right）方法实现，
 *然后将分别调用者传入的左右两个二叉树设为merge的根节点root的左右节点，最后解除原来树种的节点关系，并将两个树的size成员设为0
 *时间复杂度O(0)，因为所有的操作能在恒定的时间内完成。
 */
int bitree_merge(BiTree *merge,BiTree *left,BiTree *right,const void *data){
    
    bitree_init(merge, left->destroy);
    
    if (bitree_ins_left(merge, NULL, data)!=0) {
        bitree_destroy(merge);
        return -1;
    }
    
    bitree_root(merge)->left= bitree_root(left);
    bitree_root(merge)->right= bitree_root(right);
    
    merge->size = merge->size + bitree_size(left) + bitree_size(right);
    
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;
    
    return 0;
}






