class BigInt
{
    char *numbers;
    size_t len;
    bool positive = true;
    void fill(char *mass, size_t l, bool pos);
public:
    BigInt(const char *x);
    BigInt();
    BigInt(const BigInt &bint);
    BigInt &operator=(BigInt bint);
    ~BigInt();
    size_t getLen() const;
    const char *getNumbers() const;
    bool isPositive() const;
    bool isZero() const;
friend BigInt add(const BigInt &bint_1, const BigInt &bint_2, bool pos);
friend BigInt sub(const BigInt &bint_1, const BigInt &bint_2, bool pos);
    BigInt operator-();
    bool operator<(const BigInt &bint) const;
    bool operator>(const BigInt &bint) const;
    bool operator<=(const BigInt &bint) const;
    bool operator>=(const BigInt &bint) const;
    bool operator==(const BigInt &bint) const;
    bool operator!=(const BigInt &bint) const;
    friend std::ostream &operator<<(std::ostream &stream, const BigInt &bint);
};

BigInt operator+(const BigInt &bint_1, const BigInt &bint_2);
BigInt operator-(const BigInt &bint_1, const BigInt &bint_2);