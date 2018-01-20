//
//  hashtable2_algrithm.c
//  kvo
//
//

#include "hashtable2_algrithm.h"
#include <assert.h>

void foreach(NXHashTable *table, void (^body)(id)) {
    assert(table);
    int count = 0;
    __auto_type buf = (void *)nil;
    __auto_type iterator = NXInitHashState(table);
    while (NXNextHashState(table, &iterator, &buf)) {
        !body ?: body(buf);
        count++;
    }
}
