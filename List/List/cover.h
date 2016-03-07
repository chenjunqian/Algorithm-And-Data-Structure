//
//  cover.h
//  List
//
//  Created by BigHead_Chen on 3/7/16.
//  Copyright © 2016 Eason. All rights reserved.
//

#ifndef cover_h
#define cover_h

#include <stdio.h>
#include "set.h"

/*定义一个结构，由Key来标识子集合*/
typedef struct KSet_{
    void *Key;
    Set set;
}KSet;

int cover(Set *members, Set *subsets , Set *covering);

#endif /* cover_h */
