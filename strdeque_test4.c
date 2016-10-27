#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "strdeque.h"
#include "strdequeconst.h"

int main()
{
    unsigned long deq;
    char buf[4] = "foo";
    deq = strdeque_new();
    strdeque_insert_at(deq, 0, buf);
    buf[0] = 'b';
    assert(strdeque_get_at(deq, 0) != NULL);
    assert(strncmp(strdeque_get_at(deq, 0), "foo", 4) == 0);
    assert(strncmp(strdeque_get_at(deq, 0), "boo", 4) != 0);
    return 0;
}