#ifndef ALLOCATOR_H
#define ALLOCATOR_H

class matrixRow
{
private:
    int* row;
    int sizeOfRow;
public:
    matrixRow();
    matrixRow(int* row, int sizeOfRow);
    int& operator[](int i);
};

class Matrix
{
private:
    int rows;
    int cols;
    matrixRow row;
    int * dataArray;
public:
    Matrix(int rows, int cols);
    ~Matrix();
    void zeros();
    void ones();
    void print();
    int getRows() const;
    int getColumns() const;
    void operator*=(const int scalar);
    matrixRow operator[](int idxOfRow);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
};

#endif