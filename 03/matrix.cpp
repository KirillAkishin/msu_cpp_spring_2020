#include <iostream>

#include "matrix.h"

matrixRow::matrixRow(){}
matrixRow::matrixRow(size_t* in_row, size_t sizeOfRow)
{
    this->sizeOfRow = sizeOfRow;
    row = in_row;
}
size_t& matrixRow::operator[](size_t i)
{
    if (i >= sizeOfRow)
        throw std::out_of_range("");
    return row[i];
}


Matrix::Matrix(size_t in_rows, size_t in_cols)
{
    this->dataArray = new size_t[in_rows*in_cols];
    rows = in_rows;
    cols = in_cols;
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
    size_t size = rows*cols;
    for (size_t i = 0; i < size; i++)
    {
        dataArray[i] *= scalar;
    }
}
matrixRow Matrix::operator[](size_t idxOfRow)
{
    if (idxOfRow >= rows)
        throw std::out_of_range("");
    size_t* ptrToRow = dataArray + (idxOfRow*cols);
    row = matrixRow(ptrToRow,cols);
    return row;
}
bool Matrix::operator==(const Matrix& other) const
{
    if ((rows != other.getRows()) || (cols != other.getColumns()))
        return false;
    if (this == &other)
        return true;
    size_t size = rows * cols;
    for (size_t i = 0; i < size; i++){
        if (dataArray[i] != other.dataArray[i])
            return false;
    }
    return true;
}
bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}
