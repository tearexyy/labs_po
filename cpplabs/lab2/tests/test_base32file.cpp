#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../src/BaseFile.hpp"

const int data = 45000;
const int step = 256;

int main() {
    std::cout<<"\ntest_base32file\n";
    srand(time(nullptr));
    
    char* original = new char[data];
    for (int i = 0; i < data; i++) {
        original[i] = (char)(rand() % 256); // генерируем массив
    }
    
    {
        Base32File f("tests/test_base32file.bin", "wb");
        for (int i = 0; i < data; i += step) {
            int n;
            if (data - i < step){ // если осталось меньше 256, берем остаток
                n = data-i;
            }
            else{n = step;} // иначе берем 256
            if (f.write(original + i, n) != n) { std::cout << "тест Base32File не прошел\n"; return 1; }
        }
    }
    
    char* read_data = new char[data];
    {
        Base32File f("tests/test_base32file.bin", "rb");
        for (int i = 0; i < data; i += step) {
            int n;
            if (data - i < step){ // если осталось меньше 256, берем остаток
                n = data-i;
            }
            else{n = step;} // иначе берем 256
            int got = f.read(read_data + i, n);
            if (got == 0) { std::cout << "тест Base32File не прошел\n"; return 1; } //прочитали 0 за итерацию
        }
    }
    
    for (int i = 0; i < data; i++) {
        if (original[i] != read_data[i]) { std::cout << "тест Base32File не прошел\n"; return 1; }
    }
    
    std::cout << "тест Base32File прошел\n\n";
    delete[] original;
    delete[] read_data;
    return 0;
}