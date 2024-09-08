#include <iostream>

int main()
{       
	int a = 5;
   	int b = 2;
	int c;

	__asm__ ( 
		".intel_syntax noprefix\n\t"
		"mov eax, %1\n\t"
		"mov ebx, %2\n\t"
		"sub eax, ebx\n\t"
		"mov %0, eax\n\t"
		".att_syntax prefix"
		: "=r"(c) /* выходные операнды */
		: "r"(a), "r"(b) /* входные операнды */
		: "%eax", "ebx" /* разрушаемые регистры */);

    printf("a - b = %x - %x = %x\n", a, b, c);
	c = a - b;
	printf("proverka\n");
	printf("a - b = %x - %x = %x\n", a, b, c);
	return 0;
}