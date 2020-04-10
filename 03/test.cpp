#include <iostream>

#include "matrix.h"


int testCases(char * name){
    Matrix m0(2,3);
    Matrix m1(4,5);
    Matrix m2(4,5);
    m0.ones();
    m1.ones();
    m2.ones();
    const Matrix ctM = m2;
    int testNumber = 0;

    //T1 - getRows(), getColumns()
    testNumber++;
    if ((m0.getRows() != 2) || (m1.getColumns() != 5))
        return testNumber;
    if ((ctM.getRows() != 4) || (ctM.getColumns() != 5))
        return testNumber;

    //T2 - operator[][]
    testNumber++;
    m0[1][2] = 42;
    int temp = m0[1][2];
    if (temp != 42)
        return testNumber;
    if (ctM[0][0] != m2[0][0])
        return testNumber;

    //T3 - operator*=
    testNumber++;
    m0 *= 3;
    if ((m0[0][0] != 3) || (m0[1][2] != 42*3))
        return testNumber;

    //T4 - operator==
    testNumber++;
    if (!(m1 == m2) || !(m1 == m1))
        return testNumber;
    if (!(ctM == m2) || !(ctM == ctM))
        return testNumber;

    //T5 - operator!=
    testNumber++;
    m1[3][4] = 5;
    if (!(m0 != m2) || !(m1 != m2))
        return testNumber;
    if (!(m0 != ctM) || !(m1 != ctM))
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
        ctM[99][0];
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
        ctM[0][99];
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
