#include <iostream>      
#include <fstream>       
#include <cmath>        
#include <string>        

using namespace std;

const double PI = 3.14159265358979323846;

class Circle {
protected:
    double radius;
    string* circleData; // Something to destroy
public:
    Circle(double r) : radius(r) {
        circleData = new string("Circle data with radius: " + to_string(radius));
    }

    virtual double square() {
        return PI * radius * radius;
    }

    double circumference() {
        return 2 * PI * radius;
    }

    virtual string info() {
        return "Circle: radius = " + to_string(radius) +
            ", square = " + to_string(square()) +
            ", circumference = " + to_string(circumference());
    }

    virtual ~Circle() {
        cout << "Circle destructor: deleting circle data" << endl;
        delete circleData; // DESTROY DATA
    }
};

class RightTriangle {
protected:
    double a, b;
    string* triangleData; // Something to destroy
public:
    RightTriangle(double cat1, double cat2) : a(cat1), b(cat2) {
        triangleData = new string("Triangle data with legs: " + to_string(a) + ", " + to_string(b));
    }

    virtual double square() {
        return 0.5 * a * b;
    }

    double perimeter() {
        double c = sqrt(a * a + b * b);
        return a + b + c;
    }

    virtual string info() {
        return "Right triangle: legs = " + to_string(a) + ", " + to_string(b) +
            ", square = " + to_string(square()) +
            ", perimeter = " + to_string(perimeter());
    }

    virtual ~RightTriangle() {
        cout << "Triangle destructor: deleting triangle data" << endl;
        delete triangleData; // DESTROY DATA
    }
};

class InscribedRightTriangle : public Circle, public RightTriangle {
public:
    InscribedRightTriangle(double cat1, double cat2)
        : RightTriangle(cat1, cat2),
        Circle(sqrt(cat1* cat1 + cat2 * cat2) / 2) {}

    double square() override {
        return RightTriangle::square();
    }

    string info() {
        return "Right triangle inscribed in circle: legs = " + to_string(a) + ", " + to_string(b) +
            ", circumradius = " + to_string(radius) +
            ", triangle square = " + to_string(RightTriangle::square()) +
            ", triangle perimeter = " + to_string(perimeter()) +
            ", circle square = " + to_string(Circle::square()) +
            ", circle circumference = " + to_string(circumference());
    }
};

int main() {
    double cat1, cat2;

    cout << "Enter the first leg of the right triangle: ";
    cin >> cat1;
    cout << "Enter the second leg of the right triangle: ";
    cin >> cat2;

    InscribedRightTriangle triangle(cat1, cat2);

    // GET INDIVIDUAL AREAS:
    cout << "\n--- Individual Areas ---" << endl;
    cout << "Only triangle area: " << triangle.RightTriangle::square() << endl;
    cout << "Only circle area: " << triangle.Circle::square() << endl;

    // GET PERIMETER AND CIRCUMFERENCE:
    cout << "\n--- Perimeter and Circumference ---" << endl;
    cout << "Triangle perimeter: " << triangle.perimeter() << endl;
    cout << "Circle circumference: " << triangle.circumference() << endl;

    ofstream file("result.txt");
    if (file.is_open()) {
        file << "Shape information:" << endl;
        file << "==========================================" << endl;
        file << triangle.info() << endl;
        file.close();
        cout << "\nResults written to file 'result.txt'" << endl;
    }
    else {
        cout << "Error opening file!" << endl;
    }

    cout << "\nDestructors will clean up when program ends..." << endl;
    return 0;
}