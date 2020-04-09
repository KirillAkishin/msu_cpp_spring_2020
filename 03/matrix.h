#ifndef ALLOCATOR_H
#define ALLOCATOR_H

class matrixRow
{
private:
    size_t* row;
    int sizeOfRow;
public:
    matrixRow();
    matrixRow(size_t* row, int sizeOfRow);
    size_t& operator[](int i);
};

class Matrix
{
private:
    size_t rows;
    size_t cols;
    matrixRow row;
    size_t * dataArray;
public:
    Matrix(size_t rows, size_t cols);
    ~Matrix();
    void zeros();
    void ones();
    void print();
    size_t getRows() const;
    size_t getColumns() const;
    void operator*=(const int scalar);
    matrixRow operator[](int idxOfRow);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
};

#endif