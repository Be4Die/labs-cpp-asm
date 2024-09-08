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

	__asm__ ( 
		".intel_syntax noprefix\n\t"
		"mov eax, %1\n\t"
		"add eax, %2\n\t"
		"add eax, %3\n\t"
		"sub eax, %4\n\t"
		"mov %0, eax\n\t"
		".att_syntax prefix"
		: "=r"(y) /* выходные операнды */
		: "r"(a), "r"(b), "r"(c), "r"(d) /* входные операнды */
		: "%eax" /* разрушаемые регистры */);
	
	cout << "asm y=a + b + c - d = " << a << " + " << b <<  " + " << c << " - " << d << " = " << y << endl;
	y = a + b + c - d;
	cout << "cpp y=a + b + c - d = " << a << " + " << b <<  " + " << c << " - " << d << " = " << y << endl;

	return 0;
}