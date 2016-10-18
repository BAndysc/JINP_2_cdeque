#include <iostream>
#include <deque>
#include <unordered_map>
#include "strdeque.h"
#include "cstrdeque"

namespace
{
	const unsigned int EMPTY_STRDEQUE_ID = 0;

	typedef std::deque<std::string> Strdeque;

	static Strdeque emptyStrdeque;

	static std::unordered_map<unsigned long, Strdeque> strdeques({{0, emptyStrdeque}});

	static unsigned long lastAddedId = 0;

	bool strdeque_is_exist(unsigned long id)
	{
		return strdeques.count(id) > 0;
	}

	Strdeque& strdeque_get_from_id_or_empty(unsigned long id)
	{
		if (strdeque_is_exist(id))
		{
			return strdeques[id];
		}
		else
		{
			return emptyStrdeque;
		}
	}
}

namespace jnp1 
{
	unsigned long strdeque_new()
	{
		std::cout << "DEBUG strdeque_new()\n";

		Strdeque newStrdeque;

		lastAddedId++;
		strdeques[lastAddedId] = newStrdeque;

		return lastAddedId;
	}

	void strdeque_delete(unsigned long id)
	{
		std::cout << "DEBUG strdeque_delete("<<id<<")\n";

		strdeques.erase(id);
	}

	size_t strdeque_size(unsigned long id)
	{
		std::cout << "DEBUG strdeque_size("<<id<<")\n";

		if (strdeque_is_exist(id))
		{
			return strdeques[id].size();
		}

		return 0;
	}

	void strdeque_insert_at(unsigned long id, size_t pos, const char* value)
	{
		std::cout << "DEBUG strdeque_insert_at("<<id<<", "<<pos<<", "<<value<<")\n";

		if (strdeque_is_exist(id) && value != nullptr)
		{
			Strdeque& strdeque = strdeques[id];

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

		if (strdeque_is_exist(id))
		{
			Strdeque& strdeque = strdeques.at(id);

			if (pos < strdeque.size())
			{
				strdeque.erase(strdeque.begin() + pos);
			}
		}
	}

	const char* strdeque_get_at(unsigned long id, size_t pos)
	{
		std::cout << "DEBUG strdeque_get_at("<<id<<", "<<pos<<")\n";

		if (strdeque_is_exist(id))
		{
			Strdeque& strdeque = strdeques[id];

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

		if (strdeque_is_exist(id))
		{
			Strdeque& strdeque = strdeques[id];

			strdeque.clear();
		}
	}

	int strdeque_comp(unsigned long id1, unsigned long id2)
	{
		std::cout << "DEBUG strdeque_comp("<<id1<<", "<<id2<<")\n";

		Strdeque& strdeque1 = strdeque_get_from_id_or_empty(id1);
		Strdeque& strdeque2 = strdeque_get_from_id_or_empty(id2);

		int compareResult = 0;
		unsigned long lesserSize = strdeque1.size() < strdeque2.size() ? strdeque1.size() : strdeque2.size();

		for (unsigned long i = 0; i < lesserSize && compareResult == 0; i++)
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
