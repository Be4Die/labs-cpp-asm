#include <iostream>

using namespace std;

// task option 1:
// 
// 1. Calculate y = f(x) value: f(x) = 
// { 
//     x^2 - 3x + 9 (if x <= 3); 
//     1 / (x^3 + 1) (else);  
// }

int main()
{
	const double t3 = 3.0;
	const double t9 = 9.0;
	const double t1 = 1.0;
	double x, y;

	cout << "Lab 09-10 | Nasledskov Michael | Task Option 1" << endl;
	cout << "Task 1:" << endl;
	cout << "Enter x: " << endl; cin >> x;

	__asm {
		fld t3  // st(0) = t3
		fld x   // st(0) = x, st(1) = t3
		fcomi st(0), st(1)  
		jbe iff  // if (x <= 3)
		jmp then  // else
	iff :
		fld t3              // st(0) = t3, st(1) = x, st(1) = t3
		fmul st, st(1)      // st(0) = 3x, st(1) = x, st(1) = t3
		fld x               // st(0) = x, st(1) = 3x, st(2) = x, st(3) = t3
		fmul st, st(2)      // st(0) = x^2, st(1) = 3x, st(2) = x, st(3) = t3
		fxch st(1)          // st(0) = 3x, st(1) = x^2, st(2) = x, st(3) = t3
		fsubp st(1), st     // st(0) = x^2 - 3x, st(1) = 3x, st(2) = x, st(3) = t3
		fld t9              // st(0) = t9, st(1) = x^2 - 3x, st(2) = 3x, st(3) = x, st(4) = t3
		faddp st(1), st     // st(0) = 9 + (x^2 - 3x), st(1) = x^2 - 3x, st(2) = 3x, st(3) = x, st(4) = t3
		jmp loady
	then :
		fld x               // st(0) = x, st(1) = x, st(2) = t3
		fmul st, st(1)      // st(0) = x^2, st(1) = x, st(2) = t3
		fmul st, st(1)      // st(0) = x^3, st(1) = x, st(2) = t3
		fld t1              // st(0) = t1, st(1) = x^3, st(2) = x, st(3) = t3
		faddp st(1), st     // st(0) = 1 + x^3, st(1) = x^3, st(2) = x, st(3) = t3
		fld t1              // st(0) = 1, st(1) = 1 + x^3, st(2) = x^3, st(3) = x, st(4) = t3
		fxch st(1)          // st(0) = 1 + x^3, st(1) = 1, st(2) = x^3, st(3) = x, st(4) = t
		fdivp st(1), st     // st(0) = 1 / (1 + x^3), st(1) = 1 + x^3, st(2) = x^3, st(3) = x, st(4) = t3
		jmp loady
	loady :
		fstp y              // unload st(0) to y
	}

	cout << "asm y = f(x) = " << y << endl;

	if (x <= 3) y = x * x - 3 * x + 9;
	else y = 1.0 / (x * x * x + 1);

	cout << "cpp y = f(x) = " << y << endl;
}