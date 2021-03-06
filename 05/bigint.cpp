#include <iostream>
#include <cstring>
#include <algorithm>
#include "bigint.h"

BigInt::BigInt(const char *x)
{
    int begin = 0;
    if (x[0] == '-')
    {
        positive = false;
        begin = 1;
        len = strlen(x) - 1;
    }
    else
    {
        begin = 0;
        len = strlen(x);
    }
    numbers = new char[len+1];
    for (size_t i=begin; i<len+begin; i++)
        numbers[i-begin] = (char)x[i];
}

BigInt::BigInt()
    : numbers(nullptr), len(0) {}

BigInt::BigInt(const BigInt &bint)
    : len(bint.getLen()), positive(bint.isPositive())
{
    numbers = new char[len+1];
    for (size_t i=0; i<len; i++)
        numbers[i] = bint.numbers[i];
}

BigInt &BigInt::operator=(BigInt bint)
{
    if (this == &bint)
        return *this;
    len = bint.getLen();
    positive = bint.isPositive();
    char *new_numbers = new char[bint.getLen()+1];
    delete [] numbers;
    numbers = new_numbers;
    for (size_t i=0; i<len; i++)
        numbers[i] = bint.numbers[i];  
    return *this;
}

void BigInt::fill(char *mass, size_t l, bool pos)
{
    positive = pos;
    numbers = new char[l+1];
    len = l;
    for (size_t i=0; i<l; i++)
        numbers[i] = mass[i];
}

BigInt::~BigInt()
{
    delete [] numbers;
}

size_t BigInt::getLen() const
{
    return len;
}

const char *BigInt::getNumbers() const
{
    return numbers;
}

bool BigInt::isPositive() const
{
    return positive;
}

bool BigInt::isZero() const
{
    if (((len == 1) && (numbers[0] == '0')) || 
        (len == 0))
        return true;
    else
        return false;
}

size_t getFirstNeq(const BigInt &bint_1, const BigInt &bint_2)
{
    if (bint_1.getLen() != bint_2.getLen())
        return -1;

    size_t res = -1;
    const char *numbers_1 = bint_1.getNumbers();
    const char *numbers_2 = bint_2.getNumbers();
    for (size_t i=0; i<bint_1.getLen(); i++)
    {
        if (numbers_1[i] != numbers_2[i])
        {
            res = i;
            break;
        }
    }
    return res;
}

BigInt add(const BigInt &bint_1, const BigInt &bint_2, bool pos)
{
    size_t len_1 = bint_1.getLen();
    size_t len_2 = bint_2.getLen();
    size_t len_result = std::max(len_1, len_2) + 1;
    char *num_1 = new char[len_result+1];
    char *num_2 = new char[len_result+1];
    char *result = new char[len_result+1];
    const char *numbers_1 = bint_1.getNumbers();
    const char *numbers_2 = bint_2.getNumbers();
    num_1[0] = '0';
    num_2[0] = '0';

    if (len_1 > len_2)
    {
        size_t diff = len_1 - len_2;

        for (size_t i=0; i<diff; i++)
            num_2[i+1] = '0';

        for (size_t i=0; i<len_2; i++)
            num_2[i+1+diff] = numbers_2[i];

        for (size_t i=0; i<len_1; i++)
            num_1[i+1] = numbers_1[i];
    }

    if (len_2 >= len_1)
    {
        size_t diff = len_2 - len_1;

        for (size_t i=0; i<diff;i++)
            num_2[i+1] = '0';

        for (size_t i=0; i<len_1; i++)
            num_2[i+1+diff] = numbers_1[i];

        for (size_t i=0; i<len_2; i++)
            num_1[i+1] = numbers_2[i];
    }
    
    int curr_memory = 0;
    int prev_memory = 0;
    int curr_num = 0;
    int i_num_1;
    int i_num_2;

    for (int i=len_result-1; i >= 0; i--)
    {
        i_num_1 = int(num_1[i]);
        i_num_2 = int(num_2[i]);
        if (i_num_1 == 0) i_num_1 = '0';
        if (i_num_2 == 0) i_num_2 = '0';
        curr_num = i_num_1-'0' + i_num_2-'0';
        if (curr_num > 9)
        {
            curr_memory = (int)curr_num / 10;
            curr_num = curr_num % 10;            
        }
        result[i] = (char)(curr_num + prev_memory) + '0';
        prev_memory = curr_memory;
        curr_memory = 0;
    }
   
    BigInt rs;
    
    if (result[0] == '0')
    {
        char *cut_result = new char[len_result];
        for (size_t i=0; i<len_result-1; i++)
            cut_result[i] = result[i+1];
        rs.fill(cut_result, len_result-1, pos);
        delete [] cut_result;
        
    }
    else
        rs.fill(result, len_result, pos);

    delete [] num_1;
    delete [] num_2;
    delete [] result;

    return rs;
}

BigInt sub(const BigInt &bint_1, const BigInt &bint_2, bool pos)
{
    size_t len_1 = bint_1.getLen();
    size_t len_2 = bint_2.getLen();
    size_t len_result = std::max(len_1, len_2);
    char *num_1 = new char[len_result+1];
    char *num_2 = new char[len_result+1];
    char *result = new char[len_result+1];
    const char *numbers_1 = bint_1.getNumbers();
    const char *numbers_2 = bint_2.getNumbers();
    size_t diff = len_1 - len_2;

    for (size_t i=0; i<diff; i++)
        num_2[i] = '0';

    for (size_t i=0; i<len_2; i++)
        num_2[i+diff] = numbers_2[i];

    for (size_t i=0; i<len_1; i++)
        num_1[i] = numbers_1[i];

    int curr_digit = 0;
    int digit_1;
    int digit_2;
    int i_num_1;
    int i_num_2;

    for (int i=len_result-1; i >= 0; i--)
    {
        i_num_1 = int(num_1[i]);
        i_num_2 = int(num_2[i]);
        if (i_num_1 == 0) i_num_1 = '0';
        if (i_num_2 == 0) i_num_2 = '0';
        digit_1 = i_num_1 - '0';
        digit_2 = i_num_2 - '0';
        curr_digit = digit_1 - digit_2;
        if (digit_1 < digit_2)
        {
            for (int j=1; j<=i; j++)
            {
                if (num_1[i-j] > 0)
                {
                    num_1[i-j] -= 1;
                    break;
                }
            }
            curr_digit += 10;
        }
        result[i] = (char)(curr_digit) + '0';
    }
    
    BigInt rs;

    size_t num_zeros = 0;
    for (size_t i=0; i<len_result; i++)
    {
        if (result[i] != '0') break;
        num_zeros += 1;
    }

    if (num_zeros != 0)
    {
        char *new_result = new char[len_result-num_zeros+1];
        for (size_t i=0; i<len_result - num_zeros; i++)
            new_result[i] = result[num_zeros + i];
        rs.fill(new_result, len_result - num_zeros, pos);
        delete [] new_result;
    }
    else
        rs.fill(result, len_result, pos);

    delete [] num_1;
    delete [] num_2;
    delete [] result;

    return rs;
}

BigInt operator+(const BigInt &bint_1, const BigInt &bint_2)
{
    BigInt r;
    const char *numbers_1 = bint_1.getNumbers();
    const char *numbers_2 = bint_2.getNumbers();
    if (bint_1.isPositive() && bint_2.isPositive())
        r = add(bint_1, bint_2, true);
    else if (!bint_1.isPositive() && !bint_2.isPositive())
        r = add(bint_1, bint_2, false);
    else if (bint_1.isPositive() && !bint_2.isPositive())
    {
        if (bint_1.getLen() > bint_2.getLen())
            r = sub(bint_1, bint_2, true);
        else if (bint_1.getLen() == bint_2.getLen())
        {
            size_t neq_ind = getFirstNeq(bint_1, bint_2);
            if (numbers_1[neq_ind] >= numbers_2[neq_ind])
                r = sub(bint_1, bint_2, true);
            else
                r = sub(bint_2, bint_1, false);
        }
        else
            r = sub(bint_2, bint_1, false);
    }
    else
    {
        if (bint_1.getLen() > bint_2.getLen())
            r = sub(bint_1, bint_2, false);
        else if (bint_1.getLen() == bint_2.getLen())
        {
            size_t neq_ind = getFirstNeq(bint_1, bint_2);
            if (numbers_1[neq_ind] >= numbers_2[neq_ind])
                r = sub(bint_1, bint_2, false);
            else
                r = sub(bint_2, bint_1, true);
        }
        else
            r = sub(bint_2, bint_1, true);
    }

    return r;
}

BigInt operator-(const BigInt &bint_1, const BigInt &bint_2)
{
    BigInt r;
    const char *numbers_1 = bint_1.getNumbers();
    const char *numbers_2 = bint_2.getNumbers();
    if (bint_1.isPositive() && !bint_2.isPositive())
        r = add(bint_1, bint_2, true);
    else if (!bint_1.isPositive() && bint_2.isPositive())
        r = add(bint_1, bint_2, false);
    else if (bint_1.isPositive() && bint_2.isPositive())
    {
        if (bint_1.getLen() > bint_2.getLen())
            r = sub(bint_1, bint_2, true);
        else if (bint_1.getLen() == bint_2.getLen())
        {
            size_t neq_ind = getFirstNeq(bint_1, bint_2);
            if (numbers_1[neq_ind] >= numbers_2[neq_ind])
                r = sub(bint_1, bint_2, true);
            else
                r = sub(bint_2, bint_1, false);
        }
        else
            r = sub(bint_2, bint_1, false);
    }
    else
    {
        if (bint_1.getLen() > bint_2.getLen())
            r = sub(bint_1, bint_2, false);
        else if (bint_1.getLen() == bint_2.getLen())
        {
            size_t neq_ind = getFirstNeq(bint_1, bint_2);
            if (numbers_1[neq_ind] >= numbers_2[neq_ind])
                r = sub(bint_1, bint_2, false);
            else
                r = sub(bint_2, bint_1, true);
        }
        else
            r = sub(bint_2, bint_1, true);
    }
    return r;
}

BigInt BigInt::operator-()
{
    BigInt r = *this;
    r.positive = !positive;
    return r;
}

bool BigInt::operator<(const BigInt &bint) const
{
    BigInt r = *this - bint;
    if (r.isZero())
        return false;
    return !r.isPositive();
}

bool BigInt::operator>(const BigInt &bint) const
{
    return !this->operator<(bint);
}

bool BigInt::operator<=(const BigInt &bint) const
{
    BigInt r = *this - bint;
    if (r.isZero()){
        return true;
    }
    return !r.isPositive();
}

bool BigInt::operator>=(const BigInt &bint) const
{
    BigInt r = *this - bint;
    if (r.isZero()){
        return true;
    }
    return r.isPositive();
}

bool BigInt::operator==(const BigInt &bint) const
{
    return (this->operator<=(bint) && this->operator<=(bint));
}

bool BigInt::operator!=(const BigInt &bint) const
{
    return !this->operator==(bint);
}

std::ostream &operator<<(std::ostream &stream, const BigInt &bint)
{
    size_t l = bint.getLen();
    bool pos = bint.isPositive();
    const char *numbers = bint.getNumbers();
    if (!pos) stream << '-';
    for (size_t i=0; i<l; i++)
        stream << numbers[i];
    return stream;    
} 
