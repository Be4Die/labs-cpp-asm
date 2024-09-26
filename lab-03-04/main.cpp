#include <iostream>

using namespace std;

int main()
{
	// task option 1: (x^2 - 7x + 10) / (x^2 - 8x + 12)

	const int t7 = 7;
	const int t10 = 10;
	const int t12 = 12;
	const int t8 = 8;

	int x;
	int y;

	cout << "Lab 03-04 | Nasledskov Michael | Task Option 1" << endl;
	cout << "Enter x: ";
	cin >> x;

	__asm {
		mov eax, x    // eax = x
		imul eax, x   // eax = x^2
		mov ebx, x    // ebx = x
		imul ebx, t7  // ebx = 7x
		sub eax, ebx  // eax = x^2 - 7x
		add eax, t10  // eax = (x^2 - 7x + 10)	
		mov ecx, x
		imul ecx, x   // ecx = x^2
		mov edx, x    // edx = x
		imul edx, t8  // edx = 8x
		sub ecx, edx  // ecx = x^2 - 8x
		add ecx, t12  // ecx = (x^2 - 8x + 12)
		cdq           // extend eax to edx:eax for div
		idiv ecx      // ecx =(x^2 - 7x + 10) / (x^2 - 8x + 12)
		mov y, eax    // move to y var
	}

	cout << "asm y = (x^2 - 7x + 10) / (x^2 - 8x + 12) = " << y << endl;
	y = (x * x - 7 * x + 10) / (x * x - 8 * x + 12);
	cout << "cpp y = (x^2 - 7x + 10) / (x^2 - 8x + 12) = " << y << endl;

	return 0;
}