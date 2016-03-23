#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "infix.h"
#include "utils.h"
#include "constants.h"
using namespace std;

int main(){
	// string integral = "X^3 + X^2 + X^1";
	// process(integral, 'X', '3', '5');

	add_input("((2.5*2.5/1.2)^1.5)^0.666");
	cout << "output=" << Exp() << endl;	
}

