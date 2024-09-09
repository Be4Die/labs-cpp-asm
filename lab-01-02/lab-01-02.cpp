#include <iostream>

using namespace std;

int main()
{
	// task option 1: Y = a+b+c-d     
  

	int a;
	int b;
	int c;
	int d;
	int y;

	cout << "Enter a: ";
	cin >> a;
	cout << "Enter b: ";
	cin >> b;
	cout << "Enter c: ";
	cin >> c;
	cout << "Enter d: ";
	cin >> d;

	__asm {
		mov eax, a  // eax = a
		add eax, b  // eax = a + b
		add eax, c  // eax = a + b +c
		sub eax, d  // eax = a + b + c - d 
		mov y, eax  // move to y var
	}

	cout << "asm y=a + b + c - d = " << a << " + " << b << " + " << c << " - " << d << " = " << y << endl;
	y = a + b + c - d;
	cout << "cpp y=a + b + c - d = " << a << " + " << b << " + " << c << " - " << d << " = " << y << endl;

	return 0;
}