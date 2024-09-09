#include <iostream>
#include <cmath>

using namespace std;

// task option 1:
// 
// 1. Calculate y = f(x) value: f(x) = 
// { 
//     cosx / (x + 10) (x < -3)
//     e^(0.1x)        (-3 <= x < 4)  
//     lgx             (4 <= x < 6)
//     sin^2(x)        (x >= 6)
// }

int main()
{
	const double tn3 = -3.0;
	const double t4 = 4.0;
	const double t6 = 6.0;
	const double t10 = 10.0;
	const double t01 = 0.1;
	const double tt = 123.123;
	double x, y;

	cout << "Lab 11-12 | Nasledskov Michael | Task Option 1" << endl;
	cout << "Task 1:" << endl;
	cout << "Enter x: " << endl; cin >> x;

	__asm {
		fld x            // st(0)=x 
		fld tn3          // st(0)=-3, st(1)=x  
		fcomi st, st(1)  // compare x and - 3.0
		jae case1         // if x < -3.0, goto case1

		fld t4           // st(0)=4, st(1)=-3, st(2)=x  
		fcomi st, st(2)  // compare x and 4.0
		jae case2         // if - 3.0 <= x < 4.0, goto case2

		fld t6           // st(0)=6, st(1)=4, st(2)=-3, st(3)=x
		fcomi st, st(3)  // compare x and 6.0
		jae case3         // if 4.0 <= x < 6.0, goto case3

		jmp case4        //if x >= 6.0, goto case4
	case1:
		fld x            // st(0)=x, st(0)=-3, st(1)=x
		fld t10          // st(0)=10, st(1)=x, st(2)=-3, st(3)=x
		faddp st(1), st  // st(0) = x + 10, st(1)=-3, st(2)=x
		fld x            // st(0) = x, st(1) = x + 10, st(2)=-3, st(3)=x
		fcos             // st(0) = cosx, st(1) = x + 10, st(2)=-3, st(3)=x
		fxch st(1)       // st(0) = x + 10, st(1) = cosx, st(2)=-3, st(3)=x
		fdivp st(1), st
		jmp loady
	case2:
		fld t01          // st(0)=0.1, st(1)=4, st(2)=-3, st(3)=x
		fld x            // st(0)=x, st(1)=0.1, st(2)=4, st(3)=-3, st(4)=x
		fmul st, st(1)   // st(0)=x*0.1, st(1)=0.1, st(2)=4, st(3)=-3, st(4)=x
		fldl2e           // st(0) = ln(2), st(1) = x * 0.1, st(2) = 0.1, st(3)=4, st(4)=-3, st(5)=x
		fmul             // st(0) = ln(2) * x * 0.1, st(1) = 0.1, st(2)=4, st(3)=-3, st(4)=x
		fld st(0)        // st(0) = ln(2) * x * 0.1, st(1) = ln(2) * x * 0.1, st(2) = 0.1, st(3)=4, st(4)=-3, st(5)=x
		f2xm1            // st(0) = 2^(x * 0.1 * ln(2)) - 1, st(1) = x * 0.1 * ln(2), st(2) = 0.1, st(3)=4, st(4)=-3, st(5)=x
		fld1             // st(0) = 1, st(1) = 2^(x * 0.1 * ln(2)) - 1, st(2) = x * 0.1 * ln(2), st(3) = 0.1, st(4)=4, st(5)=-3, st(6)=x
		faddp st(1), st  // st(0) = 2^(x * 0.1 * ln(2)), st(1) = x * 0.1 * ln(2), st(2) = 0.1, st(3)=4, st(4)=-3, st(5)=x
		fscale           // st(0) = e^(x * 0.1), st(1) = x * 0.1 * ln(2), st(2) = 0.1, st(3)=4, st(4)=-3, st(5)=x
		fstp st(1)       // st(0) = e ^ (x * 0.1), st(1) = 0.1, st(3)=4, st(4)=-3, st(5)=x
		jmp loady
	case3:
		fld1             // st(0)=1, st(1)=6, st(2)=4, st(3)=-3, st(4)=x
		fld x            // st(0)=1, st(1)=x, st(2)=6, st(3)=4, st(4)=-3, st(5)=x
		fyl2x            // st(0)=log2(1), st(1)=6, st(2)=4, st(3)=-3, st(4)=x
		fldl2t           // st(0) = log2(10), st(1) = log2(x), st(2)=6, st(3)=4, st(4)=-3, st(5)=x
		fdivp st(1), st  // st(0) = log10(x), st(2)=6, st(3)=4, st(4)=-3, st(5)=x
		jmp loady
	case4:
		fld x            // st(0)=x, st(1)=6, st(2)=4, st(3)=-3, st(4)=x
		fsin             // st(0)=sinx, st(1)=6, st(2)=4, st(3)=-3, st(4)=x
		fld st(0)        // st(0)=sinx, st(1)=sinx, st(2)=6, st(3)=4, st(4)=-3, st(5)=x
		fmul st, st(1)   // st(0)=sin^2(x), st(1)=6, st(2)=4, st(3)=-3, st(4)=x
		jmp loady
	loady:
		fstp y
	}
	cout << "asm y = f(x) = " << y << endl;

	if (x < -3) y = cos(x) / (x + 10);
	else if (x >= -3 && x < 4) y = exp(0.1 * x);
	else if (x >= 4 && x < 6) y = log10(x);
	else if (x >= 6) y = pow(sin(x), 2);

	cout << "cpp y = f(x) = " << y << endl;
}