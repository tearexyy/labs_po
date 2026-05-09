#include "circle.hpp"
#include <iostream>

Point::Point(){
    x = 0;
    y = 0;
}

Point::Point(double a, double b){
    x = a;
    y = b;
}

double Point::get_x() const{
    return x;
}

double Point::get_y() const{
    return y;
}

void Point::set_x(double a){
    x = a;
}

void Point::set_y(double b){
    y = b;
}

void Point::set_new(double a, double b){
    x = a;
    y = b;
}

bool Point::operator==(const Point& other) const{
    return x == other.x && y == other.y;
}

const Point& Circle::get_center() const{
    return center;
}

double Circle::get_radius(){
    return radius;
}

bool Circle::operator==(const Circle& other) const{
    return center == other.center && radius == other.radius;
}

double Circle::area() const{
    return 3.14*radius*radius;
}

List::Node::Node(Node* next_node, const Circle& c):m_Data(c){ // next_node - узел, перед которым вставляется новый элемент
    pPrev = next_node->pPrev;
    pNext = next_node;
    next_node->pPrev->pNext = this;
    next_node->pPrev = this;
}

List::Node::~Node(){
    pPrev->pNext = pNext; // предыдущий узел начинает указывать вперёд на текущий следующий
    pNext->pPrev = pPrev; // следующий узел начинает указывать назад на текущий предыдущий
}

List::List(){
    m_size = 0;
    Head.pNext = &Tail;
    Head.pPrev = &Tail;
    Tail.pNext = &Head;
    Tail.pPrev = &Head;
}

void List::add_front(const Circle& c){
    new Node(Head.pNext, c);
    ++m_size;
}

void List::add_back(const Circle& c){
    new Node(&Tail, c);
    ++m_size;
}

bool List::remove_first(const Circle& c){
    Node* p = Head.pNext;
    while (p != &Tail){
        if (p->m_Data == c){ // проверка равенства с с
            delete p; // деструктор исключает узел из списка
            --m_size;
            return true;
        }
        p = p->pNext;
    }
    return false;
}

size_t List::remove_all(const Circle& c){
    size_t count = 0;
    Node* p = Head.pNext;
    while (p != &Tail){
        Node* next = p->pNext; // запоминаем следующий до удаления
        if (p->m_Data == c){
            delete p;
            --m_size;
            ++count;
        }
        p = next; // переходим к сохранённому следующему
    }
    return count;
}

void List::clear(){
    Node* p = Head.pNext;
    while (p != &Tail){
        Node* next = p->pNext;
        delete p;
        p = next;
    }
    m_size = 0;
}

size_t List::size(){
    return m_size; 
}

bool List::empty(){
    return m_size == 0; 
}

void List::swap_data(Node* a, Node* b){
    Circle temp = a->m_Data;
    a->m_Data = b->m_Data;
    b->m_Data = temp;
}

void List::quick_sort(Node* left, Node* right){
    if (left == right || left->pPrev == right) return; // один элемент или пустой дапазон
    Node* pivot = right; // последний элемент диапазона
    Node* i = left->pPrev; // последний элемент диапазона меньше опорного элемента

    for (Node* j = left; j != right; j = j->pNext){
        if (j->m_Data.area() < pivot->m_Data.area()){
            i = i->pNext;
            swap_data(i, j);
        }
    }
    i = i->pNext; // после цикла i указывает на последний элемент, меньший опорного.
    swap_data(i, pivot);

    if (i != left) quick_sort(left, i->pPrev); // сортируем части до и после опорного элемента
    if (i != right) quick_sort(i->pNext, right); // при условии непустого диапазона
}

void List::sort(){
    quick_sort(Head.pNext, Tail.pPrev);
}

std::ostream& operator<<(std::ostream& os, const List& list){
    List::Node* p = list.Head.pNext;
    while (p != &list.Tail){
        os << "центр: (" << p->m_Data.get_center().get_x()<< ", " << p->m_Data.get_center().get_y()<< "), "
            << "радиус = " << p->m_Data.get_radius() << ", "
            << "площадь = " << p->m_Data.area() << '\n';
        p = p->pNext;
    }
    return os;
}

void List::write_to_file(const char* filename){
    std::ofstream fout(filename);
    if (!fout) return;
    Node* p = Head.pNext;
    while (p != &Tail){
        fout << p->m_Data.get_center().get_x() << ' ' 
             << p->m_Data.get_center().get_y() << ' ' 
             << p->m_Data.get_radius() << '\n';
        p = p->pNext;
    }
    fout.close();
}

void List::read_from_file(const char* filename){
    std::ifstream fin(filename);
    if (!fin) return;
    clear();
    double x, y, r;
    while (fin >> x >> y >> r){ // читаем по три числа
        add_back(Circle(x, y, r));
    }
    fin.close();
}

List::~List(){
    clear();
}

List& List::operator=(const List& other){
    if (this != &other) {
        clear();
        Node* p = other.Head.pNext;
        while (p != &other.Tail) {
            add_back(p->m_Data);
            p = p->pNext;
        }
    }
    return *this;
}

Circle& List::index_find(int index){
    if (index >= m_size || index < 0) throw std::out_of_range("неверный индекс");
    Node* p = Head.pNext;
    for (int i = 0; i < index; ++i)
        p = p->pNext;
    return p->m_Data;
}

void List::reverse(){
    if (m_size < 2) return;
    Node* left = Head.pNext;
    Node* right = Tail.pPrev;
    while (left != right && left->pPrev != right){
        swap_data(left, right);
        left = left->pNext;
        right = right->pPrev;
    }
}

void List::sort_reverse(){
    sort();
    reverse();
}

List::List(const List& other):List(){
    Node* p = other.Head.pNext;
    while (p != &other.Tail) {
        add_back(p->m_Data);
        p = p->pNext;
    }
}