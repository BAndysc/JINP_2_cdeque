#include <iostream>
#include <deque>
#include <unordered_map>
#include <boost/format.hpp>
#include <cassert>
#include "cstrdequeconst"
#include "strdeque.h"
#include "cstrdeque"

namespace
{
	typedef unsigned long StrDequeMapKey;
	typedef std::deque<std::string> Strdeque;
	typedef std::unordered_map<StrDequeMapKey, Strdeque> StrDequeMap;

	StrDequeMapKey nextIdToUse = 0;

	StrDequeMap& get_str_deque_map()
	{
		static StrDequeMap strDequeMap;

		return strDequeMap;
	}

	Strdeque& get_empty_strdeque()
	{
		static Strdeque& empty = get_str_deque_map()[jnp1::emptystrdeque()];

		return empty;
	}

	bool strdeque_is_empty(StrDequeMapKey id)
	{
		return id == jnp1::emptystrdeque();
	}

	bool strdeque_exists(StrDequeMapKey id)
	{
		return get_str_deque_map().count(id) > 0;
	}

	Strdeque& strdeque_get_from_id_or_empty(StrDequeMapKey id)
	{
		if (strdeque_exists(id))
		{
			return get_str_deque_map()[id];
		}
		else
		{
			return get_empty_strdeque();
		}
	}

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

	std::string deque_to_string(StrDequeMapKey key)
	{
		static const std::string theEmptyDequeue = "the Empty Deque";

		if (key == jnp1::emptystrdeque())
			return theEmptyDequeue;

		return std::to_string(key);
	}
}

namespace jnp1
{
	StrDequeMapKey strdeque_new()
	{
		debug("strdeque_new()");

		assert(nextIdToUse < std::numeric_limits<StrDequeMapKey>::max());

		StrDequeMapKey key = nextIdToUse++;

		get_str_deque_map()[key] = Strdeque();

		debug((boost::format("strdeque_new: deque %1% created") % key).str());

		return key;
	}

	void strdeque_delete(StrDequeMapKey id)
	{
		debug((boost::format("strdeque_delete(%1%)") % deque_to_string(id)).str());

		StrDequeMap::iterator itr = get_str_deque_map().find(id);

		if (itr == get_str_deque_map().end())
		{
			debug((boost::format("strdeque_delete: deque %1% doesn't exist") % id).str());
		}
		else if (strdeque_is_empty(id))
		{
			debug("strdeque_delete: trying to delete empty dequeue");
		}
		else
		{
			get_str_deque_map().erase(itr);
		}
	}

	size_t strdeque_size(StrDequeMapKey id)
	{
		debug((boost::format("strdeque_size(%1%)") % deque_to_string(id)).str());

		StrDequeMap::iterator itr = get_str_deque_map().find(id);

		if (itr != get_str_deque_map().end())
		{
			return itr->second.size();
		}
		else
		{
			debug((boost::format("strdeque_size: deque %1% does not exist") % id).str());
		}

		return 0;
	}

	void strdeque_insert_at(StrDequeMapKey id, size_t pos, const char* value)
	{
		debug((boost::format("strdeque_insert_at(%1%, %2%, \"%3%\")") % deque_to_string(id) % pos % value).str());

		if (value == nullptr)
		{
			debug("strdeque_insert_at: attempt to insert NULL into a deque");
		}
		else if (strdeque_is_empty(id))
		{
			debug("strdeque_insert_at: attempt to insert into the Empty Deque");
		}
		else
		{
			StrDequeMap::iterator itr = get_str_deque_map().find(id);

			if (itr == get_str_deque_map().end())
			{
				debug((boost::format("strdeque_insert_at: deque %1% does not exist") % id).str());
			}
			else
			{
				Strdeque& strdeque = itr->second;

				if (pos < strdeque.size())
				{
					strdeque.insert(strdeque.begin() + pos, value);
				}
				else
				{
					strdeque.push_back(value);
					pos = strdeque.size();
				}
				debug((boost::format("strdeque_insert_at: deque %1%, element \"%2%\" inserted at %3%") % id % value % pos).str());
			}
		}
	}

	void strdeque_remove_at(StrDequeMapKey id, size_t pos)
	{
		debug((boost::format("strdeque_remove_at(%1%, %2%)") % deque_to_string(id) % pos).str());

		StrDequeMap::iterator itr = get_str_deque_map().find(id);

		if (strdeque_is_empty(id))
		{
			debug("strdeque_remove_at: attempt to remove from the Empty Deque");
		}
		else if (itr == get_str_deque_map().end())
		{
			debug((boost::format("strdeque_remove_at: deque %1% does not exist") % id).str());
		}
		else
		{
			Strdeque& strdeque = itr->second;

			if (pos < strdeque.size())
			{
				strdeque.erase(strdeque.begin() + pos);
				debug((boost::format("strdeque_remove_at: deque %1% element at %2% removed") % id % pos).str());
			}
			else
			{
				debug((boost::format("strdeque_remove_at: deque %1% does not contain an element at %2%") % id % pos).str());
			}
		}
	}

	const char* strdeque_get_at(StrDequeMapKey id, size_t pos)
	{
		debug((boost::format("strdeque_get_at(%1%, %2%)") % deque_to_string(id) % pos).str());

		StrDequeMap::iterator itr = get_str_deque_map().find(id);

		if (itr == get_str_deque_map().end())
		{
			debug((boost::format("strdeque_get_at: deque %1% does not exist") % id).str());
		}
		else
		{
			Strdeque& strdeque = itr->second;

			if (pos < strdeque.size())
			{
				debug((boost::format("strdeque_get_at: deque %1%, element at %2% is \"%3%\"") % id % pos % strdeque[pos]).str());
				return strdeque[pos].c_str();
			}
			else
			{
				debug((boost::format("strdeque_get_at: deque %1% does not contain an element at %2%") % deque_to_string(id) % pos).str());
			}
		}

		return nullptr;
	}

	void strdeque_clear(StrDequeMapKey id)
	{
		debug((boost::format("strdeque_clear(%1%)") % deque_to_string(id)).str());

		StrDequeMap::iterator itr = get_str_deque_map().find(id);

		if (itr == get_str_deque_map().end())
		{
			debug((boost::format("strdeque_clear: deque %1% does not exist") % id).str());
		}
		else if (strdeque_is_empty(id))
		{
			debug("strdeque_clear: attempt to clear the Empty Deque");
		}
		else
		{
			itr->second.clear();
		}
	}

	int strdeque_comp(StrDequeMapKey id1, StrDequeMapKey id2)
	{
		debug((boost::format("strdeque_comp(%1%, %2%)") % deque_to_string(id1) % deque_to_string(id2)).str());

		Strdeque& strdeque1 = strdeque_get_from_id_or_empty(id1);
		Strdeque& strdeque2 = strdeque_get_from_id_or_empty(id2);

		int compareResult = 0;
		size_t lesserSize = std::min(strdeque1.size(), strdeque2.size());

		for (size_t i = 0; i < lesserSize && compareResult == 0; ++i)
		{
			compareResult = strdeque1[i].compare(strdeque2[i]);
		}

		if (compareResult == 0 && strdeque1.size() != strdeque2.size())
		{
			compareResult = strdeque1.size() < strdeque2.size() ? -1 : 1;
		}
		else if (compareResult < -1)
		{
			compareResult = -1;
		}
		else if (compareResult > 1)
		{
			compareResult = 1;
		}

		debug((boost::format("strdeque_comp: result of comparing deque %1% to deque %2% is %3%") % deque_to_string(id1) % deque_to_string(id2) % compareResult).str());

		return compareResult;
	}
}

StrDequeMapKey strdeque_new()
{
	return jnp1::strdeque_new();
}

void strdeque_delete(StrDequeMapKey id)
{
	jnp1::strdeque_delete(id);
}

size_t strdeque_size(StrDequeMapKey id)
{
	return jnp1::strdeque_size(id);
}

void strdeque_insert_at(StrDequeMapKey id, size_t pos, const char* value)
{
	jnp1::strdeque_insert_at(id, pos, value);
}

void strdeque_remove_at(StrDequeMapKey id, size_t pos)
{
	jnp1::strdeque_remove_at(id, pos);
}

const char* strdeque_get_at(StrDequeMapKey id, size_t pos)
{
	return jnp1::strdeque_get_at(id, pos);
}

void strdeque_clear(StrDequeMapKey id)
{
	jnp1::strdeque_clear(id);
}

int strdeque_comp(StrDequeMapKey id1, StrDequeMapKey id2)
{
	return jnp1::strdeque_comp(id1, id2);
}
