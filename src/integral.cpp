#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
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
	string result;
	if(!data.eof()){
		char a = data.get();
		string op(1, a);
		if (a == '*' || a == '/'){
			// Is an actual Term
		} else if (a == '+' || a == '-'){
			// Let Polynomial handle these operations
			data.putback(a);
		} else if (isalnum(a)){
			// Is just a Factor
			string fact = FactorInt();
			result = fact;
		}
	}
	return result;
}

// This is working
string FactorInt(){
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

// This is working
string Monomial(){
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

// This is working
string Monomial2(char a){
	string num; return Coefficient(a, num);
}

string Coefficient(char a, string total){
	return Digits(a, total, 0);
}

// Not part of the grammar
double integrate(string input){
	int pos_btw = input.find("between");

	int num_count = 0;
	char A, B;
	for(int i = pos_btw + 7; i < input.length(); i++){
		if(isdigit(input[i])){
			if(++num_count == 1){
				A = input[i];
			} else {
				B = input[i];
			}
		}
	}

	// whole string first
	// number second
	// variable third
	// carrot fourth
	// exponent fifth

	input.erase(pos_btw, input.length());
	input.erase(0, input.find(" "));

	smatch sm; 
	string function;
    string term;
    istringstream iss(input);
    while(iss >> term) {
    	// Monomial case
    	if (term.length() > 1){
    		string output = "";

	    	regex e("(\\d+)?(\\w)?(\\^)?(\\d+)?");
		  	regex_match ( term.cbegin(), term.cend(), sm, e);

		  	string coef = sm[1];
		  	string var = sm[2];
		  	string expo = sm[4];

		  	// Factor case
		  	if (expo.length() > 0){
		  		int new_expo = stod(expo) + 1;

		  		if (coef.length() > 0){
		  			output = coef + "/" + to_string(new_expo) + "*";
		  			output += var + "^" + to_string(new_expo);
		  		} else {
		  			output = var + "^" + to_string(new_expo);
		  			output += "/" + to_string(new_expo);
		  		}

		  	// Constant case or not exponent case
		  	} else {
		  		// not exponent case
		  		if (var.length() > 0){
					if (coef.length() > 0){
			  			output = coef + "/2*";
			  			output += var + "^2";
			  		} else {
			  			output = var + "^2";
			  			output += "/2";
			  		}


		  		// Constant case
		  		} else {
		  			int pos = function.length() - 1;
		  			function.erase(pos, pos);
		  		}
		  	}
		  	
		  	function += output;
		// Operator case
        } else {
        	function += term;
        }
    }
    cout << "function: " << function << endl;
	return 0.0;
}



