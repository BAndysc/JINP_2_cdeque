#include <iostream>
#include "cstrdeque"
#include "strdequeconst.h"
#include "cstrdequeconst"

namespace
{
	namespace DebugStrings
	{
		const char* Empty = "emptystrdeque()";
	}

	typedef unsigned long StrDequeMapKey;

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
			static const std::ios_base::Init streamsInit;

			std::cerr << message << "\n";
		}
	}
}


StrDequeMapKey emptystrdeque()
{
	static const StrDequeMapKey emptyStrdequeId = jnp1::strdeque_new();
	
	debug(DebugStrings::Empty);

	return emptyStrdequeId;
}
