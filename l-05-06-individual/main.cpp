#include <iostream>

using namespace std;

int main()
{
	// task option 1: (x^2 - 7x + 10) / (x^2 - 8x + 12)
	double x;
	double y;

	cout << "Enter x: ";
	cin >> x;

	__asm__ ( 
		".intel_syntax noprefix\n\t"
		"flds %1\n\t"
		".att_syntax prefix"
		: "=m"(y) /* выходные операнды */
		: "m"(x) /* входные операнды */
		: "%st" /* разрушаемые регистры */);
	
	cout << "asm y = (x^2 - 7x + 10) / (x^2 - 8x + 12) =" << y << endl;
	y = (x*x - 7*x + 10) / (x*x - 8*x + 12);
	cout << "cpp y = (x^2 - 7x + 10) / (x^2 - 8x + 12) =" << y << endl;

	return 0;
}