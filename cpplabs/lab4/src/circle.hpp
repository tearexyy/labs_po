#include <fstream>

class Point{
    double x;
    double y;
public:
    Point();
    Point(double a, double b);
    double get_x() const;
    double get_y() const;
    void set_x(double x);
    void set_y(double y);
    void set_new(double x, double y);
    bool operator==(const Point& other) const;
};

class Circle {
    Point center;
    double radius;
public:
    Circle(double x = 0, double y = 0, double r = 0):center(x, y), radius(r){}
    Circle(const Point& c, double r):center(c), radius(r){}
    const Point& get_center() const;
    double get_radius();
    bool operator==(const Circle& other)const;
    double area() const;
};

class List {
    struct Node { // структура, так как вес поля публичные
        Node* pPrev; //указатель на пред.
        Node* pNext; //указаетль на след.
        Circle m_Data;

        Node():pPrev(this), pNext(this){}
        Node(Node* next_node, const Circle& c);// next_node - узел, перед которым вставляется новый элемент
        ~Node();
    };
    Node Head;
    Node Tail;
    size_t m_size;

public:
    List();
    void add_front(const Circle& c);
    void add_back(const Circle& c);
    bool remove_first(const Circle& c);
    size_t remove_all(const Circle& c);
    void clear();
    size_t size();
    bool empty();
    void swap_data(Node* a, Node* b);
    void quick_sort(Node* left, Node* right);
    void sort();
    void sort_reverse(); // отсортированный список в обратном порядке
    void reverse(); // список в обратном порядке
    friend std::ostream& operator<<(std::ostream& os, const List& list); // friend, так как 1 й аргумент - не объект класса
    void write_to_file(const char* filename);
    void read_from_file(const char* filename);
    ~List();
    List& operator=(const List& other);
    Circle& index_find(int index);
    List(const List& other);
};
