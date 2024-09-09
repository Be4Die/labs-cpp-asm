#include <iostream>

using namespace std;

// task option <general>:
// 
// 1. Calculate y value: y = 
// { 
//     a + bx (if x > 0); 
//     x^2 (if x < 0); 
//     1 (if x == 0) 
// }
// 
// 2. Enter an integer. If it is positive, then add 1 to it; 
//    otherwise, don't change it. Print the resulting number.
// 
// 3. Enter three integers. Find the smallest of them.
// 
// 4. Enter three integers. Find the number of positive numbers in the original set.
// 
// 5. There are three points on the number axis: A, B, C. 
//    Determine which of the last two points (B or C) is located closer to A, display this point and its distance from point A.

int main()
{
	const int t0 = 0;
	const int t1 = 1;
	int a, b, x, y;

	cout << "Lab 07-08 | Nasledskov Michael | Task Option <general>" << endl;
	cout << "Task 1:" << endl;
	cout << "Enter a, b, x: " << endl; cin >> a >> b >> x;

	__asm {
		mov eax, x     // place x to eax
		cmp eax, t0    // compare eax with zero
		je ravno       // goto mark ravno
		jg bolshe      // goto mark bolshe
		mov ebx, eax   // place b to ebx
		imul ebx, eax  // x^2
		jmp konec      // goto mark konec
	bolshe: 
		mov ecx, a     // place a to ecx
        mov edx, b     // place b to edx
		imul edx, eax  // multiply b * x
		add ecx, edx   // a + bx
		mov ebx, ecx
		jmp konec
	ravno:  
		mov ebx, t1    // ebx = 1
	konec:  
		mov y, ebx     // place ebx to y
	}

	cout << "asm y = " << y << endl;

	if (x > 0) {
		y = a + b * x;
	}
	else if (x < 0) {
		y = x * x;
	}
	else if (x == 0) {
		y = 1;
	}
	cout << "cpp y = " << y << endl;

	int n, r;
	cout << "Task 2:" << endl; 
	cout << "Enter num: "; cin >> n;

	__asm {
		mov eax, n     // place n to eax
		cmp eax, t0    // compare eax with t0
		mov ebx, eax   // place n to ebx (default case)
		je konec2      // if n == t0, skip to the end
		jg bolshe2     // if n > t0, handle the greater case
		jmp konec2     // if n < t0, skip to the end
	bolshe2 :
		add ebx, t1    // ebx = n + t1 (if n > t0)
	konec2 :
		mov r, ebx     // place ebx to r
	}

	cout << "asm r = " << r << endl;

	if (n > 0) r = n + 1;
	else r = n;

	cout << "cpp r = " << r << endl;


	int n1, n2, n3, minN;
	cout << "Task 3:" << endl;
	cout << "Enter n1, n2, n3: " << endl; cin >> n1 >> n2 >> n3;

	__asm {
		mov eax, n1   // place n1
		mov ebx, n2   // place n2
		mov ecx, n3   // place n3
		cmp eax, ebx
		je comp2
		jg comp1
		jmp comp2     // n1 < n2 -> eax = n1
	comp1:
		mov eax, ebx  // n1 > n2 -> eax = n2
	comp2:
		cmp eax, ecx
		je endcomp
		jg comp3
		jmp endcomp   // eax < n3 -> eax = eax
	comp3:
		mov eax, ecx  // eax > ecx -> eax = ecx
		jmp endcomp
	endcomp:
		mov minN, eax
	}

	cout << "asm minN: " << minN << endl;

	cout << "cpp minN: " << min(n3, min(n1, n2)) << endl;

	int count;
	cout << "Task 4:" << endl;
	cout << "Enter n1, n2, n3: " << endl; cin >> n1 >> n2 >> n3;


	__asm {
		mov eax, n1   // place n1
		mov ebx, n2   // place n2
		mov ecx, n3   // place n3
		mov edx, t0
		cmp eax, t0
		je check2     // n1 == 0
		jg addone1    // n1 > 0
		jmp check2    // n1 < 0
	addone1:
		add edx, t1   // n1 positive add one
		jmp check2
	check2:
		cmp ebx, t0
		je check3     // n2 == 0
		jg addone2    // n2 > 0
		jmp check3    // n2 < 0
	addone2:
		add edx, t1
		jmp check3
	check3:
		cmp ecx, t0
		je endcount   // n3 == 0
		jg addone3    // n3 > 0
		jmp endcount  // n2 < 0
	addone3:
		add edx, t1
		jmp endcount
	endcount:
		mov count, edx
	}


	cout << "asm pos count: " << count << endl;
	count = 0;
	if (n1 > 0) ++count;
	if (n2 > 0) ++count;
	if (n3 > 0) ++count;
	cout << "cpp pos count: " << count << endl;

	int aPoint, bPoint, cPoint, nPoint, nPointLenght;
	cout << "Task 5:" << endl;
	cout << "Enter A point, B point, C point: " << endl; cin >> aPoint >> bPoint >> cPoint;

	__asm {
		mov eax, aPoint
		sub eax, cPoint  // eax diff a - c
		mov ebx, aPoint
		sub ebx, bPoint  // ebx diff a - b

		cmp eax, t0
		je cmpebx        // eax == 0 not need to inverse goto next
		jg cmpebx        // eax > 0 not need to inverse goto next
		neg eax          // eax = -eax inverse
		jmp cmpebx
	cmpebx:
		cmp ebx, t0
		je cmppnt        // ebx == 0 not need to inverse goto next
		jg cmppnt        // ebx > 0 not need to inverse goto next
		neg ebx          // ebx = -ebx inverse
		jmp cmppnt
	cmppnt:              // compare points
		cmp eax, ebx     
		je aplbpnt       // eax == ebx goto apply point B as result
		jg aplbpnt       // eax > ebx goto apply point B as result 
		mov ecx, cPoint
		mov edx, eax
		jmp aplpnt
	aplbpnt:
		mov ecx, bPoint
		mov edx, ebx
		jmp aplpnt
	aplpnt:
		mov nPoint, ecx
		mov nPointLenght, edx
	}
	
	cout << "asm near point of A: " << nPoint << ", lenght = " << nPointLenght << endl;

	if (abs(aPoint - cPoint) > abs(aPoint - bPoint)) nPoint = bPoint;
	else nPoint = cPoint;
	nPointLenght = abs(aPoint - nPoint);
	cout << "cpp near point of A: " << nPoint << ", lenght = " << nPointLenght << endl;
}