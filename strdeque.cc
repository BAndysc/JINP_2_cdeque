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
	namespace DebugStrings
	{
		const char* NewDeque = "strdeque_new()";
		const char* DequeCreated = "strdeque_new: deque %1% created";
		const char* DeleteDeque = "strdeque_delete(%1%)";
		const char* DeleteDequeDoesnotExist = "strdeque_delete: deque %1% doesn't exist";
		const char* DeleteDequeEmpty = "strdeque_delete: trying to delete empty dequeue";
		const char* DequeSizeFunc = "strdeque_size(%1%)";
		const char* DequeInsertAtFunc = "strdeque_insert_at(%1%, %2%, \"%3%\")";
		const char* RemoveFunc = "strdeque_remove_at(%1%, %2%)";

		const char* DequeDoesnotExist = "%1%: deque %2% does not exist";

		const char* DequeSize = "strdeque_size";
		const char* DequeInsertAt = "strdeque_insert_at";
		const char* Remove = "strdeque_remove_at";
		const char* GetAt = "strdeque_get_at";
		const char* Clear = "strdeque_clear";

		const char* InsertAtNull = "strdeque_insert_at: attempt to insert NULL into a deque";
		const char* InsertIntoEmpty = "strdeque_insert_at: attempt to insert into the Empty Deque";
		const char* Inserted = "strdeque_insert_at: deque %1%, element \"%2%\" inserted at %3%";

		const char* RemoveEmpty = "strdeque_remove_at: attempt to remove from the Empty Deque";
		const char* ElementRemoved = "strdeque_remove_at: deque %1% element at %2% removed";
		const char* RemoveNoIndex = "strdeque_remove_at: deque %1% does not contain an element at %2%";

		const char* DequeGetAtFunc = "strdeque_get_at(%1%, %2%)";
		const char* GetAtResult = "strdeque_get_at: deque %1%, element at %2% is \"%3%\"";
		const char* GetAtNoElement = "strdeque_get_at: deque %1% does not contain an element at %2%";


		const char* ClearDequeFunc = "strdeque_clear(%1%)";
		const char* ClearEmptyDeque = "strdeque_clear: attempt to clear the Empty Deque";

		const char* CompareDequesFunc = "strdeque_comp(%1%, %2%)";
		const char* CompareResult = "strdeque_comp: result of comparing deque %1% to deque %2% is %3%";
	
		const char* TheEmptyDeque = "the Empty Deque";
	};

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
		static const std::string theEmptyDequeue(DebugStrings::TheEmptyDeque);

		if (key == jnp1::emptystrdeque())
		{
			return theEmptyDequeue;
		}

		return std::to_string(key);
	}

	int strdeque_comp_calculate(Strdeque& strdeque1, Strdeque& strdeque2)
	{
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

//namespace jnp1
//{
	StrDequeMapKey strdeque_new()
	{
		debug(DebugStrings::NewDeque);

		assert(nextIdToUse < std::numeric_limits<StrDequeMapKey>::max());

		StrDequeMapKey key = nextIdToUse++;

		get_str_deque_map()[key] = Strdeque();

		debug((boost::format(DebugStrings::DequeCreated) % key).str());

		return key;
	}

	void strdeque_delete(StrDequeMapKey id)
	{
		debug((boost::format(DebugStrings::DeleteDeque) % deque_to_string(id)).str());

		StrDequeMap::iterator itr = get_str_deque_map().find(id);

		if (itr == get_str_deque_map().end())
		{
			debug((boost::format(DebugStrings::DeleteDequeDoesnotExist) % id).str());
		}
		else if (strdeque_is_empty(id))
		{
			debug(DebugStrings::DeleteDequeEmpty);
		}
		else
		{
			get_str_deque_map().erase(itr);
		}
	}

	size_t strdeque_size(StrDequeMapKey id)
	{
		debug((boost::format(DebugStrings::DequeSizeFunc) % deque_to_string(id)).str());

		StrDequeMap::iterator itr = get_str_deque_map().find(id);

		if (itr != get_str_deque_map().end())
		{
			return itr->second.size();
		}
		else
		{
			debug((boost::format(DebugStrings::DequeDoesnotExist) % DebugStrings::DequeSize % id).str());
		}

		return 0;
	}

	void strdeque_insert_at(StrDequeMapKey id, size_t pos, const char* value)
	{
		debug((boost::format(DebugStrings::DequeInsertAtFunc) % deque_to_string(id) % pos % value).str());

		if (value == nullptr)
		{
			debug(DebugStrings::InsertAtNull);
		}
		else if (strdeque_is_empty(id))
		{
			debug(DebugStrings::InsertIntoEmpty);
		}
		else
		{
			StrDequeMap::iterator itr = get_str_deque_map().find(id);

			if (itr == get_str_deque_map().end())
			{
				debug((boost::format(DebugStrings::DequeDoesnotExist) % DebugStrings::DequeInsertAt % id).str());
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
				debug((boost::format(DebugStrings::Inserted) % id % value % pos).str());
			}
		}
	}

	void strdeque_remove_at(StrDequeMapKey id, size_t pos)
	{
		debug((boost::format(DebugStrings::RemoveFunc) % deque_to_string(id) % pos).str());

		StrDequeMap::iterator itr = get_str_deque_map().find(id);

		if (strdeque_is_empty(id))
		{
			debug(DebugStrings::RemoveEmpty);
		}
		else if (itr == get_str_deque_map().end())
		{
			debug((boost::format(DebugStrings::DequeDoesnotExist) % DebugStrings::Remove % id).str());
		}
		else
		{
			Strdeque& strdeque = itr->second;

			if (pos < strdeque.size())
			{
				strdeque.erase(strdeque.begin() + pos);

				debug((boost::format(DebugStrings::ElementRemoved) % id % pos).str());
			}
			else
			{
				debug((boost::format(DebugStrings::RemoveNoIndex) % id % pos).str());
			}
		}
	}

	const char* strdeque_get_at(StrDequeMapKey id, size_t pos)
	{
		debug((boost::format(DebugStrings::DequeGetAtFunc) % deque_to_string(id) % pos).str());

		StrDequeMap::iterator itr = get_str_deque_map().find(id);

		if (itr == get_str_deque_map().end())
		{
			debug((boost::format(DebugStrings::DequeDoesnotExist) % DebugStrings::GetAt % id).str());
		}
		else
		{
			Strdeque& strdeque = itr->second;

			if (pos < strdeque.size())
			{
				debug((boost::format(DebugStrings::GetAtResult) % id % pos % strdeque[pos]).str());

				return strdeque[pos].c_str();
			}
			else
			{
				debug((boost::format(DebugStrings::GetAtNoElement) % deque_to_string(id) % pos).str());
			}
		}

		return nullptr;
	}

	void strdeque_clear(StrDequeMapKey id)
	{
		debug((boost::format(DebugStrings::ClearDequeFunc) % deque_to_string(id)).str());

		StrDequeMap::iterator itr = get_str_deque_map().find(id);

		if (itr == get_str_deque_map().end())
		{
			debug((boost::format(DebugStrings::DequeDoesnotExist) % DebugStrings::Clear % id).str());
		}
		else if (strdeque_is_empty(id))
		{
			debug(DebugStrings::ClearEmptyDeque);
		}
		else
		{
			itr->second.clear();
		}
	}

	int strdeque_comp(StrDequeMapKey id1, StrDequeMapKey id2)
	{
		debug((boost::format(DebugStrings::CompareDequesFunc) % deque_to_string(id1) % deque_to_string(id2)).str());

		Strdeque& strdeque1 = strdeque_get_from_id_or_empty(id1);
		Strdeque& strdeque2 = strdeque_get_from_id_or_empty(id2);

		int compareResult = strdeque_comp_calculate(strdeque1, strdeque2);

		debug((boost::format(DebugStrings::CompareResult) % deque_to_string(id1) % deque_to_string(id2) % compareResult).str());

		return compareResult;
	}
//}
/*
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

*/