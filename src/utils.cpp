#include <string>
#include "constants.h"
using namespace std;

void add_input(string input);
void process(string input, char var, char lower_lim, char upper_lim);
string package(string indef_int, char var, char limit);
string create_infix(string indef_int, char var, char lower_lim, char upper_lim);

void process(string input, char var, char lower_lim, char upper_lim){
	input.erase(remove(input.begin(), input.end(), ' '), input.end());
	string definte_integral = create_infix(input, var, lower_lim, upper_lim);
	add_input(definte_integral);
}

void add_input(string input){
	ofstream input_data(FILENAME);
	input_data << input << "\n";
	input_data.close();
}

string package(string indef_int, char var, char limit){
	for(int i = 0; i < indef_int.length(); i++){
		if(indef_int[i] == var){
			indef_int[i] = limit;
		}
	}
	return indef_int;
}

string create_infix(string indef_int, char var, char lower_lim, char upper_lim){
	string definite_lower = package(indef_int, var, lower_lim);
	string definite_higher = package(indef_int, var, upper_lim);
	return "(" + definite_higher + ")" +"-" + "(" + definite_lower + ")";
}
