#include <iostream>

using namespace std;

int main()
{
	// task option 1: (x^2 - 7x + 10) / (x^2 - 8x + 12)
	int x;
	int y;

	cout << "Enter x: ";
	cin >> x;

	__asm__ ( 
		".intel_syntax noprefix\n\t"
		"mov eax, %1\n\t"
		"imul eax, %1\n\t" // x^2
		"mov ebx, %1\n\t"
		"imul ebx, 7\n\t" // 7x
		"sub eax, ebx\n\t" // x^2 - 7x
		"add eax, 10\n\t" // (x^2 - 7x + 10)	
		"mov ecx, %1\n\t"
		"imul ecx, %1\n\t" // x^2
		"mov edx, %1\n\t"
		"imul edx, 8\n\t" // 8x
		"sub ecx, edx\n\t" // x^2 - 8x
		"add ecx, 12\n\t" // (x^2 - 8x + 12)
		"cdq\n\t" // Расширяем eax до edx:eax для деления
		"idiv ecx\n\t" // (x^2 - 7x + 10) / (x^2 - 8x + 12)
		"mov %0, eax\n\t"
		".att_syntax prefix"
		: "=r"(y) /* выходные операнды */
		: "r"(x) /* входные операнды */
		: "%eax", "%ebx", "%ecx", "%edx" /* разрушаемые регистры */);
	
	cout << "asm y = (x^2 - 7x + 10) / (x^2 - 8x + 12) =" << y << endl;
	y = (x*x - 7*x + 10) / (x*x - 8*x + 12);
	cout << "cpp y = (x^2 - 7x + 10) / (x^2 - 8x + 12) =" << y << endl;

	return 0;
}