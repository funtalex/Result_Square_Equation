#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

const int INF_NUM_OF_ROOTS = 3;


/*!
	\author Alex Sergeechev aka funtalex
	\version 2.0
	\brief This function solves an equation ax^2 + bx + c = 0

	\param[in] a - coefficient for x^2
	\param[in] b - coefficient for x
	\param[in] c - constant element
	\param[out] x1 - pointer of first root (if exist)
	\param[out] x2 - pointer of second root (if exist)

	\return number of roots
	\warning don't enter nan or inf, only finite number
*/
int solve_equation(double a, double b, double c, double* x1, double* x2) {
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));
	assert(isfinite(*x1));
	assert(isfinite(*x2));
	assert(x1 != x2);

	if (a == 0) {
		if (b == 0) {
			if (c == 0) {
				return INF_NUM_OF_ROOTS;
			}
			else {
				return 0;
			}
		}
		else {
			*x1 = -c / b;
			return 1;
		}
	}
	else {
		double disc = b * b - 4 * a * c;
		if (disc > 0) {
			double sqrt_disc = sqrt(disc);
			*x1 = (-b - sqrt_disc) / (2 * a);
			*x2 = (-b + sqrt_disc) / (2 * a);
			return 2;
		}
		else if (disc == 0) {
			*x1 = -b / (2 * a);
			return 1;
		}
		else {
			return 0;
		}
	}

	assert(false); // must return before
}


/*!
	\author Alex Sergeechev aka funtalex
	\version 1.0
	\brief Testing function

	\param[in] a - coefficient for x^2
	\param[in] b - coefficient for x
	\param[in] c - constant element
	\param[in] num_roots - number of roots
	\param[in] x1 - first answer (if nan => 0)
	\param[in] x2 - second answer (if nan => 0)


	Testing of program by parameters and answers given by programmist.
	To enter testing mode give the second argument "test" for main function.
*/
void unit_test(double a, double b, double c, int num_roots, double x1, double x2) {
	static int test_num = 1;

	double x1_copy = 0, x2_copy = 0;
	int num_roots_copy = solve_equation(a, b, c, &x1_copy, &x2_copy);

	if (num_roots == num_roots_copy && x1 == x1_copy && x2 == x2_copy) {
		printf("Test %d ok\n", test_num);
		test_num++;
	}
	else {
		printf("Wrong answer: test %d\n", test_num);
		printf("Coefficients: a = %lf, b = %lf, c = %lf\n", a, b, c);
		printf("Expected answer: Number of roots = %d\n", num_roots);

		if (num_roots == 1) {
			printf("\t x1 = %lf\n", x1);
		}
		if (num_roots == 2) {
			printf("\t x1 = %lf, x2 = %lf\n", x1, x2);
		}

		printf("Program answer: Number of roots = %d\n", num_roots);
		if (num_roots == 1) {
			printf("\t x1 = %lf\n", x1_copy);
		}
		if (num_roots == 2) {
			printf("\t x1 = %lf, x2 = %lf\n", x1_copy, x2_copy);
		}
	}
}


void test_of_program() {
	unit_test(1, 2, 1, 1, -1, 0);
	unit_test(1, -2, 1, 1, 1, 0);
	unit_test(0, 0, 0, INF_NUM_OF_ROOTS, 0, 0);
	unit_test(0, 2, 4, 1, -2, 0);
	unit_test(1, -5, 6, 2, 2, 3);
}

bool is_equal_test(char* argv) {
	return strlen(argv) == 4 && argv[0] == 't' && argv[1] == 'e' && argv[2] == 's' && argv[3] == 't';
}

int main(int argc, char** argv) {

	printf("Program - Solver of a square equation\n");
	printf("Sergeechev Alex aka funtalex, 2021\n");
	printf("Enter a, b, c - coeffitients for equation a * x ^ 2 + b * x + c = 0\n");

	assert(argc < 3);
	//printf("argc = %d", argc);
	//for (int i = 0; i < argc; i++) {
	//	printf("argv[%d] = %s\n", i, argv[i]);
	//}
	//printf("argv[1] - %s", argv[1]);
	if (argc == 2 && is_equal_test(argv[1])) {
		printf("Testing mode. \n\n\n");
		test_of_program();
		return 0;
	}

	double a = 0, b = 0, c = 0;
	scanf("%lf %lf %lf", &a, &b, &c);

	double x1 = 0, x2 = 0;

	int numRoots = solve_equation(a, b, c, &x1, &x2);

	switch (numRoots) {
	case 0:
		printf("No roots\n");
		break;

	case 1:
		printf("x = %lf\n", x1);
		break;

	case 2:
		printf("x1 = %lf\nx2 = %lf\n", x1, x2);
		break;

	case INF_NUM_OF_ROOTS:
		printf("Any number\n");
		break;

	default:
		printf("ERROR: Wrong number of roots = %d\n", numRoots);
		break; // break to avoid "case <value>" after default branch
	}

	return 0;
}