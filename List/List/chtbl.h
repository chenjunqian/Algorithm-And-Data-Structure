//
//  chtbl.h
//  List
//
//  Created by BigHead_Chen on 3/8/16.
//  Copyright © 2016 Eason. All rights reserved.
//

#ifndef chtbl_h
#define chtbl_h

#include <stdio.h>
#include "list.h"

typedef struct CHTbl_{
    int buckets;
    
    int (*h)(const void *key1);
    int (*match)(const void *key1,const void *key2);
    void (*destory)(void *data);
    
    int size;
    List *table;
    
}CHTbl;

int chtbl_init(CHTbl *chtbl,int buckets,int (*h)(const void *key),int (*match)(const void *key1,const void *key2),void (*destroy)(void *data));
void chtbl_destroy(CHTbl *chtbl);

#endif /* chtbl_h */
