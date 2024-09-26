#include <iostream>
#include <cmath>
#include <utility>

using namespace std;

extern "C" double calc1(double x);
extern "C" double calc2(double x);
extern "C" double calc31(double x1, double y1, double x2, double y2, double x3, double y3);
extern "C" double calc32(double x1, double y1, double x2, double y2, double x3, double y3);


int main() {
    double x;
    cout << "Lab 17-18 | Nasledskov Michael | Task Option 1" << endl;

    cout << "Task 1:" << endl;
    cout << "Enter x: "; cin >> x;
    cout << "asm (x^2-7x+10)/(x^2-8x+12)=" << calc1(x) << endl;
    cout << "cpp (x^2-7x+10)/(x^2-8x+12)=" << ((x * x - 7 * x + 10) / (x * x - 8 * x + 12)) << endl;

    cout << "Task 2:" << endl;
    cout << "Enter x: "; cin >> x;
    cout << "asm (1-cos(2x)+sin(2x)) / (1+cos(2x)+sin(2x))=" << calc2(x) << endl;
    cout << "cpp (1-cos(2x)+sin(2x)) / (1+cos(2x)+sin(2x))=" << (1 - cos(2 * x) + sin(2 * x))/ (1 + cos(2 * x) + sin(2 * x)) << endl;

    double x1, y1, x2, y2, x3, y3;
    cout << "Task 3:" << endl;
    cout << "Enter x1, y1, x2, y2, x3, y3: "; cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    cout << "asm p=" << calc31(x1, y1, x2, y2, x3, y3) << ", s=" << calc32(x1, y1, x2, y2, x3, y3) << endl;
    double dx1 = x1 - x2;
    double dx2 = x2 - x3;
    double dx3 = x3 - x1;

    double dy1 = y1 - y2;
    double dy2 = y2 - y3;
    double dy3 = y3 - y1;

    double a = sqrt(dx1 * dx1 + dy1 * dy1);
    double b = sqrt(dx2 * dx2 + dy2 * dy2);
    double c = sqrt(dx3 * dx3 + dy3 * dy3);
    double pp = (a + b + c) / 2.0;
    cout << "cpp p=" << a + b + c << ", s=" << sqrt(pp*(pp-a)*(pp-b)*(pp-c)) << endl;
    return 0;
}