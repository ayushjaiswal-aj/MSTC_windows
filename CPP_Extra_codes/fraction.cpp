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

    void simplify(){
        int gcd = get_gcd(numerator, denominator);
        numerator = numerator / gcd;
        denominator = denominator / gcd;
    }

    void add(Fraction f2){
        int lcm = get_lcm(denominator, f2.denominator);
        int x = lcm / denominator;
        int y = lcm / f2.denominator;

        int num = (x * this->numerator) + (y * f2.numerator);

        numerator = num;
        denominator = lcm; 
    }

    void sub(Fraction f2){
        int lcm = get_lcm(denominator, f2.denominator);
        int x = lcm / denominator;
        int y = lcm / f2.denominator;

        int num = (x * this->numerator) - (y * f2.numerator);

        numerator = num;
        denominator = lcm;
    }

    private:
    int get_lcm(int a, int b){
        return (a * b)/get_gcd(a, b);
    }

    int get_gcd(int a, int b){
        if(a == 0){
            return b;
        }
        return get_gcd(b % a, a);
    }
};

int main(void){
    Fraction f1(12, 4);
    Fraction f2(13, 5);

    f1.display();
    f2.display();

    f1.add(f2);
    cout << "adding two fractions: " << endl;
    f1.display();

    f1.simplify();
    cout << "after simplifying the fraction: " << endl;
    f1.display();

    f1.sub(f2);
    cout << "after subtracting the fractions: " << endl;
    f1.display();

    f1.simplify();
    cout << "after simplifying the fraction: " << endl;
    f1.display();

    return 0;
}