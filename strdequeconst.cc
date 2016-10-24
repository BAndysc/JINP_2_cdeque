#include <iostream>
#include "cstrdeque"
#include "strdequeconst.h"
#include "cstrdequeconst"

// zaimplementowane w strdeque.cc
bool is_debug_mode();
void debug(std::string const& message);

unsigned long jnp1::emptystrdeque()
{
	static long emptyStrdequeId = jnp1::strdeque_new();
	
	debug("emptystrdeque()");

	return emptyStrdequeId;
}

unsigned long emptystrdeque()
{
	return jnp1::emptystrdeque();
}