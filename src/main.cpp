#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "integral.h"
#include "infix.h" // REMOVE THIS EVENTUALLY
#include "utils.h"
#include "constants.h"
using namespace std;

int main(){
	add_input("((2.5*2.5/1.2)^1.5)^0.666");
	cout << "output=" << Exp() << endl;	
}

