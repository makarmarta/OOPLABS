#include<iostream>
#include <iomanip>
#include<math.h>

using namespace std;

double calculation_a(double x, double y, double z, double b) {

    double top = z + pow(sin(y), 2) + pow(y + b, 1.3);

    
    double bottom1 = (x * x + y) / (y + x * x * x / 3);
    double bottom2 = z * z + fabs(bottom1) - pow(log(fabs(z)), 2);

    return y * y + top / bottom2;
}

double calculation_b(double x, double y, double z) {
    double part1 = (1 + pow(cos(y - 2 * x * x * x), 2));
    double part2 = (2 + pow(fabs(x), 1.5) - pow(sin(pow(fabs(z), 0.2)), 2));
    double part3 = pow(log(fabs(z - y)), 2);

    return part1 / part2 + part3;
}

int main() {
    int n;
    cout << "Enter variante number:";
    cin >> n;

    double x = 0.48 * n;
    double y = 0.47 * n;
    double z = -1.32 * n;

    double b = calculation_b(x, y, z);
    cout << "Function value b = " << b << endl;

    double a = calculation_a(x, y, z, b);
    cout << "Function value a = " << a << endl;

    cout << "   x\t\tb(x)\t\t\ta(x)" << endl;
    cout << "----------------------------------------------------" << endl;

    double start = -1;
    double end = 1;
    double step = 0.2;

    cout << fixed << setprecision(6);

    for (double x = start; x <= end; x += step) {
        if (fabs(x) < 1e-12) x = 0;

        b = calculation_b(x, y, z);
        a = calculation_a(x, y, z, b);

        cout << x << "   \t   " << b << "   \t   " << a << endl;
    }

    return 0;
}