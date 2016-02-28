#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "infix.h"
#include "utils.h"
#include "constants.h"
#define NUM_TESTS 7
using namespace std;

bool test_exp_1(), test_exp_2(), test_exp_3(), test_exp_4(), test_package(), test_infix(), test_process(), run_tests();
typedef bool (*FP)();

template<typename T>
bool test(T expected, T actual){
	cout << "expected: " << expected << endl;
	cout << "actual: " << actual << endl;
	if (expected == actual)
		return true;
	return false;
}

int main(){
	run_tests();
}

bool run_tests(){
	bool testsPass = true;
	FP test_funcs[NUM_TESTS]= {
		&test_exp_1,
		&test_exp_2,
		&test_exp_3,
		&test_exp_4,
		&test_package,
		&test_infix,
		&test_process
	};
	for(int i = 0; i < NUM_TESTS; i++){
		cout << "TEST: " << i << endl;
		testsPass = testsPass & test_funcs[i]();
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
	return test(18, ExpStart());
}

// Tests basic exponentiation operation
bool test_exp_2(){
	add_input("9^2");
	return test(81, ExpStart());
}

// Tests right associativity of exponentiation operator
bool test_exp_3(){
	add_input("4^3^2^1");
	return test(262144, ExpStart());
}

// Tests the abilitity to have multiple digits in the string
bool test_exp_4(){
	add_input("(1000/20)/2*10-250");
	return test(0, ExpStart());
}

// Tests util functionality to create one half of a definte integral
bool test_package(){
	string integral = "3*X^5+X^3";
	string expected = "3*3^5+3^3";
	return test(expected, package(integral, 'X', '3'));
}

// Tests util functionality ton create a definite integral
bool test_infix(){
	string integral = "X^3+X^2+X^1";
	string expected = "(5^3+5^2+5^1)-(3^3+3^2+3^1)";
	return test(expected, create_infix(integral, 'X', '3', '5'));
}

// Tests evaulation functionality of an indefinte integral
bool test_process(){
	string integral = "X^3 + X^2 + X^1";
	process(integral, 'X', '3', '5');
	return test(116, ExpStart());
}

