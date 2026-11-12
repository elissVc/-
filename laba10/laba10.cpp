#define NOMINMAX

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <windows.h>

struct Point {
    double x, y;
    double distance(const Point& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
};

enum CreationMode { FROM_VERTICES, FROM_MEDIAN_BASES };

class AbstractTriangle {
public:
    virtual ~AbstractTriangle() = default;

    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual double getMedian(int index) const = 0;
    virtual double getMidsegment(int sideIndex) const = 0;
    virtual double getInradius() const = 0;
    virtual double getCircumradius() const = 0;
    virtual void printInfo() const = 0;
};

class TriangleCoords : public AbstractTriangle {
protected:
    Point A, B, C;

    double a() const { return B.distance(C); }
    double b() const { return A.distance(C); }
    double c() const { return A.distance(B); }

public:
    TriangleCoords(Point p1, Point p2, Point p3, CreationMode mode = FROM_VERTICES)
        : A(p1), B(p2), C(p3)
    {
        if (mode == FROM_MEDIAN_BASES) {
            A = { p2.x + p3.x - p1.x, p2.y + p3.y - p1.y };
            B = { p1.x + p3.x - p2.x, p1.y + p3.y - p2.y };
            C = { p1.x + p2.x - p3.x, p1.y + p2.y - p3.y };
        }
    }

    double getPerimeter() const override { return a() + b() + c(); }

    double getArea() const override {
        double p = getPerimeter() / 2;
        return std::sqrt(p * (p - a()) * (p - b()) * (p - c()));
    }

    double getMedian(int index) const override {
        double sa = a(), sb = b(), sc = c();
        if (index == 0) return 0.5 * std::sqrt(2 * sb * sb + 2 * sc * sc - sa * sa);
        if (index == 1) return 0.5 * std::sqrt(2 * sa * sa + 2 * sc * sc - sb * sb);
        if (index == 2) return 0.5 * std::sqrt(2 * sa * sa + 2 * sb * sb - sc * sc);
        return 0;
    }

    double getMidsegment(int sideIndex) const override {
        if (sideIndex == 0) return a() / 2;
        if (sideIndex == 1) return b() / 2;
        if (sideIndex == 2) return c() / 2;
        return 0;
    }

    double getInradius() const override { return getArea() / (getPerimeter() / 2); }
    double getCircumradius() const override { return (a() * b() * c()) / (4 * getArea()); }

    void printInfo() const override {
        std::cout << "Трикутник (за координатами): A(" << A.x << "," << A.y
            << ") B(" << B.x << "," << B.y << ") C(" << C.x << "," << C.y << ")\n";
    }
};

class TriangleSides : public AbstractTriangle {
protected:
    double a, b, c;
public:
    TriangleSides(double sa, double sb, double sc) : a(sa), b(sb), c(sc) {}

    double getPerimeter() const override { return a + b + c; }
    double getArea() const override {
        double p = getPerimeter() / 2;
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }
    double getMedian(int index) const override {
        if (index == 0) return 0.5 * std::sqrt(2 * b * b + 2 * c * c - a * a);
        if (index == 1) return 0.5 * std::sqrt(2 * a * a + 2 * c * c - b * b);
        if (index == 2) return 0.5 * std::sqrt(2 * a * a + 2 * b * b - c * c);
        return 0;
    }
    double getMidsegment(int sideIndex) const override {
        if (sideIndex == 0) return a / 2;
        if (sideIndex == 1) return b / 2;
        if (sideIndex == 2) return c / 2;
        return 0;
    }
    double getInradius() const override { return getArea() / (getPerimeter() / 2); }
    double getCircumradius() const override { return (a * b * c) / (4 * getArea()); }

    void printInfo() const override {
        std::cout << "Трикутник (за сторонами): a=" << a << ", b=" << b << ", c=" << c << "\n";
    }
};

class RightTriangle : public TriangleCoords {
public:
    RightTriangle(Point p1, Point p2, Point p3) : TriangleCoords(p1, p2, p3) {}

    double getInradius() const override {
        double s1 = a(), s2 = b(), s3 = c();
        double hyp = std::max({ s1, s2, s3 });
        double leg1, leg2;

        if (hyp == s1) { leg1 = s2; leg2 = s3; }
        else if (hyp == s2) { leg1 = s1; leg2 = s3; }
        else { leg1 = s1; leg2 = s2; }

        return (leg1 + leg2 - hyp) / 2.0;
    }

    double getCircumradius() const override {
        return std::max({ a(), b(), c() }) / 2.0;
    }

    void printInfo() const override {
        std::cout << "Прямокутний ";
        TriangleCoords::printInfo();
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TriangleCoords t1({ 0, 0 }, { 4, 0 }, { 0, 3 });
    TriangleCoords t2({ 2, 0 }, { 2, 1.5 }, { 0, 1.5 }, FROM_MEDIAN_BASES);
    RightTriangle rt({ 0, 0 }, { 8, 0 }, { 0, 6 });

    std::vector<AbstractTriangle*> triangles = { &t1, &t2, &rt };

    for (const auto& t : triangles) {
        t->printInfo();
        std::cout << "Площа: " << t->getArea() << "\n";
        std::cout << "Медіана з першої вершини: " << t->getMedian(0) << "\n";
        std::cout << "Середня лінія паралельна 1-й стороні: " << t->getMidsegment(0) << "\n";
        std::cout << "Радіус вписаного кола (r): " << t->getInradius() << "\n";
        std::cout << "Радіус описаного кола (R): " << t->getCircumradius() << "\n";
        std::cout << "\n";
    }

    return 0;
}