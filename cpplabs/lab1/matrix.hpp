class Matrix
{
int m;
int n;
int** data;
public:
    Matrix(int n);
    Matrix(int m, int n, double fill_value = 0);
    Matrix(const Matrix &other);
    ~Matrix();
    double get(int i, int j);
    void set(int i, int j, double value);
    int get_height();
    int get_width();
    void negate();
    void add_in_place(Matrix &other);
    Matrix multiply(Matrix &other);
};