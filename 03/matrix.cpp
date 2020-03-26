// Нужно написать класс-матрицу, тип элементов int. 
// В конструкторе задается количество рядов и строк. 
// Поддерживаются оперции: получить количество строк(rows)/столбцов(columns), 
// получить конкретный элемент, умножить на число(*=), сравнение на равенство/неравенство. 
// В случае ошибки выхода за границы бросать исключение:
#include <iostream>

#include "matrix.h"

class matrixRow{
    int* row;
    int sizeOfRow;
    public:
        matrixRow(){}
        matrixRow(int* row, int sizeOfRow)
        {
            this->sizeOfRow = sizeOfRow;
            this->row = row;
        }
        int& operator[](int i)
        {
            if (i >= sizeOfRow)
                throw std::out_of_range("");
            return row[i];
        }
};

class Matrix{
    int rows;
    int cols;
    matrixRow row;
    int * dataArray;
    public:

        Matrix(int rows, int cols){
            this->dataArray = new int[rows*cols];
            this->rows = rows;
            this->cols = cols;
            // matrixRow();
        }
        ~Matrix(){
            delete dataArray;
        }
        void zeros()
        {
            int size = rows * cols;
            for (int i = 0; i < size; i++){
                this->dataArray[i] = 0;
            }
        }
        void ones()
        {
            int size = rows * cols;
            for (int i = 0; i < size; i++){
                this->dataArray[i] = 1;
            }
        }
        void print()
        {
            for (int j = 0; j < rows; j++){
                for (int i = 0; i < cols; i++){
                    std::cout << dataArray[i + j*cols] << " ";
                }
                std::cout << std::endl;
            }
        }
        int getRows() const
        {
            return rows;
        }
        int getColumns() const
        {
            return cols;
        }
        void operator*=(const int scalar)
        {
            int size = rows*cols;
            for (int i = 0; i < size; i++)
            {
                this->dataArray[i] *= scalar;
            }
        }
        matrixRow operator[](int idxOfRow)
        {
            if (idxOfRow >= rows)
                throw std::out_of_range("");
            int* ptrToRow = dataArray + (idxOfRow*cols);
            this->row = matrixRow(ptrToRow,cols);
            // this->row(ptrToRow,cols)
            return row;
        }
        bool operator==(const Matrix& other) const
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
        bool operator!=(const Matrix& other) const
        {
            if ((this->rows != other.getRows()) || (this->cols != other.getColumns()))
                return true;
            if (this == &other)
                return false;
            int size = rows * cols;
            for (int i = 0; i < size; i++){
                if (this->dataArray[i] != other.dataArray[i])
                    return true;
            }
            return false;
        }
};

int main(){
    Matrix m(2, 4);
    m.ones();
    m[1][2] = 42;
    m.print();
    m *= 2;
    m.print();
    // std::cout << m[1][1] << std::endl;
    if (m == m)
        std::cout << "OK-1" << std::endl;
    Matrix m1(5,6);
    Matrix m2(5,6);
    m1.ones();
    m2.ones();
    if (m1 == m2)
        std::cout << "OK-2" << std::endl;
    m2[4][9] = 123;
    if (m1 != m2)
        std::cout << "OK-3" << std::endl;
    if (m1 != m)
        std::cout << "OK-4" << std::endl;
    else 
        std::cout << "NO OK-4" << std::endl;
    return 0;
}

