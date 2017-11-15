class stack
{
private:
	int m_size;
	int m_top;
	int * mp_stack;
	
	constexpr int m_buffer_increment = 64;

public:
	stack();
	~stack();
	void clear();
	void push(int value);
	int pop();
	bool isEmpty();
};
