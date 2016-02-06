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
	string integral = "X^3 + X^2 + X^1";
	process(integral, 'X', '3', '5');
	cout << "result=" << Exp() << endl;	
}

