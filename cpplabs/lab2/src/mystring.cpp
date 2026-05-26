#include "mystring.hpp"
#include <cstring>
#include <iostream>

MyString::MyString(){
    //string = new char[1];
    string = nullptr;
}

MyString::~MyString() {
    delete[] string;
}

int MyString::get_length(){
    if (string == nullptr) throw "Строка не инициализирована";
    return strlen(string);
}

MyString::MyString(const char* str){
    string = new char[strlen(str) + 1];//+1 для \0
    strcpy(string, str);
}

char MyString::get(int i){
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

void MyString::print(){
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
}
