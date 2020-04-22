#include <iostream>
#include "matrix.h"


int testCases(char * name){
    Matrix m0(4,5);
    Matrix m1(4,5);
    Matrix m2(4,5);
    Matrix m3(2,3);
    const Matrix cm(4,5);
    m0.ones();
    m1.ones();
    m2.ones();
    m3.ones();
    cm.ones();
    int testNumber = 0;

    //T1 - getRows(), getColumns()
    testNumber++;
    if ((m0.getRows() != 4) || (m0.getColumns() != 5))
        return testNumber;
    if ((cm.getRows() != 4) || (cm.getColumns() != 5))
        return testNumber;

    //T2 - operator[][]
    testNumber++;
    m0[1][2] = 42;
    int temp = m0[1][2];
    if (temp != 42)
        return testNumber;
    cm[1][2] = 42;
    temp = cm[1][2];
    if (temp != 42)
        return testNumber;

    //T3 - operator*=
    testNumber++;
    m0 *= 3;
    if ((m0[0][0] != 3) || (m0[1][2] != 42*3))
        return testNumber;
    cm *= 3;
    if ((cm[0][0] != 3) || (cm[1][2] != 42*3))
        return testNumber;

    //T4 - operator==
    testNumber++;
    if (!(m1 == m2) || !(m1 == m1))
        return testNumber;
    if (!(cm == m0) || !(cm == cm))
        return testNumber;

    //T5 - operator!=
    testNumber++;
    m1[0][1] = 24;
    if (!(m1 != m2) || !(m2 != m3))
        return testNumber;
    if (!(m1 != cm) || !(cm != m3))
        return testNumber;

    //T6 - out_of_range for Matrix
    testNumber++;
    bool ok = false;
    try
    {
        m0[99][0];
    }
    catch (const std::out_of_range)    
    { 
        ok = true;
    }
    if (!ok)
        return testNumber;
    try
    {
        cm[99][0];
    }
    catch (const std::out_of_range)    
    { 
        ok = true;
    }
    if (!ok)
        return testNumber;

    //T7 - out_of_range for matrixRow
    testNumber++;
    ok = false;
    try
    {
        m0[0][99];
    }
    catch (const std::out_of_range)    
    { 
        ok = true;
    }
    if (!ok)
        return testNumber;
    try
    {
        cm[0][99];
    }
    catch (const std::out_of_range)    
    { 
        ok = true;
    }
    if (!ok)
        return testNumber;

    return 0;
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("test.exe run incorrectly\n");
        return 0;
    }
    char* name = argv[1];

    printf("\nTesting started...\n");
    int status = testCases(name);
    if (status != 0){
        printf("Test number %i failed\n", status);   
        return 1;
    }
    printf("All tests passed!\n");   
    return 0;
}
