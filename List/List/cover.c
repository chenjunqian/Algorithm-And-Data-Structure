//
//  cover.c
//  List
//
//  Created by BigHead_Chen on 3/7/16.
//  Copyright © 2016 Eason. All rights reserved.
//

#include "cover.h"

/**
 *  members 是待覆盖的集合,subsets 是目标集合中的子集,covering 是作为返回的覆盖集
 */
int cover(Set *members, Set *subsets , Set *covering){
    Set intersection;
    KSet *subset;
    ListElmt *member,*max_member;
    void *data;
    int max_size;
    /*初始化 convering 集合*/
    set_init(covering, subsets->match, NULL);
    
    
    while (set_size(members)>0 && set_size(subsets)>0) {
        max_size = 0;
        
        /*从subsets中找出能够覆盖到members的最大交集*/
        for (member = list_head(subsets); member!=NULL; member = list_next(member)) {
            /**/
            if (set_insersection(&intersection, &((KSet *)list_data(member))->set, members)!=0) {
                return -1;
            }
            
            if (set_size(&intersection)>max_size) {
                max_member = member;
                max_size = set_size(&intersection);
            }
            
            /**/
            set_destroy(&intersection);
        }
        
        if (max_size==0) {
            return 1;
        }
        
        subset = (KSet *)list_data(max_member);
        
        /*将找出的集合加到covering集合中*/
        if (set_insert(covering, subset)!=0) {
            return -1;
        }
        
        /*移除已经加到covering集合中的成员，节省下次迭代判断的时间*/
        for (member = list_head(&((KSet *)list_data(max_member))->set); member!=NULL; member = list_next(member)) {
            data = list_data(member);
            if (set_remove(members, (void**)&data) == 0 && members->destroy !=NULL) {
                members->destroy(data);
            }
        }
        
        if (set_remove(subsets, (void**)&subset)!=0) {
            return -1;
        }
    }
    
    if (set_size(members)>0) {
        return -1;
    }
    
    return 0;
}