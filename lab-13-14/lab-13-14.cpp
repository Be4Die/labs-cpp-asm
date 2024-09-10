#include <iostream>
#include <cmath>

using namespace std;

// task option 1:
// Three real numbers are given. 
// Square those whose values ​​are non-negative, 
// and those whose values ​​are negative to the fourth power.

int main()
{
	const double t0 = 0;

	double a, b, c;
	double ra, rb, rc;

	cout << "Lab 13-14 | Nasledskov Michael | Task Option 1" << endl;
	cout << "Task 1:" << endl;
	cout << "Enter a, b, c: " << endl; cin >> a >> b >> c;

	__asm {
		fld a  // st(0)=a
		fld t0 // st(0)=0, st(1)=a
		fcomi st, st(1) // compare a and 0
		jae casea       // if a < 0, goto case1

		fxch st(1) // st(0)=a, st(1)=0
		fld a // st(0)=a, st(1)=a, st(2)=0
		fmul // st(0) = a^2, st(1) = 0
		fld a // st(0) = a, st(1) = a^2, st(2) = 0
		fmul  // st(0) = a^3, st(1) = 0
		fstp ra // st(0) = 0
		jmp checkb
	casea:
		fxch st(1) // st(0)=a, st(1)=0
		fld a // st(0)=a, st(1)=a, st(2)=0
		fmul // st(0) = a^2, st(1) = 0
		fld a // st(0) = a, st(1) = a^2, st(2) = 0
		fmul  // st(0) = a^3, st(1) = 0
		fld a // st(0) = a, st(1) = a^3, st(2) = 0
		fmul  // st(0) = a^4, st(1) = 0
		fstp ra // st(0) = 0
		jmp checkb
	checkb:
		fld b // st(0)=b, st(1)=0
		fxch st(1)
		fcomi st, st(1) // compare b and 0
		jae caseb	// if b < 0, goto case1

		fxch st(1) // st(0)=b, st(1)=0
		fld b // st(0)=b, st(1)=b, st(2)=0
		fmul // st(0) = b^2, st(1) = 0
		fld b // st(0) = b, st(1) = b^2, st(2) = 0
		fmul  // st(0) = b^3, st(1) = 0
		fstp rb // st(0) = 0
		jmp checkc
	caseb:
		fxch st(1) // st(0)=b, st(1)=0
		fld b // st(0)=b, st(1)=b, st(2)=0
		fmul // st(0) = b^2, st(1) = 0
		fld b // st(0) = b, st(1) = b^2, st(2) = 0
		fmul  // st(0) = b^3, st(1) = 0
		fld b // st(0) = b, st(1) = b^3, st(2) = 0
		fmul  // st(0) = b^4, st(1) = 0
		fstp rb // st(0) = 0
		jmp checkc
	checkc:
		fld c // st(0)=c, st(1)=0
		fxch st(1)
		fcomi st, st(1) // compare c and 0
		jae casec	// if c < -0, goto case1
		fxch st(1) // st(0)=c, st(1)=0
		fld c // st(0)=c, st(1)=c, st(2)=0
		fmul // st(0) = c^2, st(1) = 0
		fld c // st(0) = c, st(1) = c^2, st(2) = 0
		fmul  // st(0) = c^3, st(1) = 0
		fstp rc // st(0) = 0
		jmp endp
	casec:
		fxch st(1) // st(0)=c, st(1)=0
		fld c // st(0)=c, st(1)=c, st(2)=0
		fmul // st(0) = c^2, st(1) = 0
		fld c // st(0) = c, st(1) = c^2, st(2) = 0
		fmul  // st(0) = c^3, st(1) = 0
		fld c // st(0) = c, st(1) = c^3, st(2) = 0
		fmul  // st(0) = c^4, st(1) = 0
		fstp rc // st(0) = 0
		jmp endp
	endp:
	}
	cout << "asm a, b, c =" << ra << ", " << rb << ", " << rc << endl;


	if (a >= 0) ra = pow(a,3);
	else ra = pow(a, 4);
	if (b >= 0) rb = pow(b, 3);
	else rb = pow(b, 4);
	if (c >= 0) rc = pow(c, 3);
	else rc = pow(c, 4);

	cout << "cpp a, b, c =" << ra << ", " << rb << ", " << rc << endl;
}