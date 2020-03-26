#include <iostream>

#include "matrix.h"

matrixRow::matrixRow(){}

matrixRow::matrixRow(int* row, int sizeOfRow)
{
    this->sizeOfRow = sizeOfRow;
    this->row = row;
}
int& matrixRow::operator[](int i)
{
    if (i >= sizeOfRow)
        throw std::out_of_range("");
    return row[i];
}


Matrix::Matrix(int rows, int cols)
{
    this->dataArray = new int[rows*cols];
    this->rows = rows;
    this->cols = cols;
}
Matrix::~Matrix()
{
    delete dataArray;
}
void Matrix::zeros()
{
    int size = rows * cols;
    for (int i = 0; i < size; i++){
        this->dataArray[i] = 0;
    }
}
void Matrix::ones()
{
    int size = rows * cols;
    for (int i = 0; i < size; i++){
        this->dataArray[i] = 1;
    }
}
void Matrix::print()
{
    for (int j = 0; j < rows; j++){
        for (int i = 0; i < cols; i++){
            std::cout << dataArray[i + j*cols] << " ";
        }
        std::cout << std::endl;
    }
}
int Matrix::getRows() const
{
    return rows;
}
int Matrix::getColumns() const
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
    int* ptrToRow = dataArray + (idxOfRow*cols);
    this->row = matrixRow(ptrToRow,cols);
    return row;
}
bool Matrix::operator==(const Matrix& other) const
{
    if ((this->rows != other.getRows()) || (this->cols != other.getColumns()))
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
