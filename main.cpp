#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "matrix.hpp" // Include the custom Matrix class definition

using namespace std;

int main(int argc, char* argv[]) {
    // Check for the required input file.
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    
    ifstream infile(argv[1]);
    if (!infile.is_open()){
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }
    
    // Read matrix size (N) and type flag (0 for int, 1 for double)
    int N, typeFlag;
    infile >> N >> typeFlag;
    
    // Ignore the rest of the first line
    infile.ignore();
    
    try {
        if (typeFlag == 0) { // Use integer matrices
            Matrix<int> mat1(N);
            Matrix<int> mat2(N);
            
            // Read the two matrices from the file
            infile >> mat1;
            infile >> mat2;
            
            // Display the matrices
            cout << "Matrix 1:" << endl;
            cout << mat1 << endl;
            
            cout << "Matrix 2:" << endl;
            cout << mat2 << endl;
            
            // 1. Matrix Addition
            Matrix<int> sum = mat1 + mat2;
            cout << "Addition (Matrix 1 + Matrix 2):" << endl;
            cout << sum << endl;
            
            // 2. Matrix Multiplication
            Matrix<int> product = mat1 * mat2;
            cout << "Multiplication (Matrix 1 * Matrix 2):" << endl;
            cout << product << endl;
            
            // 3. Diagonal Sum of Matrix 1 (main and secondary diagonals)
            int diagSum = mat1.diagonalSum();
            cout << "Sum of main and secondary diagonals of Matrix 1: " << diagSum << "\n" << endl;
            
            // 4. Swap rows in Matrix 1 (demonstration)
            int r1, r2;
            cout << "Enter two row indices to swap in Matrix 1 (0-based index): ";
            cin >> r1 >> r2;
            mat1.swapRows(r1, r2);
            cout << "Matrix 1 after swapping rows " << r1 << " and " << r2 << ":" << endl;
            cout << mat1 << endl;
            
            // 5. Swap columns in Matrix 1 (demonstration)
            int c1, c2;
            cout << "Enter two column indices to swap in Matrix 1 (0-based index): ";
            cin >> c1 >> c2;
            mat1.swapColumns(c1, c2);
            cout << "Matrix 1 after swapping columns " << c1 << " and " << c2 << ":" << endl;
            cout << mat1 << endl;
            
            // 6. Update an element in Matrix 1 (demonstration)
            int row, col, newValue;
            cout << "Enter row index, column index, and new value to update in Matrix 1: ";
            cin >> row >> col >> newValue;
            mat1.updateElement(row, col, newValue);
            cout << "Matrix 1 after updating element at (" << row << ", " << col << "):" << endl;
            cout << mat1 << endl;
        }
        else if (typeFlag == 1) { // Use double matrices
            Matrix<double> mat1(N);
            Matrix<double> mat2(N);
            
            // Read the two matrices from the file
            infile >> mat1;
            infile >> mat2;
            
            // Display the matrices
            cout << "Matrix 1:" << endl;
            cout << mat1 << endl;
            
            cout << "Matrix 2:" << endl;
            cout << mat2 << endl;
            
            // 1. Matrix Addition
            Matrix<double> sum = mat1 + mat2;
            cout << "Addition (Matrix 1 + Matrix 2):" << endl;
            cout << sum << endl;
            
            // 2. Matrix Multiplication
            Matrix<double> product = mat1 * mat2;
            cout << "Multiplication (Matrix 1 * Matrix 2):" << endl;
            cout << product << endl;
            
            // 3. Diagonal Sum of Matrix 1 (main and secondary diagonals)
            double diagSum = mat1.diagonalSum();
            cout << "Sum of main and secondary diagonals of Matrix 1: " << diagSum << "\n" << endl;
            
            // 4. Swap rows in Matrix 1 (demonstration)
            int r1, r2;
            cout << "Enter two row indices to swap in Matrix 1 (0-based index): ";
            cin >> r1 >> r2;
            mat1.swapRows(r1, r2);
            cout << "Matrix 1 after swapping rows " << r1 << " and " << r2 << ":" << endl;
            cout << mat1 << endl;
            
            // 5. Swap columns in Matrix 1 (demonstration)
            int c1, c2;
            cout << "Enter two column indices to swap in Matrix 1 (0-based index): ";
            cin >> c1 >> c2;
            mat1.swapColumns(c1, c2);
            cout << "Matrix 1 after swapping columns " << c1 << " and " << c2 << ":" << endl;
            cout << mat1 << endl;
            
            // 6. Update an element in Matrix 1 (demonstration)
            int row, col;
            double newValue;
            cout << "Enter row index, column index, and new value to update in Matrix 1: ";
            cin >> row >> col >> newValue;
            mat1.updateElement(row, col, newValue);
            cout << "Matrix 1 after updating element at (" << row << ", " << col << "):" << endl;
            cout << mat1 << endl;
        }
        else {
            cerr << "Invalid type flag in input file. Use 0 for int or 1 for double." << endl;
            return 1;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    infile.close();
    return 0;
}