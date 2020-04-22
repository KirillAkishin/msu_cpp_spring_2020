#ifndef ALLOCATOR_H
#define ALLOCATOR_H

class matrixRow
{
private:
    int* row;
    size_t sizeOfRow;
public:
    matrixRow();
    matrixRow(int* row, size_t sizeOfRow);
    int& operator[](size_t i) const;
};

class Matrix
{
private:
    size_t rows;
    size_t cols;
    int * dataArray;
public:
    Matrix(size_t rows, size_t cols);
    ~Matrix();
    Matrix(Matrix const& copy);
    void ones() const;
    void print() const;
    size_t getRows() const;
    size_t getColumns() const;
    Matrix& operator*=(const int scalar);
    const Matrix operator*=(const int scalar) const;
    const matrixRow operator[](size_t idxOfRow) const;
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
};

#endif