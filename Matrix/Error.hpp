#pragma once

#include <string>

namespace Matrix_Except
{
	class Exception
	{
	private:
		std::string m_error;
	public:
		Exception(const char * error) : m_error(error) {}
		virtual const std::string & what() { return m_error; };
	};

	class bad_matrix_file_format : public Exception
	{
	public:
		bad_matrix_file_format(const char * error = "bad matrix file format") : Exception(error) {}
	};

	class det_equal_0 : public Exception
	{
	public:
		det_equal_0(const char * error = "det is equal 0") : Exception(error) {}
	};

	class matrix_is_not_quadratic : public Exception
	{
	public:
		matrix_is_not_quadratic(const char * error = "matrix is not quadratic") : Exception(error) {}
	};

	class other_size_of_matrixs : public Exception
	{
	public:
		other_size_of_matrixs(const char * error = "other size of matrixs") : Exception(error) {}
	};

	class bad_size_matrixs : public Exception
	{
	public:
		bad_size_matrixs(const char * error = "bad size matrixs") : Exception(error) {}
	};

	class bad_initialize_list : public Exception
	{
	public:
		bad_initialize_list(const char * error = "bad initialize list") : Exception(error) {}
	};

	class no_memory : public Exception
	{
	public:
		no_memory(const char * error = "no memory") : Exception(error) {}
	};
}