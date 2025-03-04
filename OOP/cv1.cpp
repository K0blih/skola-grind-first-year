#include <iostream>
using namespace std;

class Point {   
public:
    int x;
    int y;

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    void display() {
        cout << "Point values: " << this->x << " " << this->y << "\n";
    }
};

class Vektor {
public:
    int x;
    int y;

    Vektor(Point pointA, Point pointB) {
        this->x = pointB.x - pointA.x;
        this->y = pointB.y - pointA.y;
    }

    void display() {
        cout << "Vektor values: " << this->x << " " << this->y << "\n";
    }
};

int main() {
    Point point1(1, 2);
    Point point2(3, 4);
    point1.display();

    Vektor vektor1(point1, point2);
    vektor1.display();

    return 0;
}
