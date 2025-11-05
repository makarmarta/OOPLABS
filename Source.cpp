#include <iostream>
#include <cmath>
using namespace std;

// Base class Circle
class Circle {
protected:
    double radius;
    const double PI = 3.14159;
public:
    Circle(double r) : radius(r) {}

    // Virtual methods
    virtual double getLength() const {
        return 2 * PI * radius;
    }

    virtual void showInfo() const {
        cout << "Circle with radius: " << radius << endl;
        cout << "Circumference: " << getLength() << endl;
    }

    virtual ~Circle() {}  // Virtual destructor for proper cleanup
};

//class Disk (inherits from Circle)
class Disk : public Circle {
public:
    Disk(double r) : Circle(r) {}

    // Override virtual methods
    double getArea() const {
        return PI * radius * radius;
    }

    void showInfo() const override {
        cout << "Disk with radius: " << radius << endl;
        cout << "Circumference: " << getLength() << endl;
        cout << "Area: " << getArea() << endl;
    }
};

//  class Cylinder (inherits from Disk)
class Cylinder : public Disk {
private:
    double height;
public:
    Cylinder(double r, double h) : Disk(r), height(h) {}

    // Additional methods for cylinder
    double getVolume() const {
        return getArea() * height;
    }

    double getSideArea() const {
        return getLength() * height;
    }

    double getFullArea() const {
        return 2 * getArea() + getSideArea();
    }

    void showInfo() const override {
        cout << "Cylinder with radius: " << radius << " and height: " << height << endl;
        cout << "Base circumference: " << getLength() << endl;
        cout << "Base area: " << getArea() << endl;
        cout << "Side surface area: " << getSideArea() << endl;
        cout << "Total surface area: " << getFullArea() << endl;
        cout << "Volume: " << getVolume() << endl;
    }
};

int main() {
    double radius, height;

    // Get user input for Circle
    cout << "Enter radius for Circle: ";
    cin >> radius;

    // Get user input for Disk
    double diskRadius;
    cout << "Enter radius for Disk: ";
    cin >> diskRadius;

    // Get user input for Cylinder
    double cylinderRadius, cylinderHeight;
    cout << "Enter radius for Cylinder: ";
    cin >> cylinderRadius;
    cout << "Enter height for Cylinder: ";
    cin >> cylinderHeight;

    // Polymorphism demonstration
    Circle* shapes[3];  // Array of pointers to base class

    // Creating different objects but storing them as base class pointers
    shapes[0] = new Circle(radius);                    
    shapes[1] = new Disk(diskRadius);                
    shapes[2] = new Cylinder(cylinderRadius, cylinderHeight);   

    cout << "\n=== Polymorphism Demonstration ===" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "\n--- Shape " << (i + 1) << " ---" << endl;
        shapes[i]->showInfo();  // Each object calls its OWN showInfo() method
    }

    // Memory cleanup
    for (int i = 0; i < 3; i++) {
        delete shapes[i];  // Virtual destructor ensures proper cleanup
    }

    // Demonstration of individual objects
    cout << "\n=== Individual Objects ===" << endl;

    Circle circle(radius);
    cout << "\n--- Circle ---" << endl;
    circle.showInfo();

    Disk disk(diskRadius);
    cout << "\n--- Disk ---" << endl;
    disk.showInfo();

    Cylinder cylinder(cylinderRadius, cylinderHeight);
    cout << "\n--- Cylinder ---" << endl;
    cylinder.showInfo();

    return 0;
}