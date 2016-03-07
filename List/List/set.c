//
//  set.c
//  List
//
//  Created by BigHead_Chen on 2/17/16.
//  Copyright © 2016 Eason. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "set.h"

//集合相关的计算

void set_init(Set *set,int (*match)(const void *key1,const void *key2),void (*destroy)(void *data)){
    list_init(set, destroy);
    set->match = match;
    return;
}

int set_insert(Set *set,const void *data){
    if (set_is_mumber(set, data)) {
        return 1;
    }
    
    return list_ins_next(set, list_tail(set), data);
}

int set_remove(Set *set,void **data){
    ListElmt *member, *prev;
    
    prev = NULL;
    
    for (member = list_head(set); member!=NULL; member = list_next(member)) {
        if (set->match(*data,list_data(member))) {
            break;
        }
        
        prev = member;
    }
    
    if (member == NULL) {
        return -1;
    }
    
    return list_rem_next(set, prev, data);
}

/*得到集合的并集*/
int set_union(Set *setu,const Set *set1,const Set *set2){
    ListElmt *member;
    void *data;
    
    /*初始化目标集合setu*/
    set_init(setu, set1->match, NULL);
    
    /*讲集合set1插入到目标集合setu*/
    for (member = list_head(set1); member !=NULL; member = list_next(member)) {
        data = list_data(member);
        if (list_ins_next(setu, list_tail(setu), data)!=0) {
            set_destroy(setu);
            return -1;
        }
    }
    
    /*讲集合set2中和集合set1中不重合的元素插入目标集合setu中*/
    for (member = list_head(set2); member !=NULL; member = list_next(member)) {
        if (set_is_mumber(set1, list_data(member))) {
            continue;
        }else{
            data = list_data(member);
            
            if (list_ins_next(setu, list_tail(setu), data)!=0) {
                set_destroy(setu);
                return -1;
            }
        }
    }
    
    return 0;
}

/*得到集合的交集*/
int set_intersection(Set *seti,const Set *set1,const Set *set2){
    ListElmt *member;
    void *data;
    
    /*初始化目标集合Set*/
    set_init(seti, set1->match, NULL);
    
    /*插入集合set1和集合set2都有的成员*/
    for (member = list_head(set1); member !=NULL; member = list_next(member)) {
        if (set_is_mumber(set2, list_data(member))) {
            data = list_data(member);
            if (list_ins_next(seti, list_tail(seti), data)!=0) {
                set_destroy(seti);
                return -1;
            }
        }
    }
    
    return 0;
}

int set_difference(Set *setd,const Set *set1,const Set *set2){
    ListElmt *member;
    void *data;
    
    /*初始化目标集合Set*/
    set_init(setd, set1->match, NULL);
    
    /*从set1插入成员member不属于set2的 */
    for (member = list_head(set1); member !=NULL; member = list_next(member)) {
        if (!set_is_mumber(set2, list_data(member))) {
            data = list_data(member);
            
            if (list_ins_next(setd, list_tail(setd), data) !=0) {
                set_destroy(setd);
                return -1;
            }
        }
    }
    
    return 0;
}

int set_is_mumber(const Set *set,const void *data){
    ListElmt *member;
    
    /*检测 data 是否是 set 中的元素*/
    for (member = list_head(set); member !=NULL; member = list_next(member)) {
        if (set->match(data,list_data(member))) {
            return 1;
        }
    }
    
    return 0;
}

/*检测是否是子集*/
int set_is_subset(const Set *set1,const Set *set2){
    ListElmt *member;
    
    if (set_size(set1)>set_size(set2)) {
        return 0;
    }
    
    /*检测set1 是否是 set2 的子集*/
    for (member = list_head(set1); member !=NULL; member = list_next(member)) {
        if (!set_is_mumber(set2, list_data(member))) {
            return 0;
        }
    }
    
    return 1;
}

int set_is_equal(const Set *set1,const Set *set2){
    
    if (set_size(set1) != set_size(set2)) {
        return 0;
    }
    
    return set_is_subset(set1, set2);
}