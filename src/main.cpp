#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "integral.h"
#include "infix.h" // REMOVE THIS EVENTUALLY
#include "utils.h"
#include "constants.h"
using namespace std;

int main(){
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
	// resetInt();
	// resetExp();
	// add_input("123.825x^123*45");
	// cout << "output=" << TermInt() << endl;
}

