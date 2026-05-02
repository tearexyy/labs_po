#include <iostream>

class BoolArray {
private:
    unsigned char* data; // массив для хранения битов
    size_t size; // кол-во битов (элементов)
    size_t capacity; // кол-во байт
    void clear();
    void expand(size_t new_capacity); // увеличение емкости
    
public:
    BoolArray();
    BoolArray(size_t n, bool fill_value = false);
    BoolArray(const BoolArray& other);
    BoolArray(BoolArray&& other);
    BoolArray& operator=(const BoolArray& other);
    BoolArray& operator=(BoolArray&& other);
    ~BoolArray();
    size_t get_size() const;
    void resize(size_t new_size, bool fill_value = false);
    void print() const;
    class Item { // реализация прокси-класса, тк у бита нет адреса, но его необходимо запонмить
    private:
        unsigned char* byte; //указатель на байт
        size_t bit_index; //номер бита
    public:
        Item(unsigned char* byte, size_t bit_index);
        operator bool(); //чтение
        Item& operator=(bool value); //запись
    };
    
    Item operator[](int index);
    bool operator[](int index) const;
};
