#include <iostream>
#include <fstream>
#include "circle.hpp"

int main(){
    List list;
    list.add_back(Circle(0, 0, 5));
    list.add_front(Circle(1, 1, 2));
    list.add_back(Circle(2, 2, 3));
    list.add_front(Circle(-1, -1, 4));
    list.add_back(Circle(3, 3, 2));
    list.add_back(Circle(3, 3, 2));
    
    std::cout << list << '\n';
    std::cout << "размер: " << list.size() << "\n";

    std::cout << "первый элемент: " << list.index_find(0).get_center().get_x() << ' ' << list.index_find(0).get_center().get_y() << ' ' \
    << list.index_find(0).area()<< '\n';
    
    if (list.remove_first(Circle(1, 1, 2))) {
        std::cout << "элемент удалён: "  << list << '\n';
        
    }

    std::cout << "размер списка: " << list.size() << "\n";
    size_t removed = list.remove_all(Circle(3, 3, 2));
    std::cout << "удалено элементов: " << removed << "\n";
    std::cout << "новый размер: " << list.size() << "\n\n";
    
    std::cout<< "текущий список: " << list << '\n';
    list.reverse();
    std::cout<< "новый список: " << list << "\n";

    std::cout << "сортировка: \n";
    list.sort();
    std::cout << list << "\n";

    std::cout << "сортировка по убыванию: \n";    
    list.sort_reverse();
    std::cout << list << "\n";

    list.write_to_file("test/test.txt");
    list.read_from_file("test/test.txt");
    std::cout << "прочитано из файла:\n" << list << "\n"; 

    List copy;
    copy = list;
    std::cout << "cписок copy:\n" << copy << "\n";

    list.clear();
    if (list.empty()){
        std:: cout << "список пустой\n";
    }
    else{
        std:: cout << "список не пустой\n";
    }
    
    return 0;
}