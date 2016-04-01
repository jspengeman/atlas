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
			// Not sure what to put here
			// TODO: this needs to implement the recursive returning of elements
			return op + FactorInt();
		} else {
			string term = TermInt();
			data.seekg(term.length(), data.beg);
			return term + Polynomial();
		}
	}
	return result;
}

// This is fine now, I think
string TermInt(){
	cout << "TEST 1" << endl;
	string result;
	if(!data.eof()){
		char a = data.get();
		string op(1, a);
		if (a == '*' || a == '/'){
			result = result + op + FactorInt();
		} else if (a == '+' || a == '-'){
			data.putback(a);
		} else {
			return FactorInt();
		}
	}
	return result;
}

string FactorInt(){
	cout << "TEST 2" << endl;
	string monomial = Monomial();
	char a = data.get();
	if(a == '^'){
		cout << "mono 0: " << data.tellg() << endl; 
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

// TODO: Fix the infinite loop and remove print statements
string Monomial(){
	cout << "TEST 3" << endl;
	if(!data.eof()){
		char a = data.get();
		if(isalpha(a)){
			cout << "mono 1: " << a << endl;
			string var(1, a);
			return var;
		} 
		else if (isdigit(a)){
			cout << "mono 2: " << a << endl;
			string coef = Monomial2(a);
			data.seekg(coef.length(), data.beg);
			string var = Monomial();
			return coef + var;
		}
	}
	return "";
}

string Monomial2(char a){
	string num;
	return Coefiencet(a, num);
}

string Coefiencet(char a, string total){
	return Digits(a, total, 0);
}



