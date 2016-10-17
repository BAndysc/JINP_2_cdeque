#include <iostream>
#include "strdeque.h"
#include "cstrdeque"

unsigned long strdeque_new()
{
	std::cout << "DEBUG strdeque_new()\n";
	return 0;
}

void strdeque_delete(unsigned long id)
{
	std::cout << "DEBUG strdeque_delete(" << id << ")\n";
}

size_t strdeque_size(unsigned long id)
{
	std::cout << "DEBUG strdeque_size("<<id<<")\n";
	return 0;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value)
{
	std::cout << "DEBUG strdeque_insert_at("<<id<<", "<<pos<<", "<<value<<")\n";
}

void strdeque_remove_at(unsigned long id, size_t pos)
{
	std::cout << "DEBUG strdeque_remove_at("<<id<<", "<<pos<<"\n";
}

const char* strdeque_get_at(unsigned long id, size_t pos)
{
	std::cout << "DEBUG strdeque_get_at("<<id<<", "<<pos<<")\n";
	return nullptr;
}

void strdeque_clear(unsigned long id)
{
	std::cout << "DEBUG strdeque_clear("<<id<<")\n";
}

int strdeque_comp(unsigned long id1, unsigned long id2)
{
	std::cout << "DEBUG strdeque_comp("<<id1<<", "<<id2<<")\n";
	return 0;
}


unsigned long jnp1::strdeque_new()
{
	return strdeque_new();
}

void jnp1::strdeque_delete(unsigned long id)
{
	strdeque_delete(id);
}

size_t jnp1::strdeque_size(unsigned long id)
{
	return strdeque_size(id);
}

void jnp1::strdeque_insert_at(unsigned long id, size_t pos, const char* value)
{
	strdeque_insert_at(id, pos, value);
}

void jnp1::strdeque_remove_at(unsigned long id, size_t pos)
{
	strdeque_remove_at(id, pos);
}

const char* jnp1::strdeque_get_at(unsigned long id, size_t pos)
{
	return strdeque_get_at(id, pos);
}

void jnp1::strdeque_clear(unsigned long id)
{
	strdeque_clear(id);
}

int jnp1::strdeque_comp(unsigned long id1, unsigned long id2)
{
	return strdeque_comp(id1, id2);
}

