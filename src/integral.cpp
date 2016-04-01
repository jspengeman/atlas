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
	string result;
	if(!data.eof()){
		char a = data.get();
		if(a == '+' || a == '-'){
			string op(1, a);
			result = Polynomial() + op + TermInt();
		} else {
			data.putback(a);
		}
	}
	return result;
}

// Not working
string TermInt(){
	string result;
	if(!data.eof()){
		char a = data.get();
		string op(1, a);
		if (a == '*' || a == '/'){
			result = result + op + FactorInt();
		} else if (a == '+' || a == '-'){
			data.putback(a);
		} else {
			data.putback(a);
		}
	}
	return result;
}

string FactorInt(){
	string monomial = Monomial();
	char a = data.get();
	if(a == '^'){
		char a_prime = data.get();
		string num;
		string pw(1, a);
		// This only allows for numbers as exponents not expressions
		string exponent = Digits(a_prime, num, monomial.length() + 1);
		data.seekg(exponent.length(), data.beg);
		monomial = monomial + pw + exponent;
	} else 
		data.putback(a);
	return monomial;
}

string Monomial(){
	if(!data.eof()){
		char a = data.get();
		if(isalpha(a)){
			string num(1, a);
			return num;
		} 
		else if (isdigit(a)){
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



