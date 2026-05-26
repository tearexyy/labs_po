#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../src/BaseFile.hpp"

const int data = 45000;
const int step = 256;

int main() {
    std::cout<<"\ntest_composition\n";
    srand(time(nullptr));
    char* original = new char[data];
    for (int i = 0; i < data; i++) {
        original[i] = (char)(rand() % 256); // генерируем массив
    }
    
    {
        IFile* f = new Base32File2(new RleFile2(new BaseFile("tests/test_composition.bin", "wb")));
        for (int i = 0; i < data; i += step) {
            int n;
            if (data - i < step){ // если осталось меньше 256, берем остаток
                n = data-i;
            }
            else{n = step;} // иначе берем 256
            if (f->write(original + i, n) != n) { std::cout << "тест composition не прошел\n"; delete f; return 1; }
        }
        delete f;
    }
    
    char* read_data = new char[data];
    {
        IFile* f = new Base32File2(new RleFile2(new BaseFile("tests/test_composition.bin", "rb")));
        for (int i = 0; i < data; i += step) {
            int n;
            if (data - i < step){ // если осталось меньше 256, берем остаток
                n = data-i;
            }
            else{n = step;} // иначе берем 256
            if (f->read(read_data + i, n) == 0) { std::cout << "тест composition не прошел\n"; delete f; return 1; }
        }
        delete f;
    }
    
    for (int i = 0; i < data; i++) {
        if (original[i] != read_data[i]) { std::cout << "тест composition не прошел\n"; return 1; }
    }
    
    std::cout << "тест composition прошел\n";
    delete[] original;
    delete[] read_data;
    return 0;
}