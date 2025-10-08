#include <cmath>
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

class Rectangle {
private:
    double a, b; // rectangle sides

public:
    Rectangle(double sideA, double sideB) : a(sideA), b(sideB) {}

    // Standard area
    double square() const {
        return a * b; 
    }

    double square(char method) const {
        if (method == 'd' || method == 'D') {
            double d = sqrt(a * a + b * b);   // calculate diagonal
            return (d * d) / 2;               
        }
        else {
            throw invalid_argument("Unknown method for area calculation");
        }
    }


    double perimeter() const {
        return 2 * (a + b);
    }

    double diagonal() const {
        return sqrt(a * a + b * b);
    }

    void printInfo() const {
        cout << "Rectangle:" << endl;
        cout << "Side a = " << a << ", b = " << b << endl;
        cout << "Area = " << square() << endl;
        cout << "Perimeter = " << perimeter() << endl;
        cout << "Diagonal = " << diagonal() << endl;
        cout << "------------------------" << endl;
    }

    // overloaded print with title
    void printInfo(const string& title) const {
        cout << title << endl;
        printInfo();
    }

    // proportional increase (10%)
    Rectangle& operator++() {
        a *= 1.1;
        b *= 1.1;
        return *this;
    }

    // proportional decrease (10%)
    Rectangle& operator--() {
        a *= 0.9;
        b *= 0.9;
        if (a <= 0 || b <= 0)
            throw invalid_argument("Sides cannot be <= 0 after reduction");
        return *this;
    }
};

int main() {
    try {
        double a, b;
        cout << "Enter side a: ";
        cin >> a;
        cout << "Enter side b: ";
        cin >> b;

        Rectangle p(a, b);
        p.printInfo("Initial rectangle:");

        ++p;
        p.printInfo("After ++ :");

        --p;
        p.printInfo("After -- :");

        // test overloaded area method
        cout << "Area using diagonal method: " << p.square('d') << endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}