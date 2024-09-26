#include <iostream>
#include <cmath>

using namespace std;

// task option general:
// Task 1:
// Given two integers n and k (n < k). 
// Find the sum of all numbers from n to k inclusive.
// 
// Task 2:
// Given two integers n and k (n < k, n > 0). 
// Find the product of all numbers from n to k inclusive.
// 
// Task 3:
// Given an array of integers X (positive and negative). 
// Find the sum of the squares of all numbers.
// 
// Task 4:
// Given an array of integers X (positive, zero and negative).
// Find the number of negative array elements.
// 
// Task 5:
// Given an array of positive integers X. 
// Find the maximum element of the array.

int main()
{
	const int t1 = 1;
	cout << "Lab 15-16 | Nasledskov Michael | Task Option general" << endl;

	int n, k, s;
	cout << "Task 1:" << endl;
	cout << "Enter n, k (n < k):" << endl; cin >> n >> k;

	__asm {
		mov eax, k
		sub eax, n
		mov ecx, eax
		mov eax, n // i
		mov ebx, n // sum
	t1loop:
		add eax, t1
		add ebx, eax
		loop t1loop

		mov s, ebx
	}
	cout << "asm sum=" << s << endl;
	s = n;
	for (int i = 1; i < (k-n)+1; i++) {
		s += n + i;
	}
	cout << "cpp sum=" << s << endl;

	int p;
	cout << "Task 2:" << endl;
	cout << "Enter n, k (n < k, n > 0):" << endl; cin >> n >> k;

	__asm {
		mov eax, k
		sub eax, n
		mov ecx, eax
		mov eax, n // i
		mov ebx, n // prod
	t2loop :
		add eax, t1
		imul ebx, eax
		loop t2loop

		mov p, ebx
	}

	cout << "asm prod=" << p << endl;
	p = n;
	for (int i = 1; i < (k - n) + 1; i++) {
		p *= (n + i);
	}
	cout << "cpp prod=" << p << endl;

	const int t0 = 0;
	const int t4 = 4;
	int arrsize, sqrSum;
	cout << "Task 3:" << endl;
	cout << "Enter size of array: ";  cin >> arrsize; 
	int* arr = new int[arrsize];
	for (int i = 0; i < arrsize; i++){
		cout << "Element " << i + 1 << ": "; cin >> arr[i];
	}

	__asm {
		mov esi, arr
		mov ecx, arrsize
		mov eax, t0
	t3loop :
		mov ebx, [esi]
		imul ebx, ebx
		add eax, ebx
		add esi, t4
		loop t3loop

		mov sqrSum, eax
	}
	cout << "asm sqr sum=" << sqrSum << endl;
	sqrSum = 0;
	for (int i = 0; i < arrsize; i++){
		sqrSum += arr[i] * arr[i];
	}
	cout << "cpp sqr sum=" << sqrSum << endl;

	int negCount;
	cout << "Task 4:" << endl;
	cout << "Enter size of array: ";  cin >> arrsize;
	for (int i = 0; i < arrsize; i++) {
		cout << "Element " << i + 1 << ": "; cin >> arr[i];
	}

	__asm {
		mov esi, arr
		mov ecx, arrsize
		mov eax, t0
	t4loop :
		mov ebx,[esi]
		cmp ebx, t0
		je skipMark
		jg skipMark
		inc eax
	skipMark:
		add esi, t4
		loop t4loop

		mov negCount, eax
	}

	cout << "asm neg count=" << negCount << endl;
	negCount = 0;
	for (int i = 0; i < arrsize; i++){
		if (arr[i] < 0) ++negCount;
	}
	cout << "cpp neg count=" << negCount << endl;

	int maxElement;
	cout << "Task 5:" << endl;
	cout << "Enter size of array: ";  cin >> arrsize;
	for (int i = 0; i < arrsize; i++) {
		cout << "Element " << i + 1 << ": "; cin >> arr[i];
	}

	__asm {
		mov esi, arr
		mov ecx, arrsize
		mov eax, [esi]
	t5loop :
		mov ebx, [esi]
		cmp ebx, eax
		jg setMax
		jmp nextElem
	setMax:
		mov eax, ebx
	nextElem:
		add esi, t4
		loop t5loop

		mov maxElement, eax
	}
	cout << "asm max=" << maxElement << endl;
	cout << "cpp max=" << *max_element(arr, arr + arrsize) << endl;

}