#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "infix.h"
#include "utils.h"
#include "constants.h"
#define NUM_TESTS 4
using namespace std;

bool test_process(), test_exp_1(), test_exp_2(), test_exp_3(), run_tests();
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

bool test_exp_1(){
	add_input("((3+3)^2)/2");
	return test(18, ExpStart());
}

bool test_exp_2(){
	add_input("9^2");
	return test(81, ExpStart());
}

// Tests right associativity of exponentiation operator
bool test_exp_3(){
	add_input("4^3^2^1");
	return test(262144, ExpStart());
}

bool test_process(){
	// Test the process functions ability
	// to create an infix expression
	string integral = "X^3 + X^2 + X^1";
	process(integral, 'X', '3', '5');
	return test(116, ExpStart());
}

