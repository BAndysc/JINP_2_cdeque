#include <iostream>
#include <deque>
#include <unordered_map>
#include "strdeque.h"
#include "cstrdeque"

namespace
{
	const unsigned int EMPTY_STRDEQUE_ID = 0;
	unsigned long lastAddedId = EMPTY_STRDEQUE_ID;

	typedef std::deque<std::string> Strdeque;
	typedef std::unordered_map<unsigned long, Strdeque> StrDequeMap;

	Strdeque& get_empty_strdeque()
	{
		static Strdeque empty;
		return empty;
	}

	StrDequeMap& get_str_deque_map()
	{
		static StrDequeMap str_deque_map({{ EMPTY_STRDEQUE_ID, get_empty_strdeque() }});
		return str_deque_map;
	}

	bool strdeque_exists(unsigned long id)
	{
		return get_str_deque_map().count(id) > 0;
	}

	Strdeque& strdeque_get_from_id_or_empty(unsigned long id)
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
}

namespace jnp1
{
	unsigned long strdeque_new()
	{
		std::cout << "DEBUG strdeque_new()\n";

		get_str_deque_map()[++lastAddedId] = Strdeque();

		return lastAddedId;
	}

	void strdeque_delete(unsigned long id)
	{
		std::cout << "DEBUG strdeque_delete("<<id<<")\n";

		get_str_deque_map().erase(id);
	}

	size_t strdeque_size(unsigned long id)
	{
		std::cout << "DEBUG strdeque_size("<<id<<")\n";

		if (strdeque_exists(id))
		{
			return get_str_deque_map()[id].size();
		}

		return 0;
	}

	void strdeque_insert_at(unsigned long id, size_t pos, const char* value)
	{
		std::cout << "DEBUG strdeque_insert_at("<<id<<", "<<pos<<", "<<value<<")\n";

		if (value != nullptr && strdeque_exists(id))
		{
			Strdeque& strdeque = get_str_deque_map()[id];

			if (pos < strdeque.size())
			{
				strdeque.insert(strdeque.begin() + pos, value);
			}
			else
			{
				strdeque.push_back(value);
			}
		}
	}

	void strdeque_remove_at(unsigned long id, size_t pos)
	{
		std::cout << "DEBUG strdeque_remove_at("<<id<<", "<<pos<<")\n";

		if (strdeque_exists(id))
		{
			Strdeque& strdeque = get_str_deque_map()[id];

			if (pos < strdeque.size())
			{
				strdeque.erase(strdeque.begin() + pos);
			}
		}
	}

	const char* strdeque_get_at(unsigned long id, size_t pos)
	{
		std::cout << "DEBUG strdeque_get_at("<<id<<", "<<pos<<")\n";

		if (strdeque_exists(id))
		{
			Strdeque& strdeque = get_str_deque_map()[id];

			if (pos < strdeque.size())
			{
				return strdeque[pos].c_str();
			}
		}

		return nullptr;
	}

	void strdeque_clear(unsigned long id)
	{
		std::cout << "DEBUG strdeque_clear("<<id<<")\n";

		if (strdeque_exists(id))
		{
			get_str_deque_map()[id].clear();
		}
	}

	int strdeque_comp(unsigned long id1, unsigned long id2)
	{
		std::cout << "DEBUG strdeque_comp("<<id1<<", "<<id2<<")\n";

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

		return compareResult;
	}
}

unsigned long strdeque_new()
{
	return jnp1::strdeque_new();
}

void strdeque_delete(unsigned long id)
{
	jnp1::strdeque_delete(id);
}

size_t strdeque_size(unsigned long id)
{
	return jnp1::strdeque_size(id);
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value)
{
	jnp1::strdeque_insert_at(id, pos, value);
}

void strdeque_remove_at(unsigned long id, size_t pos)
{
	jnp1::strdeque_remove_at(id, pos);
}

const char* strdeque_get_at(unsigned long id, size_t pos)
{
	return jnp1::strdeque_get_at(id, pos);
}

void strdeque_clear(unsigned long id)
{
	jnp1::strdeque_clear(id);
}

int strdeque_comp(unsigned long id1, unsigned long id2)
{
	return jnp1::strdeque_comp(id1, id2);
}
