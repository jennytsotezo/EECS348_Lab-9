#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

// Template Matrix class to support either integer or double matrix data.
template <typename T>
class Matrix {
private:
    int N;    // Dimension (matrix is N x N)
    T* data;  // Dynamically allocated array to hold N*N elements
public:
    // Constructor: allocates memory for a matrix of size n x n.
    Matrix(int size) : N(size) {
        data = new T[N * N];
    }
    
    // Default constructor.
    Matrix() : N(0), data(nullptr) { }
    
    // Copy constructor (performs deep copy).
    Matrix(const Matrix<T>& other) {
        N = other.N;
        data = new T[N * N];
        for (int i = 0; i < N * N; i++) {
            data[i] = other.data[i];
        }
    }
    
    // Overloaded assignment operator (performs deep copy).
    Matrix<T>& operator=(const Matrix<T>& other) {
        if (this == &other)
            return *this;
        delete[] data;
        N = other.N;
        data = new T[N * N];
        for (int i = 0; i < N * N; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }
    
    // Destructor: frees allocated memory.
    ~Matrix() {
        delete[] data;
    }
    
    // Overloaded function call operator to access elements (with bounds checking).
    T& operator()(int i, int j) {
        if (i < 0 || i >= N || j < 0 || j >= N)
            throw out_of_range("Index out of range");
        return data[i * N + j];
    }
    
    // Const version for read-only access.
    const T& operator()(int i, int j) const {
        if (i < 0 || i >= N || j < 0 || j >= N)
            throw out_of_range("Index out of range");
        return data[i * N + j];
    }
    
    // Returns the matrix dimension.
    int size() const {
        return N;
    }
    
    // Overloaded extraction operator to input the matrix elements.
    friend istream& operator>>(istream& in, Matrix<T>& mat) {
        for (int i = 0; i < mat.N; i++) {
            for (int j = 0; j < mat.N; j++) {
                in >> mat(i, j);
            }
        }
        return in;
    }
    
    // Overloaded insertion operator to display the matrix with proper alignment.
    friend ostream& operator<<(ostream& out, const Matrix<T>& mat) {
        for (int i = 0; i < mat.N; i++) {
            for (int j = 0; j < mat.N; j++) {
                out << setw(8) << mat(i, j);
            }
            out << "\n";
        }
        return out;
    }
    
    // Operator overloading for matrix addition.
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (N != other.N)
            throw invalid_argument("Matrix sizes do not match for addition");
        Matrix<T> result(N);
        for (int i = 0; i < N * N; i++) {
            result.data[i] = this->data[i] + other.data[i];
        }
        return result;
    }
    
    // Operator overloading for matrix multiplication.
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (N != other.N)
            throw invalid_argument("Matrix sizes do not match for multiplication");
        Matrix<T> result(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                result(i, j) = 0;
                for (int k = 0; k < N; k++) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }
    
    // Computes the sum of the main and secondary diagonals.
    // If N is odd, the center element (common to both) is subtracted once.
    T diagonalSum() const {
        T sum = 0;
        for (int i = 0; i < N; i++) {
            sum += (*this)(i, i);            // Main diagonal
            sum += (*this)(i, N - 1 - i);      // Secondary diagonal
        }
        if (N % 2 == 1) { // Adjust for the center element counted twice.
            int mid = N / 2;
            sum -= (*this)(mid, mid);
        }
        return sum;
    }
    
    // Swaps two rows given their indices (0-based).
    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= N || row2 < 0 || row2 >= N)
            throw out_of_range("Row index out of bounds");
        for (int j = 0; j < N; j++) {
            T temp = (*this)(row1, j);
            (*this)(row1, j) = (*this)(row2, j);
            (*this)(row2, j) = temp;
        }
    }
    
    // Swaps two columns given their indices (0-based).
    void swapColumns(int col1, int col2) {
        if (col1 < 0 || col1 >= N || col2 < 0 || col2 >= N)
            throw out_of_range("Column index out of bounds");
        for (int i = 0; i < N; i++) {
            T temp = (*this)(i, col1);
            (*this)(i, col1) = (*this)(i, col2);
            (*this)(i, col2) = temp;
        }
    }
    
    // Updates the element at the given row and column with a new value.
    void updateElement(int row, int col, const T& newValue) {
        if (row < 0 || row >= N || col < 0 || col >= N)
            throw out_of_range("Index out of bounds");
        (*this)(row, col) = newValue;
    }
}; 

#endif // MATRIX_HPP