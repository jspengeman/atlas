#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "infix.h"
#include "constants.h"
using namespace std;

ifstream fin(FILENAME);

// This is the base Expression in our language
// which contains an expression +/- a term
// or it contains a term.
double ExpStart(){
	fin.clear();
	fin.seekg(0, fin.beg);	
	return Exp();
}

double Exp(){ return Exp2(Term()); }

// This is the base of the Term which is either
// a Term * a Factor or a Term / Factor or a Term
double Term(){ return Term2(Fact()); } 

// Exp2 handles the logic that would take place
// to parse this part of the language dealing 
// with addition and subtraction
double Exp2(double inp){
	double result = inp;
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
double Term2(double inp){
	double result = inp; 
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
double Fact(){
	double result = 0;
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
double Numb(char a){
	double result;
	if (a == '('){
		result = Exp();
		char x = fin.get();
	}
	else {
		string number(1, a);
		double num = stod(Digits(a, number));
		result = num;
	}
	return result;
}

// This function handles the part of the language that describes
// describes the grammar as containing a string that is a single  
// digit or mutiple digits potentially
string Digits(char a, string total){
	if(!isdigit(a) && a != '.'){
		fin.putback(a);
		total.pop_back();
		return total;
	}
	char digit = fin.get();
	total.push_back(digit);
	return Digits(digit, total);
}