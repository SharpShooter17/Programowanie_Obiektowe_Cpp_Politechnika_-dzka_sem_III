#pragma once
#include <string>
#include <ostream>

struct node_t {
	node_t * next;
	int value;
	std::string key;
};

class Map_I
{
protected:
	 node_t * head;

	 int get(std::string);
	 void clear();
	 node_t * newNode(node_t * next, int val, std::string key);

public:
	Map_I();
	Map_I(const Map_I& t);
	virtual ~Map_I();
	virtual int operator[](std::string) = 0;
	virtual void insert(std::string, int);
	Map_I & operator=(const Map_I &);
	friend std::ostream & operator <<(std::ostream & in, const Map_I& m);
};

