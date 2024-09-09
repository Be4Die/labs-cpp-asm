#include <iostream>

using namespace std;

int main()
{
	// task option 1: (x^2 - 7x + 10) / (x^2 - 8x + 12)


	const double t7 = 7;
	const double t10 = 10;
	const double t12 = 12;
	const double t8 = 8;

	double x;
	double y;

	cout << "Lab 05-06 | Nasledskov Michael | Task Option 1" << endl;
	cout << "Enter x: ";
	cin >> x;

	__asm {
		fld x            // Load x into the FPU stack (st(0) = x)
		fmul st, st(0)   // x^2 (st(0) = x^2)
		fld x            // Load x again (st(0) = x, st(1) = x^2)
		fld t7           // Load 7 (st(0) = 7, st(1) = x, st(2) = x^2)
		fmulp st(1), st  // Multiply x by 7 (st(0) = 7x, st(1) = x^2)
		fsubp st(1), st  // Subtract 7x from x^2 (st(0) = x^2 - 7x)
		fld t10          // Load 10 (st(0) = 10, st(1) = x^2 - 7x)
		faddp st(1), st  // Add 10 to x^2 - 7x (st(0) = x^2 - 7x + 10)

		fld x            // Load x again (st(0) = x, st(1) = x^2 - 7x + 10)
		fmul st, st(0)   // x^2 (st(0) = x^2, st(1) = x^2 - 7x + 10)
		fld x            // Load x again (st(0) = x, st(1) = x^2, st(2) = x^2 - 7x + 10)
		fld t8           // Load 8 (st(0) = 8, st(1) = x, st(2) = x^2, st(3) = x^2 - 7x + 10)
		fmulp st(1), st  // Multiply x by 8 (st(0) = 8x, st(1) = x^2, st(2) = x^2 - 7x + 10)
		fsubp st(1), st  // Subtract 8x from x^2 (st(0) = x^2 - 8x, st(1) = x^2 - 7x + 10)
		fld t12          // Load 12 (st(0) = 12, st(1) = x^2 - 8x, st(2) = x^2 - 7x + 10)
		faddp st(1), st  // Add 12 to x^2 - 8x (st(0) = x^2 - 8x + 12, st(1) = x^2 - 7x + 10)

		fdivp st(1), st  // Divide (x^2 - 7x + 10) by (x^2 - 8x + 12) (st(0) = result)
		fstp y           // Store the result in y
	}

	cout << "asm y = (x^2 - 7x + 10) / (x^2 - 8x + 12) = " << y << endl;
	y = (x * x - 7 * x + 10) / (x * x - 8 * x + 12);
	cout << "cpp y = (x^2 - 7x + 10) / (x^2 - 8x + 12) = " << y << endl;
}