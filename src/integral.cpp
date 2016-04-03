#include <iostream>
#include <fstream>
#include <string>
#include "infix.h"
#include "integral.h"
#include "constants.h"
using namespace std;

// Might be troublesome to use same file
ifstream data(FILENAME);

void resetInt(){
	data.clear();
	data.seekg(0, data.beg);	
}

// Operation mutliplexor, distributes to
// correct grammar based on the type of
// equation that is used as input
double Input(){
	string operation;
	data >> operation;
	double output;	
	if (operation == INTEGRATE)
		output = Integral();
	else if (operation == DERIVE)
		output = Derivative();
	else
		output = 0;

	resetInt();
	resetExp();
	return output;
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

// Not working 
string Polynomial(){
	cout << "TEST 0" << endl;
	string result;
	if(!data.eof()){
		char a = data.get();
		if(a == '+' || a == '-'){
			string op(1, a);
			// TODO: this needs to implement the recursive returning of elements
			return op + TermInt();
		} else {
			string term = TermInt();
			data.seekg(term.length(), data.beg);
			return term + Polynomial();
		}
	}
	return result;
}

// TODO: Fix this function to have recursive traversal of string
string TermInt(){
	cout << "TEST 1" << endl;
	string result;
	if(!data.eof()){
		char a = data.get();
		string op(1, a);
		cout << "op: " << op << endl;
		if (a == '*' || a == '/'){
			string fact = FactorInt();
			string term = TermInt();
			result = term + op + fact;
		} else if (a == '+' || a == '-'){
			// Let Polynomial handle these operations
			data.putback(a);
		} else if (isalnum(a)){
			// Only reads a factor and not anything else afterwards
			string fact = FactorInt();
			result = fact;
		}
	}
	return result;
}

// This is working
string FactorInt(){
	cout << "TEST 2" << endl;
	string monomial = Monomial();
	char a = data.get();
	if(a == '^'){
		char a_prime = data.get();
		string num;
		string op(1, a);

		// This only allows for numbers as exponents not expressions
		string exponent = Digits(a_prime, num, monomial.length() + 1);
		data.seekg(exponent.length(), data.beg);
		monomial = monomial + op + exponent;
	} else 
		data.putback(a);
	return monomial;
}

string Monomial(){
	cout << "TEST 3" << endl;
	string result;
	if(!data.eof()){
		char a = data.get();
		if(isalpha(a)){
			string var(1, a);
			result = var;
		} 
		else if (isdigit(a)){
			string coef = Monomial2(a);
			data.seekg(coef.length(), data.beg);
			string var = Monomial();
			result = coef + var;
		}
	}
	return result;
}

string Monomial2(char a){
	string num;
	return Coefficient(a, num);
}

string Coefficient(char a, string total){
	return Digits(a, total, 0);
}



