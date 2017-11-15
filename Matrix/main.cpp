#include "Matrix.h"

#include <iostream>
#include <complex>
#include <fstream>


void test1()
{
	std::cout << "*********************test1***********************\n\n";
	
	CMatrix<double> A{ { 1, 2, 3 },
					{ 4, 7, 6 },
					{ 7, 8, 9 } };
	
	std::cout << "A\n" << A
			  << "\nA.transposition()\n"	<< A.transposition() 
			  << "\nA.det() "				<< A.getDet() 
			  << "\nA.col "					<< A.getColumns() 
			  << "\nA.row "					<< A.getRows() 
			  << "\nA.Val "					<< A.getValue(0,0) 
			  << "\nA.alg\n"				<< A.algebraicCoplement()
			  << "\nA.reverse\n"			<< A.reverse();
}

void test2()
{
	std::cout << "*********************test2***********************\n\n";

	CMatrix<std::complex<double>> A(2,2);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			A.setValue(i, j, std::complex<double>(i + 5 + rand(), j + rand()));
	
	std::cout << "A\n" << A
		<< "\nA.transposition()\n"	<< A.transposition()
		<< "\nA.det() "				<< A.getDet()
		<< "\nA.col "				<< A.getColumns()
		<< "\nA.row "				<< A.getRows()
		<< "\nA.Val "				<< A.getValue(0, 0)
		<< "\nA.alg\n"				<< A.algebraicCoplement()
		<< "\nA.reverse\n"			<< A.reverse();
}

void test3()
{
	std::cout << "*********************test3***********************\n\n";

	CMatrix<double> A(2, 2);
	CMatrix<double> B{ {6, 5}, {3, 5} };

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			A.setValue(i, j, j + rand());
	
	std::cout << A << B;
	
	std::cout << A + B << A - B << A * B << A*2;

	A += B;
	std::cout << A;
	A *= B;
	std::cout << -A;
	A -= B;
}

void test4()
{
	std::cout << "*********************test4***********************\n\n";

	CMatrix<double> mat{
		{1.2, 2.7, 4.3},
		{-1.0, 4.0, 1.0},
		{0.5, 4.4, 67.01} };

	std::cout << mat.getDet();
}

void test5()
{
	std::cout << "\n*********************test5***********************\n\n";
	CMatrix<double> mat{
		{ 1.2, 2.7, 4.3 },
		{ -1.0, 4.0, 1.0 },
		{ 0.5, 4.4, 67.01 } };
	mat(2, 2) = 5.0;
	std::cout << "Matrix(2,2) : " << mat(2, 2) << std::endl;
}

void test6()
{
	std::cout << "\n*********************test6***********************\n\n popsiute.. ^^";
	CMatrix<double> mat;
	std::ifstream file("matrix.txt", std::ifstream::in);
	file >> mat;
	std::cout << mat;
	file.close();
}

void test7()
{
	std::cout << "\n*********************test7***********************\n\n";
	CMatrix<double> A{ {1.0, 2.0, 3.0},
					   {4.0, 5.0, 6.0},
					   {7.0, 8.0, 9.0} };
	CMatrix<double> B(A);

	std::cout << B << std::endl;
	std::cout << A(0, 0) << std::endl;
	A(0,0) = 5.0;
	std::cout << A << std::endl;
	CMatrix<double> C;
	C = A;
	C += B -= A *= B;
	A * 2.0 + A - B;
	std::cout << C << std::endl;
	std::cout << (A + B * A - A * A);
}

void test8()
{
	std::cout << "\n*********************test8***********************\n\n";
	CMatrix<int> A(2, 2);
	std::cin >> A;
	std::cout << A;
}

void test9()
{
	std::cout << "\n*********************test9***********************\n\n";
	CMatrix<double> A("matrix.txt");
	std::cout << A << std::endl;
}

void test10()
{
	std::cout << "\n*********************test10**********************\n\n";
	CMatrix<double> A({ { 2 } });
	CMatrix<double> B({ { 3 } });
	A = B;
	B(0, 0) = 7;
	std::cout << A << B;
}

int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();

	std::cin.get();
	std::cin.get();

	return 0;
}
