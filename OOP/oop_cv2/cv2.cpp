//#include <iostream>
//using namespace std;
//
//class Point {
//public:
//    int x, y;
//
//    Point(int x, int y) {
//        this->x = x;
//        this->y = y;
//    }
//
//    void display() {
//        cout << "Point values: " << this->x << " " << this->y << "\n";
//    }
//};
//
//class Vektor {
//public:
//    int x, y;
//
//    Vektor(Point *pointA, Point *pointB) {
//        this->x = pointB->x - pointA->x;
//        this->y = pointB->y - pointA->y;
//    }
//
//    void display() {
//        cout << "Vektor values: " << this->x << " " << this->y << endl;
//    }
//};
//
//int main() {
//    Point *point1 = new Point(1, 2);
//    Point *point2 = new Point(3, 4);
//    //Point point1 = Point(1, 2);
//    //Point point2(3, 4);
//    point1->display();
//
//    Vektor *vektor1 = new Vektor(point1, point2);
//    vektor1->display();
//
//    delete vektor1;
//    delete point1;
//    delete point2;
//    return 0;
//}
