#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <initializer_list>
using namespace std;

template <typename T>
class Matrix {
private:
    int N;    // Dimension: matrix is N x N.
    T* data;  // Pointer to dynamically allocated array holding N*N elements.
public:
    // Default constructor.
    Matrix() : N(0), data(nullptr) {}

    // Constructor that takes the dimension.
    Matrix(int size) : N(size) {
        if (size <= 0)
            throw invalid_argument("Matrix size must be positive.");
        data = new T[N * N];
    }

    // Constructor from a brace-enclosed initializer list.
    Matrix(initializer_list<initializer_list<T>> list) {
        N = list.size();
        if (N == 0) {
            data = nullptr;
            return;
        }
        data = new T[N * N];
        int i = 0;
        for (auto row : list) {
            if (row.size() != static_cast<size_t>(N))
                throw invalid_argument("All rows must contain exactly N elements.");
            int j = 0;
            for (auto val : row) {
                (*this)(i, j) = val;
                j++;
            }
            i++;
        }
    }

    // Constructor from a two-dimensional vector.
    Matrix(const vector<vector<T>>& vec) {
        N = vec.size();
        if (N == 0) {
            data = nullptr;
            return;
        }
        data = new T[N * N];
        for (int i = 0; i < N; i++) {
            if (vec[i].size() != static_cast<size_t>(N))
                throw invalid_argument("Each row must have size equal to N.");
            for (int j = 0; j < N; j++) {
                (*this)(i, j) = vec[i][j];
            }
        }
    }

    // Copy constructor.
    Matrix(const Matrix<T>& other) {
        N = other.N;
        if (N > 0) {
            data = new T[N * N];
            for (int i = 0; i < N * N; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }

    // Assignment operator.
    Matrix<T>& operator=(const Matrix<T>& other) {
        if (this == &other)
            return *this;
        delete[] data;
        N = other.N;
        if (N > 0) {
            data = new T[N * N];
            for (int i = 0; i < N * N; i++)
                data[i] = other.data[i];
        } else {
            data = nullptr;
        }
        return *this;
    }

    // Destructor.
    ~Matrix() {
        delete[] data;
    }

    // Element access with bounds checking.
    T& operator()(int i, int j) {
        if (i < 0 || i >= N || j < 0 || j >= N)
            throw out_of_range("Index out of range");
        return data[i * N + j];
    }

    // Const element access.
    const T& operator()(int i, int j) const {
        if (i < 0 || i >= N || j < 0 || j >= N)
            throw out_of_range("Index out of range");
        return data[i * N + j];
    }

    // Returns the size of the matrix.
    int get_size() const {
        return N;
    }

    // Returns the value at position (i, j).
    T get_value(int i, int j) const {
        return (*this)(i, j);
    }

    // Sets the value at position (i, j) to newValue.
    void set_value(int i, int j, const T& newValue) {
        (*this)(i, j) = newValue;
    }

    // Returns the sum of the major (main) diagonal elements.
    T sum_diagonal_major() const {
        T sum = 0;
        for (int i = 0; i < N; i++) {
            sum += (*this)(i, i);
        }
        return sum;
    }

    // Returns the sum of the minor (secondary) diagonal elements.
    T sum_diagonal_minor() const {
        T sum = 0;
        for (int i = 0; i < N; i++) {
            sum += (*this)(i, N - 1 - i);
        }
        return sum;
    }

    // Swaps two rows (row indices are 0-based).
    void swap_rows(int row1, int row2) {
        if (row1 < 0 || row1 >= N || row2 < 0 || row2 >= N)
            throw out_of_range("Row index out of range");
        for (int j = 0; j < N; j++) {
            T temp = (*this)(row1, j);
            (*this)(row1, j) = (*this)(row2, j);
            (*this)(row2, j) = temp;
        }
    }

    // Swaps two columns (column indices are 0-based).
    void swap_cols(int col1, int col2) {
        if (col1 < 0 || col1 >= N || col2 < 0 || col2 >= N)
            throw out_of_range("Column index out of range");
        for (int i = 0; i < N; i++) {
            T temp = (*this)(i, col1);
            (*this)(i, col1) = (*this)(i, col2);
            (*this)(i, col2) = temp;
        }
    }

    // Overloaded addition operator.
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (N != other.N)
            throw invalid_argument("Matrix sizes do not match for addition.");
        Matrix<T> result(N);
        for (int i = 0; i < N * N; i++) {
            result.data[i] = this->data[i] + other.data[i];
        }
        return result;
    }

    // Overloaded multiplication operator.
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (N != other.N)
            throw invalid_argument("Matrix sizes do not match for multiplication.");
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

    // Overloaded extraction operator for input.
    friend istream& operator>>(istream& in, Matrix<T>& mat) {
        for (int i = 0; i < mat.N; i++) {
            for (int j = 0; j < mat.N; j++) {
                in >> mat(i, j);
            }
        }
        return in;
    }

    // Overloaded insertion operator for output.
    friend ostream& operator<<(ostream& out, const Matrix<T>& mat) {
        for (int i = 0; i < mat.N; i++) {
            for (int j = 0; j < mat.N; j++) {
                out << setw(8) << mat(i, j);
            }
            out << "\n";
        }
        return out;
    }
};

#endif // MATRIX_HPP