#include "matrix.hpp"
#include <iostream>
Matrix::Matrix(int n1){
    m = n1;
    n = n1;
    data = new int*[n];
    for(int i = 0; i< n1;i++){
        this->data[i] = new int[n]();
        this->data[i][i] = 1;
    }
std::cout << "выделение памяти: конструктор квадратной матрицы\n";
}
Matrix::Matrix(){
    data = nullptr;
    m =0;
    n = 0;
}

Matrix::Matrix(int m1, int n1, double fill_value){
    m = m1;
    n = n1;
    data = new int*[m]; 
    for (int i = 0; i < m; i++) {
        data[i] = new int[n];
        for (int j = 0; j < n; j++) {
            data[i][j] = fill_value;
        }
    }
    std::cout << "выделение памяти: конструктор с параметрами\n";
}

void test_default_constructed_matrix() {
    // TODO: убедиться, что такой код выполняется без ошибок
    Matrix m;
    Matrix m2 = m;
}

Matrix::Matrix(const Matrix &other) {
    m = other.m;
    n = other.n;
    if (m == 0 || n == 0) {
        data = nullptr;
        return; //выход из конструктора копирования
    }
    data = new int*[m];
    for (int i = 0; i < m; i++) {
        data[i] = new int[n];
        for (int j = 0; j < n; j++) {
            data[i][j] = other.data[i][j];
        }
    }
    std::cout << "выделение памяти: конструктор копирования\n";
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        // освобождаем старую память
        for (int i = 0; i < m; i++) {
            delete[] data[i];
        }
        delete[] data;
    
    m = other.m;
    n = other.n;
    if (m == 0 || n == 0) {
        data = nullptr;
        return *this;
    }
    data = new int*[m];
    for (int i = 0; i < m; i++) {
        data[i] = new int[n];
        for (int j = 0; j < n; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}
std::cout << "выделение памяти: operator=\n";
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {   
    if (m != other.m || n != other.n) {
        throw "матрицы должны иметь одинаковый размер";
    }
    if (data == nullptr || other.data == nullptr) {
        throw "матрица не инициализирована";
    }
   for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] += other.data[i][j];
        }
    }
    std::cout << "выделение памяти: operator+=\n";
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {   
    if (m != other.m || n != other.n) {
        throw "матрицы должны иметь одинаковый размер";
    }
    if (data == nullptr || other.data == nullptr) {
        throw "матрица не инициализирована";
    }
   for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] -= other.data[i][j];
        }
    }
    std::cout << "выделение памяти: operator-=\n";
    return *this;

}

Matrix& Matrix::operator*=(double a) {   
    if (data == nullptr) {
        throw "матрица не инициализирована";
    }
   for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] *= a;
        }
    }
    std::cout << "выделение памяти: operator*=\n";
    return *this;
}

Matrix& Matrix::operator/=(double a) {   
    if (data == nullptr) {
        throw "матрица не инициализирована";
    }

    if (a == 0) {
        throw "деление на ноль";
    }

   for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] /= a;
        }
    }
    std::cout << "выделение памяти: operator/=\n";
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const{
    Matrix result = *this;
    result += other; //здесь проверка
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const{
    Matrix result = *this;
    result -= other; //здесь проверка
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const{
return multiply(other) ;
}

Matrix operator*(double a, const Matrix& other) {
    return other * a;
}

Matrix operator-(const Matrix& other){
    Matrix result = other;
    result.negate();
    return result;
}

Matrix Matrix::operator*(double a) const{
    Matrix result = *this;
    result*=a;
    return result;
}

Matrix Matrix::operator/(double a) const{
    Matrix result = *this;
    result/=a;
    return result;
}

Matrix::~Matrix(){
    for(int i = 0;i<m;i++){
        delete[] data[i];
    }
    delete[] data;
    data = nullptr;
    std::cout << "освобождение памяти\n";
}
 
double Matrix::get(int i, int j) const{
    if (data == nullptr) throw "Матрица не инициализирована";
    if (i < 0 || i >= m || j < 0 || j >= n) throw "Неверный индекс";
    return data[i][j];
}

void Matrix::set(int i, int j, double value){
    if (data == nullptr) throw "Матрица не инициализирована";
    if (i < 0 || i >= m || j < 0 || j >= n) throw "Неверный индекс";
    data[i][j] = value;
}

int Matrix::get_height() const{
    return n;
}

int Matrix::get_width() const{
    return m;
}

void Matrix::negate(){
    if (data == nullptr) throw "Матрица не инициализирована";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] = -data[i][j];
        }
    }
}

void Matrix::add_in_place(Matrix &other){
    if (data == nullptr || other.data == nullptr) throw "Матрица не инициализирована";
    if (m != other.m || n != other.n){
        throw "Несовместимые рамеры матриц";
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] += other.data[i][j];
        }
    }
}   

Matrix Matrix::multiply(const Matrix &other) const{
if (data == nullptr || other.data == nullptr) throw "Матрица не инициализирована";
if (n != other.m) {
    throw "Несовместимые рамеры матриц";
    }

    Matrix mult_res(m, other.n, 0);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < other.n; j++) {
            double sum = 0.0; //для строка*столбец
            for (int k = 0; k < n; k++) {
                sum += data[i][k] *  other.data[k][j];
            }
            mult_res.data[i][j] = sum;
        }
    }
    return mult_res; 
}

Matrix::Matrix(Matrix&& other){
    m = other.m;
    n = other.n;
    data = other.data;
    other.m = 0;
    other.n = 0;
    other.data = nullptr;
}
 
Matrix& Matrix::operator=(Matrix&& other){
    if (this != &other) {
        for (int i = 0; i < m; i++) {
            delete[] data[i];
        }
        delete[] data;
        m = other.m;
        n = other.n;
        data = other.data;
        other.m = 0;
        other.n = 0;
        other.data = nullptr;
    }
    return *this;
}
 
void Matrix::print() const{
    for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << get(i, j) << ' ';
        }
        std::cout << '\n';
    }
}