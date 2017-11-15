#pragma once

class Exception
{
public:
	void what() = 0;
};

class det_equal_0 : public Exception
{
public:
	void what();
}

class matrix_is_not_quadratic : public Exception
{
public:
	void what();
}

class other_size_of_matrixs : public Exception
{
public:
	void what();
}

class bad_size_matrixs : public Exception
{
public:
	void what();
}

class bad_initialize_list : public Exception
{
public:
	void what();
}