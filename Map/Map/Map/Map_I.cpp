#include "Map_I.h"
#include <iostream>
#include <stdexcept>

Map_I::Map_I() : head(nullptr)
{
}

Map_I::Map_I(const Map_I & t) 
{
	head = nullptr;

	node_t* temp;
	for (temp = t.head; temp != nullptr; temp = temp->next)
		insert(temp->key, temp->value);
}


Map_I::~Map_I()
{
	clear();
}

void Map_I::insert(std::string key, int value)
{
	node_t * old = nullptr;
	node_t * node = head;

	while (node != nullptr)
	{
		if (node->key == key)
		{
			node->value = value;
			return;
		}
		old = node;
		node = node->next;
	}

	if (old == nullptr)
		head = newNode(nullptr, value, key);
	else
		old->next = newNode(nullptr, value, key);
}

Map_I & Map_I::operator=(const Map_I & t)
{
	if (this == &t)
		return *this;

	clear();

	for (node_t * x = t.head; x != nullptr; x = x->next)
		insert(x->key, x->value);

	return *this;
}

int Map_I::get(std::string key)
{
	node_t * o;
	for (o = head; o != nullptr; o = o->next) {
		if (o->key == key) {
			break;
		}
		else {
			if (o->next == nullptr) {
				throw std::out_of_range("No such key in Map");
			}
		}
	}
	return o->value;
}

void Map_I::clear()
{
	node_t *temp;
	for (node_t *o = head; o != nullptr; o = temp)
	{
		temp = o->next;
		delete o;
	}
}

node_t * Map_I::newNode(node_t * next, int val, std::string key)
{
	node_t* result = new node_t;
	result->next = next;
	result->key = key;
	result->value = val;
	return result;
}

std::ostream & operator<<(std::ostream & in, const Map_I & m)
{
	node_t * o;
	for (o = m.head; o != nullptr; o = o->next) 
		in << "key: " << o->key << ", value: " << o->value << std::endl;
	return in;
}

