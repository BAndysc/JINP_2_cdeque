#include <cassert>
#include <cstdio>
#include <climits>
#include <iostream>
#include "string.h"
#include "cstrdeque"
#include "cstrdequeconst"

int streq(const char* s1, const char* s2, size_t len) {
    if (s1 == s2)
        return 1;

    if (s1 == NULL || s2 == NULL)
        return 0;

    return strncmp(s1, s2, len) == 0;
}

int main() {
    unsigned long d1, d2, d3;

    d1 = jnp1::strdeque_new();

    jnp1::strdeque_insert_at(d1, 0, "a");
    assert(streq(jnp1::strdeque_get_at(d1, 0), "a", 2));

    jnp1::strdeque_insert_at(d1, 8, "aa");
    assert(streq(jnp1::strdeque_get_at(d1, 1), "aa", 3));

    jnp1::strdeque_remove_at(d1, 1);
    assert(jnp1::strdeque_get_at(d1, 1) == NULL);
    assert(streq(jnp1::strdeque_get_at(d1, 0), "a", 2));

    jnp1::strdeque_insert_at(d1, 0, NULL);
    assert(streq(jnp1::strdeque_get_at(d1, 0), "a", 2));
    assert(jnp1::strdeque_size(d1) == 1);

    jnp1::strdeque_remove_at(d1, 1);
    assert(jnp1::strdeque_size(d1) == 1);

    jnp1::strdeque_delete(d1);
    jnp1::strdeque_insert_at(d1, 0, "b");
    assert(jnp1::strdeque_size(d1) == 0);
    assert(jnp1::strdeque_get_at(d1, 0) == NULL);

    d2 = jnp1::strdeque_new();
    d3 = jnp1::strdeque_new();
    jnp1::strdeque_insert_at(d2, 0, "c");
    jnp1::strdeque_insert_at(d2, 0, "cc");
    jnp1::strdeque_insert_at(d2, 0, "ccc");
    jnp1::strdeque_insert_at(d3, 100, "ccc");
    jnp1::strdeque_insert_at(d3, 1000, "cc");
    jnp1::strdeque_insert_at(d3, 10000, "c");
    assert(jnp1::strdeque_comp(d2, d3) == 0);

    jnp1::strdeque_remove_at(d2, 0);
    assert(jnp1::strdeque_comp(d2, d3) == -1);

    jnp1::strdeque_delete(d3);
    assert(jnp1::strdeque_comp(d2, d3) == 1);

    jnp1::strdeque_delete(d2);
    assert(jnp1::strdeque_comp(d2, d3) == 0);
    assert(jnp1::strdeque_comp(d2, jnp1::emptystrdeque()) == 0);
    assert(jnp1::strdeque_comp(jnp1::emptystrdeque(), d3) == 0);
    assert(jnp1::strdeque_comp(jnp1::emptystrdeque(), jnp1::emptystrdeque()) == 0);

    assert(jnp1::strdeque_size(jnp1::emptystrdeque()) == 0);

    jnp1::strdeque_delete(jnp1::emptystrdeque());
    jnp1::strdeque_insert_at(jnp1::emptystrdeque(), 0, "d");
    assert(jnp1::strdeque_size(jnp1::emptystrdeque()) == 0);

    jnp1::strdeque_insert_at(jnp1::emptystrdeque(), 0, "d");
    jnp1::strdeque_insert_at(jnp1::emptystrdeque(), 0, "dd");
    assert(jnp1::strdeque_get_at(jnp1::emptystrdeque(), 0) == NULL);

    jnp1::strdeque_remove_at(jnp1::emptystrdeque(), 0);
    assert(jnp1::strdeque_size(jnp1::emptystrdeque()) == 0);

    jnp1::strdeque_clear(jnp1::emptystrdeque());

    //std::cout << emptystrdeque();

    return 0;
}
