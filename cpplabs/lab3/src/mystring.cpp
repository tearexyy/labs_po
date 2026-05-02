#include "mystring.hpp"
#include <cstring>
#include <iostream>

MyString::MyString(){
    //string = new char[1];
    string = nullptr;
}

MyString::~MyString() {
    delete[] string;
    //std::cout << "освобождение памяти\n";
}

int MyString::get_length() const{
    if (string == nullptr) throw "Строка не инициализирована";
    return strlen(string);
}

MyString::MyString(const char* str){
    string = new char[strlen(str) + 1];//+1 для \0
    strcpy(string, str);
    //std::cout << "выделение памяти: конструктор от строки\n";
}

MyString& MyString::operator=(const MyString& other){
     if (this != &other) {
        delete[] string; // освобождаем старую память
        if (other.string == nullptr) {
            string = nullptr; 
        } else {
            string = new char[strlen(other.string) + 1];
            strcpy(string, other.string);
        }
    }
    //std::cout << "выделение памяти: operator=\n";
    return *this;
}

char MyString::get(int i) const{
    if (string == nullptr) throw "Строка не инициализирована";
    int len = strlen(string);
    if (i < 0 || i >= len) {
        throw "Неверный индекс";
    }
    return string[i];
}

void MyString::set(int i, char c){
    if (string == nullptr) throw "Строка не инициализирована";
    int len = strlen(string);
    if (i < 0 || i >= len) {
        throw "Неверный индекс";
    }
    string[i] = c;
}

void MyString::set_new_string(const char *str){
    if (string!=nullptr){delete[] string;}
    string = new char[strlen(str) + 1];
    strcpy(string, str);
}

void MyString::print() const{
    if (string == nullptr) {
        std::cout<<"\n";
        return;
    }
    printf("%s\n", string);
}

void MyString::read_line(){
    if (string!=nullptr){delete[] string;}
    std::cout << "Введите строку: \n";
    int bufsize = 20; //начальный размер буфера
    string = new char[bufsize];
    char c; //символ
    int position = 0; //показывает место, куда поставить след символ в string

    while (std::cin.get(c) && c!='\n'){ //читаем по одному символу
        string[position] = c; //сохраняем символ в текущую позицию
        position += 1; 
        if (position >= bufsize - 1) //если получается больше, оставляем место для \0
        { 
            int newbufsize = bufsize * 2;
            char* newbuf = new char[newbufsize];
            for (int k = 0; k < position; k++) // переносим все символы из старого массива в новый
            {
                newbuf[k] = string[k];
            }
            delete[] string;
            string = newbuf;
            bufsize = newbufsize;
        }
    }
    string[position] = '\0'; //окончание строки
}

MyString::MyString(const MyString& other) {
    if (other.string == nullptr) throw "Строка не инициализирована";
    string = new char[strlen(other.string) + 1];
    strcpy(string, other.string);
    //std::cout << "выделение памяти: конструктор копирования\n";
}

MyString& MyString::operator+=(const MyString& other){
    if (other.string == nullptr) return *this;
    int len1 = strlen(string);
    int len2 = strlen(other.string);
    char* new_string = new char[len1 + len2 + 1];
    for (int i = 0; i < len1; i++) {
        new_string[i] = string[i];
    }
    for (int i = 0; i < len2; i++) {
        new_string[len1 + i] = other.string[i];
    }
    new_string[len1 + len2] = '\0';
    
    delete[] string;
    string = new_string;
    //std::cout << "выделение памяти: operator+=\n";
    return *this;
}

MyString& MyString::operator+=(const char* other){
    if (other == nullptr) return *this;
    int len1 = strlen(string);
    int len2 = strlen(other);
    char* new_string = new char[len1 + len2 + 1];
    for (int i = 0; i < len1; i++) {
        new_string[i] = string[i];
    }
    for (int i = 0; i < len2; i++) {
        new_string[len1 + i] = other[i];
    }
    new_string[len1 + len2] = '\0';
    
    delete[] string;
    string = new_string;
    //std::cout << "выделение памяти: operator+=\n";
    return *this;
}
    
MyString MyString::operator+(const MyString& other) const{
    MyString result = *this;
    result += other;
    return result;
}

MyString MyString::operator+(const char* other) const{
    MyString result = *this;
    result += other;
    return result;
}

MyString operator+(const char* string, const MyString& other) {
    MyString result(string);
    result += other;
    return result;
}

MyString::MyString(MyString&& other){
   string = other.string;
   other.string = nullptr;
}

MyString& MyString::operator=(MyString&& other){
     if (this != &other) {
        delete[] string;        
        string = other.string;
        other.string = nullptr; // другой объект становится пустым
    }
    return *this;
}

bool MyString::operator==(const MyString& other) const{
    if (string == nullptr && other.string == nullptr) return true;
    if (string == nullptr || other.string == nullptr) return false;
    return strcmp(string, other.string) == 0;
}
bool MyString::operator==(const char* other) const{
    if (string == nullptr && other == nullptr) return true;
    if (string == nullptr || other == nullptr) return false;
    return strcmp(string, other) == 0;
}

bool MyString::operator!=(const MyString& other) const{
    return !(*this == other);
}
bool MyString::operator!=(const char* other) const{
    return !(*this == other);
}

bool MyString::operator<(const MyString& other) const{
    if (string == nullptr && other.string == nullptr) return false;
    if (string == nullptr) return true;
    if (other.string == nullptr) return false;
    return strcmp(string, other.string) < 0;
}

bool MyString::operator<(const char* other) const{
    if (string == nullptr && other == nullptr) return false;
    if (string == nullptr) return true;
    if (other == nullptr) return false;
    return strcmp(string, other) < 0;
}

bool MyString::operator<=(const MyString& other) const{
    return (*this < other) || (*this == other);
}

bool MyString::operator<=(const char* other) const{
    return (*this < other) || (*this == other);
}

bool operator==(const char* string1, const MyString& other){
    MyString temp(string1);
    return temp == other;
}

bool operator!=(const char* string1, const MyString& other){
    MyString temp(string1);
    return temp != other;
}

bool operator<(const char* string1, const MyString& other){
    MyString temp(string1);
    return temp < other;
}

bool operator<=(const char* string1, const MyString& other){
    MyString temp(string1);
    return temp <= other;
}

char& MyString::operator[](int index){
    if (string == nullptr) {
        throw "строка не инициализирована";
    }
    if (index < 0 || index >= strlen(string)) {
        throw "индекс выходит за границы строки";
    }
    return string[index];
}


std::ostream& operator<<(std::ostream& out, const MyString& str){
    return out<<str.get_string();
}

std::istream& operator>>(std::istream& in, MyString& str){
    str.read_line();
    return in;
}