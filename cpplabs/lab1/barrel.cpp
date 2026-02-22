#include "barrel.hpp"
#include <iostream>
using namespace std;

Barrel::Barrel(){
    amount = 0;
    concentration = 0;
}

Barrel::Barrel(double p1, double p2){
    amount = p1;
    concentration = p2;
}

void Barrel::fill(Barrel& b)
{
    amount -= 1;
    double b_amount = b.amount + 1;
    double b_concentration = (b.concentration * b.amount + concentration * 1) / b_amount;
    b.amount = b_amount;
    b.concentration = b_concentration;
}

double Barrel::getConcentration()
{
    return concentration;
}
