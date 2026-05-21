class Matrix
{
    int m;
    int n;
    int** data;
public:
    Matrix();
    Matrix(int n);
    Matrix(int m, int n, double fill_value = 0);
    Matrix(const Matrix &other);
    ~Matrix();
    double get(int i, int j) const;
    int get_height() const;
    int get_width() const;
    void print() const;
    void set(int i, int j, double value);
    void negate();
    void add_in_place(Matrix &other);
    Matrix multiply(const Matrix &other) const;
    Matrix& operator=(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double a);
    Matrix& operator/=(double a);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double a) const;
    Matrix operator/(double a) const;
    Matrix(Matrix&& other);
    Matrix& operator=(Matrix&& other);
};
Matrix operator*(double a, const Matrix& other);
Matrix operator-(const Matrix& matrix);