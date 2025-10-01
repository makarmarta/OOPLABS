#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class my_vector {
private:
    size_t size;
    double* data;

public:
    my_vector(size_t n = 0, double value = 0.0) : size(n) {
        data = (size > 0) ? new double[size] : nullptr;
        for (size_t i = 0; i < size; i++) data[i] = value;
    }

    my_vector(const my_vector& other) : size(other.size) {
        data = (size > 0) ? new double[size] : nullptr;
        for (size_t i = 0; i < size; i++) data[i] = other.data[i];
    }

    my_vector& operator=(const my_vector& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        data = (size > 0) ? new double[size] : nullptr;
        for (size_t i = 0; i < size; i++) data[i] = other.data[i];
        return *this;
    }

    ~my_vector() { delete[] data; }

    size_t get_size() const { return size; }
    void set(size_t i, double val) { if (i < size) data[i] = val; }
    double get(size_t i) const { return (i < size) ? data[i] : 0.0; }

    void show() const {
        cout << "[ ";
        for (size_t i = 0; i < size; i++) cout << data[i] << " ";
        cout << "]" << endl;
    }
};


class matrix {
private:
    size_t rows, cols;
    my_vector* data;

public:
    matrix(size_t r = 0, size_t c = 0) : rows(r), cols(c) {
        data = (rows > 0) ? new my_vector[rows] : nullptr;
        for (size_t i = 0; i < rows; i++) data[i] = my_vector(cols, 0.0);
    }

    matrix(const matrix& other) : rows(other.rows), cols(other.cols) {
        data = (rows > 0) ? new my_vector[rows] : nullptr;
        for (size_t i = 0; i < rows; i++) data[i] = other.data[i];
    }

    matrix& operator=(const matrix& other) {
        if (this == &other) return *this;
        delete[] data;
        rows = other.rows; cols = other.cols;
        data = (rows > 0) ? new my_vector[rows] : nullptr;
        for (size_t i = 0; i < rows; i++) data[i] = other.data[i];
        return *this;
    }

    ~matrix() { delete[] data; }

    void set(size_t i, size_t j, double val) { if (i < rows) data[i].set(j, val); }

    double get(size_t i, size_t j) const { return (i < rows) ? data[i].get(j) : 0.0; }

    void show() const {
        for (size_t i = 0; i < rows; i++) data[i].show();
    }

    matrix add(const matrix& other) const {
        matrix res(rows, cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                res.set(i, j, get(i, j) + other.get(i, j));
        return res;
    }

    matrix sub(const matrix& other) const {
        matrix res(rows, cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                res.set(i, j, get(i, j) - other.get(i, j));
        return res;
    }

    my_vector mul(const my_vector& v) const {
        my_vector res(rows, 0.0);
        for (size_t i = 0; i < rows; i++) {
            double sum = 0;
            for (size_t j = 0; j < cols; j++) sum += get(i, j) * v.get(j);// Add the product of the matrix element to the vector element
            res.set(i, sum);
        }
        return res;
    }

    matrix mul(const matrix& other) const {
        matrix res(rows, other.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < other.cols; j++) {
                double sum = 0;
                for (size_t k = 0; k < cols; k++) sum += get(i, k) * other.get(k, j);
                res.set(i, j, sum);
            }
        }
        return res;
    }
};


int main() {
    srand(time(0)); 

    size_t r1, c1, r2, c2, v_size;

    cout << "Enter the dimensions of matrix A (rows and columns): ";
    cin >> r1 >> c1;
    matrix A(r1, c1);
    for (size_t i = 0; i < r1; i++)
        for (size_t j = 0; j < c1; j++)
            A.set(i, j, rand() % 21 - 10); // -10 to 10

    cout << "Enter the dimensions of matrix B (rows and columns): ";
    cin >> r2 >> c2;
    matrix B(r2, c2);
    for (size_t i = 0; i < r2; i++)
        for (size_t j = 0; j < c2; j++)
            B.set(i, j, rand() % 21 - 10);

    cout << "Enter the vector size: ";
    cin >> v_size;
    my_vector V(v_size);
    for (size_t i = 0; i < v_size; i++)
        V.set(i, rand() % 21 - 10);

    cout << "\nMatrix A:" << endl; A.show();
    cout << "Matrix B:" << endl; B.show();
    cout << "Vector V:" << endl; V.show();

    if (c1 == r2) {
        cout << "\nA * B:" << endl;
        A.mul(B).show();
    }
    else {
        cout << "\nMultiplication A * B is impossible (the sizes do not match)." << endl;
    }

    if (c1 == V.get_size()) {
        cout << "\nA * V:" << endl;
        A.mul(V).show();
    }
    else {
        cout << "\nMultiplication of A * V is impossible (vector size does not match)." << endl;
    }

    if (r1 == r2 && c1 == c2) {
        cout << "\nA + B:" << endl; A.add(B).show();
        cout << "A - B:" << endl; A.sub(B).show();
    }
    else {
        cout << "\nAdding/subtracting A and B is not possible (different sizes)." << endl;
    }
}
