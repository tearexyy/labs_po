class Barrel
{
private:
    double amount;  
    double concentration;

public:
    Barrel(double vol, double conc);
    Barrel();
    void fill(Barrel& b);
    double getConcentration();
};