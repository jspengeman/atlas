#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "infix.h"
#include "utils.h"
#include "constants.h"
#define NUM_TESTS 3
using namespace std;

bool test_process(), test_expression(), run_tests();
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
		&test_expression,
		&test_expression,
		&test_expression
		// &test_process
	};
	for(int i = 0; i < NUM_TESTS; i++){
		cout << "TEST: " << i << endl;
		testsPass = testsPass & test_funcs[i]();
		
	} 
	if(testsPass){
		cout << "Output: all tests pass" << endl;
	} else {
		cout << "Output: at least one test fails" << endl;
	}
	return testsPass;
}

bool test_expression(){
	add_input("((3+3)^2)/2");
	int output = Exp();
	// print_file(FILENAME);
	return test(18, output);
}

bool test_process(){
	// Test the process functions ability
	// to create an infix expression
	string integral = "X^3 + X^2 + X^1";
	process(integral, 'X', '3', '5');
	int output = Exp();
	return test(116, output);
}

