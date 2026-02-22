#include "rect.hpp"
#include <iostream>
Rect::Rect(){
        left = right = top = bottom = 0;
std::cout << "Вызов конструктора без параметров " << this << "\n";
}

Rect::Rect(int p1, int p2, int p3, int p4){
        left = p1;
        right = p2;
        top = p3;
        bottom = p4;
std::cout << "Вызов конструктора с параметрами " << this << "\n";
}

Rect::~Rect(){
    std::cout << "Вызов деструктора " << this << "\n";
}

Rect::Rect(const Rect &other){
left = other.left;
right = other.right;
top = other.top;
bottom = other.bottom;
std::cout << "Вызов конструктора копирования " << this << "\n";
}

int Rect::get_left(){return left;}
int Rect::get_right(){return right;}
int Rect::get_top(){return top;}
int Rect::get_bottom(){return bottom;}

void Rect::set_all(int left1, int right1, int top1, int bottom1){
    left = left1;
    right = right1;
    top = top1;
    bottom = bottom1;
}

void Rect::inflate(int amount){
    left-=amount;
    right+=amount;
    top+=amount;
    bottom-=amount;
}

void Rect::inflate(int dw, int dh){
    top+=dh;
    bottom -=dh;
    left-=dw;
    right+=dw;
}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom){
    left -= d_left;
    right += d_right;
    top+=d_top;
    bottom-=d_bottom;
}

void Rect::move(int x, int y){
    right += x;
    left += x;
    top += y;
    bottom += y;
}

Rect bounding_rect(Rect r1, Rect r2){
    int left = (r1.get_left() < r2.get_left()? r1.get_left() : r2.get_left());
    int right = (r1.get_right() > r2.get_right()? r1.get_right() : r2.get_right());
    int bottom = (r1.get_bottom() < r2.get_bottom() ? r1.get_bottom()  : r2.get_bottom() );
    int top = (r1.get_top() > r2.get_top()? r1.get_top() : r2.get_top());
    return Rect(left, right, top, bottom);
}

void print_rect(Rect &r){
    std::cout << "левая граница: " << r.get_left() << '\n';
    std::cout << "правая граница: " << r.get_right() << '\n';
    std::cout << "верхняя граница: " << r.get_top() << '\n';
    std::cout << "нижняя граница: " << r.get_bottom() << '\n';

    for (int i = r.get_left(); i < r.get_right(); i+=1){std::cout << " .";};
    std::cout<<'\n';
    for (int i = r.get_bottom()+1; i < r.get_top()-1; i+=1){
        std::cout<<" .";
        for (int j = r.get_left() + 1; i < r.get_right() -1; i+=1){
            std::cout << "  ";
        }
        std::cout<<" .\n"; 
    }
    for (int i = r.get_left(); i < r.get_right(); i+=1){std::cout << " .";};
    std::cout << '\n';
}

int Rect::get_width(){
    return right - left;
}

int Rect::get_height(){
    return top - bottom;
}

int Rect::get_square(){
    return ((top - bottom)*(right - left));
}

void Rect::set_width(int w){
    right = left + w;
}

void Rect::set_height(int h){
    top = bottom + h;
}