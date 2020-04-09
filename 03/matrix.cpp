#include <iostream>

#include "matrix.h"

matrixRow::matrixRow(){}

matrixRow::matrixRow(size_t* row, int sizeOfRow)
{
    this->sizeOfRow = sizeOfRow;
    this->row = row;
}
size_t& matrixRow::operator[](int i)
{
    if (i >= sizeOfRow)
        throw std::out_of_range("");
    return row[i];
}


Matrix::Matrix(size_t rows, size_t cols)
{
    this->dataArray = new size_t[rows*cols];
    this->rows = rows;
    this->cols = cols;
}
Matrix::~Matrix()
{
    delete [] dataArray;
}
void Matrix::zeros()
{
    size_t size = rows * cols;
    for (size_t i = 0; i < size; i++){
        dataArray[i] = 0;
    }
}
void Matrix::ones()
{
    size_t size = rows * cols;
    for (size_t i = 0; i < size; i++){
        dataArray[i] = 1;
    }
}
void Matrix::print()
{
    for (size_t j = 0; j < rows; j++){
        for (size_t i = 0; i < cols; i++){
            std::cout << dataArray[i + j*cols] << " ";
        }
        std::cout << std::endl;
    }
}
size_t Matrix::getRows() const
{
    return rows;
}
size_t Matrix::getColumns() const
{
    return cols;
}
void Matrix::operator*=(const int scalar)
{
    int size = rows*cols;
    for (int i = 0; i < size; i++)
    {
        this->dataArray[i] *= scalar;
    }
}
matrixRow Matrix::operator[](int idxOfRow)
{
    if (idxOfRow >= rows)
        throw std::out_of_range("");
    size_t* ptrToRow = dataArray + (idxOfRow*cols);
    this->row = matrixRow(ptrToRow,cols);
    return row;
}
bool Matrix::operator==(const Matrix& other) const
{
    if ((rows != other.getRows()) || (cols != other.getColumns()))
        return false;
    if (this == &other)
        return true;
    int size = rows * cols;
    for (int i = 0; i < size; i++){
        if (this->dataArray[i] != other.dataArray[i])
            return false;
    }
    return true;
}
bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}
