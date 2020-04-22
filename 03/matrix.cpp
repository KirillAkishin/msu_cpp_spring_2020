#include <iostream>

#include "matrix.h"

matrixRow::matrixRow(){}
matrixRow::matrixRow(int* in_row, size_t sizeOfRow)
{
    this->sizeOfRow = sizeOfRow;
    row = in_row;
}
int& matrixRow::operator[](size_t i) const
{
    if (i >= sizeOfRow)
        throw std::out_of_range("");
    return row[i];
}


Matrix::Matrix(size_t in_rows, size_t in_cols)
{
    this->dataArray = new int[in_rows*in_cols];
    rows = in_rows;
    cols = in_cols;
}
Matrix::~Matrix()
{
    delete [] dataArray;
}
Matrix::Matrix(Matrix const& copy)
  : rows(copy.rows), cols(copy.cols), dataArray(new int[copy.rows * copy.cols]) 
{
    size_t size = rows*cols;
    for (size_t i = 0; i < size; i++){
        dataArray[i] = copy.dataArray[i];
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
Matrix& Matrix::operator*=(const int scalar)
{
    size_t size = rows*cols;
    for (size_t i = 0; i < size; i++)
    {
        dataArray[i] *= scalar;
    }
    return *this;
}
const matrixRow Matrix::operator[](size_t idxOfRow) const
{
    if (idxOfRow >= rows)
        throw std::out_of_range("");
    int* ptrToRow = dataArray + (idxOfRow*cols);
    return matrixRow(ptrToRow,cols);
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
