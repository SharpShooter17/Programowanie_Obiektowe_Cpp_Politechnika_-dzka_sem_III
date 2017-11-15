#pragma once
#include <ostream>
#include <stdexcept>

template <class Key, class Value>
class Map
{
private:
	struct node_t {
		node_t * next;
		Key key;
		Value value;
	};
protected:
	node_t * head;

	Value * get(Key);
	virtual void clear();

public:
	Map();
	Map(const Map & t);
	~Map();
	Value  * operator[](Key);
	void insert(Key, Value);
	Map<Key, Value> & operator=(const Map &);
	template <class id, class val>
	friend std::ostream & operator <<(std::ostream & in, const Map<id, val> & m)
	{
		node_t * it;
		for (it = m.head; it != nullptr; it = it->next)
			in << "key: " << it->key << ", value: " << it->value << std::endl;
		return in;
	}
};

template<class Key, class Value>
Value * Map<Key, Value>::get(Key key)
{
	node_t * result;
	for (result = head; result != nullptr; result = result->next) 
		if (result->key == key)
			break;
		else if (result->next == nullptr)
				throw std::out_of_range("No such key in Map");

	return &result->value;
}

template<class Key, class Value>
void Map<Key, Value>::clear()
{
	node_t *temp;
	for (node_t *o = head; o != nullptr; o = temp)
	{
		temp = o->next;
		delete o;
	}
	head = nullptr;
}

template<class Key, class Value>
Map<Key, Value>::Map() : head(nullptr)
{
}

template<class Key, class Value>
Map<Key, Value>::Map(const Map & t) : head(nullptr)
{
	for (node_t * temp = t.head; temp != nullptr; temp = temp->next)
		insert(temp->key, temp->value);
}

template<class Key, class Value>
Map<Key, Value>::~Map()
{
	clear();
}

template<class Key, class Value>
Value * Map<Key, Value>::operator[](Key key)
{
	return get(key);
}

template<class Key, class Value>
void Map<Key, Value>::insert(Key key, Value value)
{
	node_t * wsk = new node_t{ nullptr, key, value };

	if (head == nullptr) 
	{
		head = wsk;
		return;
	}

	node_t * temp;
	for (temp = head; temp->next != nullptr; temp = temp->next);
	temp->next = wsk;
}

template<class Key, class Value>
Map<Key, Value> & Map<Key, Value>::operator=(const Map & map)
{
	if (this == & map)
		return *this;

	clear();

	for (node_t * x = map.head; x != nullptr; x = x->next)
		insert(x->key, x->value);

	return *this;	
}
