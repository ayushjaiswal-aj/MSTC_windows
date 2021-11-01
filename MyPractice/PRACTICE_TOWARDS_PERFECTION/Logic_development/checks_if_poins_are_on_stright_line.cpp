/*
 *checks if three points are in line.
 */

#include <iostream>

using namespace std;

class Point{
    public:
    double x, y;

    Point(double x, double y){
        this->x = x;
        this->y = y;
    }
};

int are_on_stringt_line(Point *p1, Point *p2, Point *p3);

int main(void){
    double x, y;
    cout << "Enter number point: " << endl;
    cin >> x >> y;
    Point *p1 = new Point(x, y);
    cout << "Enter number point: " << endl;
    cin >> x >> y;
    Point *p2 = new Point(x, y);
    cout << "Enter number point: " << endl;
    cin >> x >> y;
    Point *p3 = new Point(x, y);
    
    if(are_on_stringt_line(p1, p2, p3)){
        cout << "points are on same line" << endl;
    }
    else {
        cout << "Points are not on same line" << endl;
    }

    return 0;
}

int are_on_stringt_line(Point *p1, Point *p2, Point *p3){
    double slope1, slope2;

    slope1 = (p1->x - p2->x) / (p1->y - p2->y);
    slope2 = (p2->x - p3->x) / (p2->y - p3->y);

    if(slope1 == slope2){
        return 1;
    }
    else {
        return 0;
    }
}