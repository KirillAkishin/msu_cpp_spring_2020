#ifndef ALLOCATOR_H
#define ALLOCATOR_H

class matrixRow
{
private:
    size_t* row;
    size_t sizeOfRow;
public:
    matrixRow();
    matrixRow(size_t* row, size_t sizeOfRow);
    size_t& operator[](size_t i) const;
};

class Matrix
{
private:
    size_t rows;
    size_t cols;
    size_t * dataArray;
public:
    Matrix(size_t rows, size_t cols);
    ~Matrix();
    Matrix(Matrix const& copy);
    void ones();
    void print();
    size_t getRows() const;
    size_t getColumns() const;
    Matrix& operator*=(const int scalar);
    const matrixRow operator[](size_t idxOfRow) const;
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
};

#endif