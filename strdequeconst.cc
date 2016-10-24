#include <iostream>
#include "cstrdeque"
#include "strdequeconst.h"
#include "cstrdequeconst"

namespace
{
	// zapytać się jutro co z tym zrobić:
	bool is_debug_mode()
	{
		#ifdef NDEBUG
			return false;
		#else
			return true;
		#endif
	}

	void debug(std::string const& message)
	{
		if (is_debug_mode())
		{
			std::ios_base::Init();
			std::cerr << message << "\n";
		}
	}

}

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