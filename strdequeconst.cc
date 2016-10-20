#include <iostream>
#include "cstrdeque"
#include "strdequeconst.h"
#include "cstrdequeconst"

unsigned long jnp1::emptystrdeque()
{
	static long emptyStrdequeId = jnp1::strdeque_new();

	return emptyStrdequeId;
}

unsigned long emptystrdeque()
{
	return jnp1::emptystrdeque();
}