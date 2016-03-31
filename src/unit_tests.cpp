#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "infix.h"
#include "integral.h"
#include "utils.h"
#include "constants.h"
#define NUM_TESTS 9
using namespace std;

bool test_exp_1(), test_exp_2(), test_exp_3(), test_exp_4(), test_exp_5(), 
test_package(), test_infix(), test_process(), test_factor_int(), run_tests();
bool double_equals(double a, double b, double epsilon);
typedef bool (*FP)();

bool double_equals(double a, double b, double epsilon = 0.001){
    return std::abs(a - b) < epsilon;
}

template<typename T>
bool test_str(T expected, T actual){
	cout << "expected: " << expected << endl;
	cout << "actual: " << actual << endl;
	if (expected == actual)
		return true;
	return false;
}

template<typename T>
bool test_dbl(T expected, T actual){
	cout << "expected: " << expected << endl;
	cout << "actual: " << actual << endl;
	if (double_equals(actual, expected))
		return true;
	return false;
}

int main(){
	run_tests();
}

bool run_tests(){
	bool testsPass = true;
	bool testResults[NUM_TESTS];
	FP test_funcs[NUM_TESTS]= {
		&test_factor_int,
		&test_process,
		&test_package,
		&test_infix,
		&test_exp_1,
		&test_exp_2,
		&test_exp_3,
		&test_exp_4,
		&test_exp_5
	};
	for(int i = 0; i < NUM_TESTS; i++){
		cout << "TEST: " << i << endl;
		bool single_test = test_funcs[i]();
		cout << "result: " << ((single_test) ? "pass" : "fail") << endl;
		testsPass = testsPass & single_test;
		cout << endl;
	} 
	if(testsPass){
		cout << "Output: all tests pass" << endl;
	} else {
		cout << "Output: at least one test fails" << endl;
	}

	return testsPass;
}

// Tests a non trivial string for infix
bool test_exp_1(){
	add_input("((3+3)^2)/2");
	return test_dbl(18.0, ExpStart());
}

// Tests basic exponentiation operation
bool test_exp_2(){
	add_input("9^2");
	return test_dbl(81.0, ExpStart());
}

// Tests right associativity of exponentiation operator
bool test_exp_3(){
	add_input("4^3^2^1");
	return test_dbl(262144.0, ExpStart());
}

// Tests the abilitity to have multiple digits in the string
bool test_exp_4(){
	add_input("(1000/20)/2*10-250");
	return test_dbl(0.0, ExpStart());
}

// Tests the abilitity to have decimals in a number
bool test_exp_5(){
	add_input("((2.5*2.5/1.2)^1.5)^0.666");
	return test_dbl(5.19975, ExpStart());
}

// Tests util functionality to create one half of a definte integral
bool test_package(){
	string integral = "3*X^5+X^3";
	string expected = "3*3^5+3^3";
	return test_str(expected, package(integral, 'X', '3'));
}

// Tests util functionality ton create a definite integral
bool test_infix(){
	string integral = "X^3+X^2+X^1";
	string expected = "(5^3+5^2+5^1)-(3^3+3^2+3^1)";
	return test_str(expected, create_infix(integral, 'X', '3', '5'));
}

// Tests evaulation functionality of an indefinte integral
bool test_process(){
	string integral = "X^3 + X^2 + X^1";
	process(integral, 'X', '3', '5');
	return test_dbl(116.0, ExpStart());
}

bool test_factor_int(){
	clear(FILENAME);
	string factor = "123.825x^2";
	add_input("123.825x^2");
	return test_str(factor, FactorInt());
}

