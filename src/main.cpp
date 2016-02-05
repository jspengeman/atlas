#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "utils.cpp"
#include "constants.h"
using namespace std;

int Exp(), Term(), Exp2(int), Term2(int), Fact(), Numb(char);
ifstream fin(FILENAME);

int main(){
	string integral = "X^3 + X^2 + X^1";
	process(integral, 'X', '3', '5');
	cout << "result=" << Exp() << endl;	
}

// This is the base Expression in our language
// which contains an expression +/- a term
// or it contains a term.
int Exp(){ return Exp2(Term()); }

// This is the base of the Term which is either
// a Term * a Factor or a Term / Factor or a Term
int Term(){ return Term2(Fact()); } 

// Exp2 handles the logic that would take place
// to parse this part of the language dealing 
// with addition and subtraction
int Exp2(int inp){
	int result = inp;
	char a;
	if (!fin.eof()){
		a = fin.get();
		if (a == '+')
			result = Exp2(result + Term());
		else if (a == '-')
			result = Exp2(result - Term());
		else
			fin.putback(a);
	}
	return result;
}

// Term2 handles the logic that the language
// requires if the potential operation is going
// to be multiplication or division
int Term2(int inp){
	int result = inp; 
	char a;
	if (!fin.eof()){
		a = fin.get();
		if (a == '*')
			result = Term2(result * Fact());
		else if (a == '/')
			result = Term2(result / Fact());
		else if (a == '+' || a == '-')
			fin.putback(a);
		else
			fin.putback(a);
	}
	return result;
}

// The function handles the parts of the language that
// has to do with putting something to a cetain power
// it is the inbetween function for term and number so
// if something is a term it can be either a number of
// a number and a factor
int Fact(){
	int result = 0;
	char a = fin.get();
	result = Numb(a);
	a = fin.get();
	if (a == '^')
		result = pow(result, Fact());
	else
		fin.putback(a);
	return result;
}

// This function handles the part of the language that could
// be described by either being a number of by being an expression
// surrounded by parenthesis so that it has the highest precedence
int Numb(char a){
	int result;
	if (a == '('){
		result = Exp();
		char x = fin.get();
	}
	else
		result = int(a - '0');
	return result;
}