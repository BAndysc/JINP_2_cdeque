#include <iostream>
#include "cstrdeque"
#include "cstrdequeconst"

namespace
{
	namespace DebugStrings
	{
		const char* Empty = "emptystrdeque()";
	}

	typedef unsigned long StrDequeMapKey;

	inline bool is_debug_mode()
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

namespace jnp1 
{
	StrDequeMapKey emptystrdeque()
	{
		static const StrDequeMapKey emptyStrdequeId = jnp1::strdeque_new();
		
		debug(DebugStrings::Empty);

		return emptyStrdequeId;
	}
}
