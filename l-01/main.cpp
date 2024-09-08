#include <iostream>

int main()
{       
	int a = 1;
   	int b = 2;
	int c;

	__asm__ ( 
		".intel_syntax noprefix\n\t"
		"mov eax, %1\n\t"
		"add eax, %2\n\t"
		"mov %0, eax\n\t"
		".att_syntax prefix"
		: "=r"(c) /* выходные операнды */
		: "r"(a), "r"(b) /* входные операнды */
		: "%eax" /* разрушаемые регистры */);

    printf("a + b = %x + %x = %x\n", a, b, c);
	return 0;
}