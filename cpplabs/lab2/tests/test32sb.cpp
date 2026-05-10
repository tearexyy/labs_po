#include <cassert>
#include <cstdio>
#include <iostream>
#include "../src/BaseFile.hpp"

void test32sb(int write_block, int read_block) {
    const int data = 100;
    unsigned char* original = new unsigned char[data];
    for (int i = 0; i < data; i++)
        original[i] = (unsigned char)(i * 3 + 7);
    
    std::cout << "  write_block=" << write_block << ", read_block=" << read_block << "\n";
    
    {
        Base32File f("tests/test_b32.txt", "wb");
        int written = 0;
        while (written < data) {
            int step = (data - written < write_block) ? data - written : write_block;
            size_t n = f.write(original + written, step);
            if (n != (size_t)step) {
                std::cout << "тест test32sb не прошел\n";
                delete[] original;
                return;
            }
            written += n;
        }
    }
    
    unsigned char* result = new unsigned char[data];
    for (int i = 0; i < data; i++) result[i] = 0;
    
    {
        Base32File f("tests/test_b32.txt", "rb");
        int total_read = 0;
        while (total_read < data) {
            int step = (data - total_read < read_block) ? data - total_read : read_block;
            size_t n = f.read(result + total_read, step);
            if (n == 0) break;
            total_read += n;
        }
        
        if (total_read != data) {
            std::cout << "тест test32sb не прошел\n";
            delete[] original;
            delete[] result;
            return;
        }
        
        for (int i = 0; i < data; i++) {
            if (original[i] != result[i]) {
                std::cout << "тест test32sb не прошел\n";
                delete[] original;
                delete[] result;
                return;
            }
        }
    }
    
    std::cout << "тест test32sb прошел\n";
    delete[] original;
    delete[] result;
}

int main(){
    std::cout<<"\test32sb\n";
    test32sb(400, 5);
    test32sb(5, 3);
    test32sb(577, 20);
    test32sb(807, 300);
    test32sb(307, 300);
    test32sb(207, 300);
    return 0;
}