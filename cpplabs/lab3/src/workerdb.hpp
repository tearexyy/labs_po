#include "mystring.hpp"

struct WorkerData {
    MyString name;
    int age;
    double salary;
    WorkerData();
    WorkerData(const char* n, int a, double s);
};

class WorkerDb {
private:
    struct Node {
        MyString key; // ключ для поиска (фамилия)
        WorkerData data; // информация о сотруднике
        Node* next; // укзатель на следующий эемент в цепочке
    };
    Node** buckets; // массив указателей на начала цепочек
    int size; // общее кол-во элементов
    int bucket_count; // кол-во цепочек
    int hash(const MyString& key) const; // хеш-функция
    
public:
    WorkerDb();
    ~WorkerDb();
    WorkerData& operator[](const MyString& key);
    int get_size() const {return size;}
    class Iterator {
    private:
        Node** buckets; // копия указателя на массив цепочек
        Node* current; // текущий элемент
        int bucket_index; // индекс текущей цепочки
        int bucket_count; // общее количество цепочек
        void find_next();
        
    public:
        Iterator(Node** buckets, int bucket_count, int start_bucket = 0, Node* start_node = nullptr);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        Iterator& operator++();
        Iterator operator++(int);
        WorkerData& operator*();
        WorkerData* operator->();
        MyString key() const;
    };
    Iterator begin();
    Iterator end();
};

double get_avg_age(WorkerDb& db);
void print_db(WorkerDb& db);