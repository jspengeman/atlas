#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "integral.h"
#include "infix.h" 
#include "utils.h"
#include "constants.h"
using namespace std;

int main(){

	// This is all testing stuff
	add_input("((2.5*2.5/1.2)^1.5)^0.666");
	cout << "output=" << ExpStart() << endl;	

	add_input("int x^2 between 1 and 2");
	cout << "output=" << Input() << endl;

	add_input("123.825"); string num;
	cout << "output=" << Coefficient('1', num) << endl;

	resetInt();
	resetExp();
	add_input("123.825x");
	cout << "output=" << Monomial() << endl;

	resetInt();
	resetExp();
	add_input("123.825x^123");
	cout << "output=" << FactorInt() << endl;

	// This and up are the broken parts
	resetInt();
	resetExp();
	add_input("123.825x^123*45+4");
	cout << "output=" << TermInt() << endl;
	// Till here is testing stuff


	// Input: you can see a few functions below
	// make sure to mirror this input. Unfortunately
	// there are not currently negative values allowed
	// for limits of integration or multiple digits limits

	double result;
	result  = integrate("int x^3 + 3x^2 + 5x + 25 between 1 and 5");
	cout << "result=" << result << endl;

	result  = integrate("int x^2 - 3x between 3 and 7");
	cout << "result=" << result << endl;

	result  = integrate("int x^4 - 25 between 0 and 1");
	cout << "result=" << result << endl;

	result  = integrate("int x^4 - 25 between 0 and 1");
	cout << "result=" << result << endl;


	// This one is wrong because the 1 is not correctly integrated
	result  = integrate("int x^4 - x^3 - x^2 - x + 1 between 2 and 4");
	cout << "result=" << result << endl;
}

