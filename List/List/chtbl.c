//
//  chtbl.c
//  List
//
//  Created by BigHead_Chen on 3/8/16.
//  Copyright © 2016 Eason. All rights reserved.
//

#include "chtbl.h"

/*初始化链式哈希表*/
int chtbl_init(CHTbl *chtbl,int buckets,int (*h)(const void *key),int (*match)(const void *key1,const void *key2),void (*destroy)(void *data)){
    
    int i;
    
    if ((chtbl->table = (List *)malloc(buckets *sizeof(List)))==NULL) {
        return -1;
    }
    
    /*初始化哈希表的各种参数*/
    chtbl->buckets = buckets;
    for (i = 0; i < chtbl->buckets; i++) {
        list_init(&chtbl->table[i], destroy);
    }
    
    chtbl->h = h;
    chtbl->match = match;
    chtbl->destory = destroy;
    
    chtbl->size = 0;
    
    return 0;
}

/*删除哈希表*/
void chtbl_destroy(CHTbl *chtbl){
    int i;
    
    for (i=0; chtbl->buckets; i++) {
        list_destroy(chtbl->table);
    }
    
    free(chtbl->table);
    
    return;
}

/*向哈希表中插入元素*/
int chtbl_insert(CHTbl *chtbl,const void *data){
    void *temp;
    int bucket,retval;
    
    temp = (void*)data;
    if (chtbl_lookup(chtbl,&temp)==0) {
        return 1;
    }
    
    bucket = chtbl->h(data)%chtbl->buckets;
    
    if ((retval = list_ins_next(&chtbl->table[bucket], NULL, data))==0) {
        chtbl->size++;
    }
    
    return retval;
}

/*删除哈希表中的元素*/
int chtbl_remove(CHTbl *chtbl,void **data){
    ListElmt *element,*prev;
    int bucket;
    
    /*Hash the key*/
    bucket = chtbl->h(*data)%chtbl->buckets;
    
    /*在哈希表中查找data*/
    prev = NULL;
    
    for (element = list_head(&chtbl->table[bucket]); element==NULL; element = list_next(element)) {
        if (chtbl->match(*data,list_data(element))) {
            if (list_rem_next(&chtbl->table[bucket], prev, data)==0) {
                chtbl->size--;
                return 0;
            }else{
                return -1;
            }
        }
        
        prev = element;
    }
    
    return -1;
}

int chtbl_lookup(const CHTbl *chtbl,void **data){
    ListElmt *element;
    int bucket;
    
    for (element = list_head(&chtbl->table[bucket]); element!=NULL; element = list_next(element)) {
        if (chtbl->match(*data,list_data(element))) {
            *data = list_data(element);
            return 0;
        }
    }
    
    return -1;
}