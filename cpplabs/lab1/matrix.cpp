#include "matrix.hpp"
#include <iostream>
Matrix::Matrix(int n1){
    this->data = new int*[n];
    m = n1;
    n = n1;
    for(int i = 0; i< n1;i++){
        this->data[i] = new int[n]();
        this->data[i][i] = 1;
    }
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
}

Matrix::Matrix(const Matrix &other){
    m = other.m;
    n = other.n;
    data = new int*[m]; 
    for (int i = 0; i < m; i++) {
        data[i] = new int[n];
        for (int j = 0; j < n; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix(){
    for(int i = 0;i<m;i++){
        delete[] data[i];
    }
    delete[] data;
    data = nullptr;
}

double Matrix::get(int i, int j){
    return data[i][j];
}

void Matrix::set(int i, int j, double value){
    data[i][j] = value;
}

int Matrix::get_height(){
    return n;
}

int Matrix::get_width(){
    return m;
}

void Matrix::negate(){
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] = -data[i][j];
        }
    }
}

void Matrix::add_in_place(Matrix &other){
    if (m != other.m || n != other.n){
        throw "Несовместимые рамеры матриц";
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] += other.data[i][j];
        }
    }
}   

Matrix Matrix::multiply(Matrix &other){
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