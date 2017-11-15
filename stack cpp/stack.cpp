#include "stack.hpp"
#include <iostream>
#include <cstdint>
#include <cstring>

stack::stack() :
	m_size(m_buffer_increment),
	m_top(0),
	mp_stack(new int[m_buffer_increment])
{
	if (mp_stack == nullptr)
		std::cout << "Blad alokacji pamieci!";
}
stack::~stack()
{
	delete[] mp_stack;
}

void stack::clear()
{
	m_top = 0;
}

void stack::push(int value)
{
	if (m_top == m_size)
	{
		int * tmp = new int[m_size + m_buffer_increment];
		if (tmp == nullptr)
		{
			std::cout << "Nie mozna rozszerzyc stosu\n";
			return;
		}
		
		std::memcpy(tmp, mp_stack, sizeof(int) * m_size);
		
		m_size += m_buffer_increment;
		delete[] mp_stack;
		mp_stack = tmp;
	}
	
	mp_stack[m_top] = value;
	m_top++;
}

int stack::pop()
{
	if (m_top != 0)
		return mp_stack[--m_top];

	std::cout << "Brak elementow na stosie!\n";
	return mp_stack[0];
}

bool stack::isEmpty()
{
	return m_top == 0 ? true : false;
}