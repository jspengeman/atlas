#include <string>
using namespace std;

double Input(), Integral(), Derivative(), Equation();
string TermInt(), FactorInt(), Monomial(), Monomial2(char), Coefficient(char, string), Polynomial();
void resetInt();

// Not part of the grammar
double integrate(string input);
