#include "boolarray.hpp" 
#include <iostream>

void BoolArray::clear() { //очищение памяти
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

void BoolArray::expand(size_t new_capacity) {
    if (new_capacity <= 0) {
        throw "неверная ёмкость";
    }
    unsigned char* new_data = new unsigned char[new_capacity]();

    size_t copy_bytes = (new_capacity < capacity) ? new_capacity : capacity; // определяем сколько байтов нужно скопировать
    
    for (size_t i = 0; i < copy_bytes; i++) { //копируем данные
        new_data[i] = data[i];
    }
    
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

BoolArray::BoolArray(){
    size = 0;
    capacity = 0;
    data = nullptr;
}

BoolArray::BoolArray(size_t n, bool fill_value){ 
    size = n; // кол-во битов
    capacity = (n + 7) / 8; // округленре вверх

    data = new unsigned char[capacity]();

    if (fill_value) {
        for (size_t i = 0; i < capacity; i++) {
            data[i] = 0xFF; //заполняем все биты
        }
        if (size % 8 != 0) { //если размер не кратен 8, нужно обнулить лишние биты
            int last_byte_bits = size % 8; // количество значимых битов в последнем байте
            data[capacity - 1] &= (0xFF >> (8 - last_byte_bits));
        }
    }
}

BoolArray::BoolArray(const BoolArray& other){
    size = other.size;
    capacity = other.capacity;
    
    data = new unsigned char[capacity];
    
    for (size_t i = 0; i < capacity; i++) { // копирование данных из исходного массива
        data[i] = other.data[i];
    }
}

BoolArray::BoolArray(BoolArray&& other){ 
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = 0;
    other.capacity = 0; 
}

BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (other.capacity != capacity || data == nullptr) {
        clear(); // очистка текущих данных
        capacity = other.capacity;
        data = new unsigned char[capacity];
    }
    
    size = other.size;
    for (size_t i = 0; i < capacity; i++) { // копирование данных
        data[i] = other.data[i];
    }
    
    return *this;
}

BoolArray& BoolArray::operator=(BoolArray&& other){
    clear();
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
    
    return *this;
}

BoolArray::~BoolArray() {
    clear();
}

size_t BoolArray::get_size() const {
    return size;
}

void BoolArray::resize(size_t new_size, bool fill_value) {
    size_t new_capacity = (new_size + 7) / 8;
    
    if (new_capacity > capacity) {
        expand(new_capacity);
    }
    
    size_t old_size = size;
    size = new_size;
    
    for (size_t i = old_size; i < new_size; i++) {
        (*this)[i] = fill_value;
    }
    
    if (new_capacity < capacity) {
        capacity = new_capacity;
    }

    if (size % 8 != 0 && capacity > 0){ // маскировка лишних битов
        int last_byte_bits = size % 8;
        data[capacity - 1] &= (0xFF >> (8 - last_byte_bits));
    }
}

void BoolArray::print() const{
    for (size_t i = 0; i < size; i++) {
        std::cout << (*this)[i] << ' ';
    }
    std::cout << "\n";
}

BoolArray::Item::Item(unsigned char* byte1, size_t bit_index1){
    byte = byte1;
    bit_index = bit_index1;
}

BoolArray::Item::operator bool(){ //проверяем установлен ли бит
    return (*byte) & (1 << (7 - bit_index));
}

BoolArray::Item& BoolArray::Item::operator=(bool value){ // запись бита
    if (value) {
        *byte |= (1 << (7 - bit_index));
    } else {
        *byte &= ~(1 << (7 - bit_index)); // обнуление бита
    }
    return *this;
}


BoolArray::Item BoolArray::operator[](int index){
    if (index < 0 || index >= size) { // проверка границ
        throw "индекс выходит за границы";
    }
    //&data[index / 8] - указатель на байт, содержащий бит
    //index % 8 - номер бита в этом байте
    return Item(&data[index / 8], index % 8);
}

bool BoolArray::operator[](int index) const{
    if (index < 0 || static_cast<size_t>(index) >= size) {
        throw "индекс выходит за границы";
    }
    return data[index / 8] & (1 << (7 - (index % 8))); // установлен ли бит
}