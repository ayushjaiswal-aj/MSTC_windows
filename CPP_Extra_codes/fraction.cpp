#include <iostream>

using namespace std;

class Fraction{
    int numerator;
    int denominator;

    public:
    Fraction(int numerator, int denominator){
        this->numerator = numerator;
        this->denominator = denominator;
    }

    void display(){
        cout << "numerator: " << numerator << " " << "denominator: " << denominator << endl;
    }

    void add(Fraction f2){
        int lcm = this->denominator * f2. denominator;
        int x = lcm / denominator;
        int y = lcm / f2.denominator;

        int num = (x * this->numerator) + (y * f2.numerator);

        numerator = num;
        denominator = lcm; 
    }
};

int main(void){
    Fraction f1(12, 4);
    Fraction f2(13, 5);

    f1.display();
    f2.display();

    f1.add(f2);
    f1.display();

    return 0;
}