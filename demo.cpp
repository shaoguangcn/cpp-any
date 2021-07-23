#include "any.h"
#include <iostream>

#include <any>

struct Point
{
    Point() = default;
    Point(double _x, double _y) : x(_x), y(_y) { }
    double x{ 0.0 };
    double y{ 0.0 };
};

int main(int, char*[])
{
    std::cout << std::boolalpha;

    // any type
    any a = 1;
    std::cout << a.type().name() << ": " << any_cast<int>(a) << '\n';
    a = 3.14;
    std::cout << a.type().name() << ": " << any_cast<double>(a) << '\n';
    a = true;
    std::cout << a.type().name() << ": " << any_cast<bool>(a) << '\n';

    // bad cast
    try {
        a = 1;
        std::cout << any_cast<float>(a) << '\n';
    } catch (const bad_any_cast& e) {
        std::cout << e.what() << '\n';
    }

    // has value
    a = 1;
    if (a.has_value()) {
        std::cout << a.type().name() << '\n';
    }

    // reset
    a.reset();
    if (!a.has_value()) {
        std::cout << "no value\n";
    }

    // pointer to contained data
    a = 1;
    int* i = any_cast<int>(&a);
    std::cout << *i << "\n";

    any any_pt = Point(10.0, 20.0);
    Point pt = any_cast<Point>(any_pt);
    std::cout << "Point.x=" << pt.x << std::endl;
    std::cout << "Point.y=" << pt.y << std::endl;

    return 0;
}