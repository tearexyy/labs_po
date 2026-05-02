#include "workerdb.hpp"
#include <cstring>
#include <iostream>

WorkerData::WorkerData() : name(""), age(0), salary(0) {}

WorkerData::WorkerData(const char* n, int a, double s) : name(n), age(a), salary(s){}; // вызывается конструктор для name

WorkerDb::WorkerDb(){
    bucket_count = 10;
    size = 0;
    buckets = new Node*[bucket_count]; // массив указателей на цепочки
    for (int i = 0; i < bucket_count; i++){
        buckets[i] = nullptr;
    }
}

WorkerDb::~WorkerDb(){
    for (int i = 0; i < bucket_count; i++){
        Node* current = buckets[i]; // начало цепочки
        Node* temp;
        while (current != nullptr){
            temp = current;
            current = current->next; // переходим к следующему
            delete temp;
        }
    }
    delete[] buckets;
}


int WorkerDb::hash(const MyString& key) const {
    const char* str = key.get_string();
    int h = 0;
    for (int i = 0; str[i] != '\0'; i++){
        h = (h * 31 + str[i]) % bucket_count;
    }
    return h;
}
WorkerData& WorkerDb::operator[](const MyString& key){
    int index = hash(key); // индекс корзины
    Node* current = buckets[index]; 
    while (current != nullptr){
        if (current->key == key){ // находим нужный элемент
            return current->data;
        }
        current = current->next;
    }
    Node* new_node = new Node(); // еслин ет нужного элемента, нужно создать новый
    new_node->key = key; //сохранили ключ
    new_node->next = buckets[index]; // добавляем элемент в начало
    buckets[index] = new_node;
    size++;
    return new_node->data; // данные элемента
}

void WorkerDb::Iterator::find_next(){ // находит следующий непустой элемент
    while (bucket_index < bucket_count && current == nullptr){
        current = buckets[bucket_index];
        if (current == nullptr){
            bucket_index++; // если все элементы nullptr, то итератор в состоянии end()
        }
    }
}

WorkerDb::Iterator::Iterator(Node** buckets, int bucket_count, int start_bucket, Node* start_node)
    : buckets(buckets), bucket_count(bucket_count), bucket_index(start_bucket), current(start_node){
    if (current == nullptr && bucket_index < bucket_count){
        current = buckets[bucket_index];
        find_next(); // поиск первого существующего элемента
    }
}

bool WorkerDb::Iterator::operator==(const Iterator& other) const { // сравнение двух итераторов
    return (bucket_index == other.bucket_index && current == other.current);
}

bool WorkerDb::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

WorkerDb::Iterator& WorkerDb::Iterator::operator++(){
    if (current != nullptr){
        current = current->next; // переход к следующем уэлементу
        
        if (current == nullptr){ // если цепочка кончилась
            bucket_index++; // переход к следующей
            find_next();
        }
    }
    return *this;
}

WorkerDb::Iterator WorkerDb::Iterator::operator++(int){ // переход к следующему элементу
    Iterator temp = *this;
    ++(*this);
    return temp;
}

WorkerData& WorkerDb::Iterator::operator*(){
    return current->data; // ссылка на данные текущего узла
}

WorkerData* WorkerDb::Iterator::operator->(){
    return &current->data; // указатель на данные текущего узла
}

MyString WorkerDb::Iterator::key() const {
    return current->key; // фамилия 
}

WorkerDb::Iterator WorkerDb::begin(){ // итератор на паервый элемент
    return Iterator(buckets, bucket_count, 0, nullptr);
}

WorkerDb::Iterator WorkerDb::end(){
    return Iterator(buckets, bucket_count, bucket_count, nullptr);
} // указаетль на элемент после последгего 

void print_db(WorkerDb& db){
    std::cout << "база данных работников:\n\n"; 
    int n =0;
    for (auto it = db.begin(); it != db.end(); ++it){
        std::cout << ++n << '\n';
        std::cout << "фамилия: " << it.key().get_string() << "\n";
        std::cout << "имя: " << it->name.get_string() << "\n";
        std::cout << "возраст: " << it->age << " лет\n";
        std::cout << "зарплата: " << it->salary << " руб.\n\n";
    }
}

double get_avg_age(WorkerDb& db){
    if (db.get_size() == 0){
        return 0.0;
    }
    int age = 0.;
    int n = 0;
    
    for (auto it = db.begin(); it != db.end(); ++it){
        age += it->age;
        n++;
    }
    
    return (age) / n;
}