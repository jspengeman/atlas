#include <iostream>
#include <fstream>
#include <string>
#include "infix.h"
#include "constants.h"
using namespace std;

// Might be troublesome to use same file
ifstream data(FILENAME);
double Input(), Integral(), Derivative(), Equation(), Polynomial(), Monomial(), Coefiencet(char, string);

double Input(){
	string operation;
	data >> operation;
	
	if (operation == INTEGRATE)
		return Integral();
	else if (operation == DERIVE)
		return Derivative();
	else
		return 0;
}

double Integral(){
	return Equation();	
}

double Derivative(){
	return 0;
}

double Equation(){
	return 0;
}

double Polynomial(){
	return 0;
}

double Monomial(){
	return 0;
}

double Coefiencet(char a, string total){
	return stod(Digits(a, total));
}



