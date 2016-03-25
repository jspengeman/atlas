#include <iostream>
#include <fstream>
#include <string>
#include "infix.h"
#include "constants.h"
using namespace std;

// Might be troublesome to use same file
ifstream data(FILENAME);
double Input(), Integral(), Derivative(), Equation(), Polynomial();
string Monomial(), Monomial2(char), Coefiencet(char, string);

// Operation mutliplexor, distributes to
// correct grammar based on the type of
// equation that is used as input
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
	} else {
		return "";
	}
	
}

string Monomial2(char a){
	string num;
	return Coefiencet(a, num);
}

string Coefiencet(char a, string total){
	return Digits(a, total);
}



