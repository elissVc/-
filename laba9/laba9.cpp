#include <iostream>
#include <cmath>
#include <windows.h>

class GeometricFigure {
protected:
    double x, y;
    double angle;
    double scale;
    bool isVisible;

public:
    GeometricFigure(double x = 0.0, double y = 0.0, double angle = 0.0, double scale = 1.0)
        : x(x), y(y), angle(angle), scale(scale), isVisible(false) {
    }

    virtual ~GeometricFigure() {
        std::cout << "Деструктор GeometricFigure" << std::endl;
    }

    virtual void show() = 0;
    virtual void hide() = 0;

    virtual void rotate(double dAngle) {
        angle += dAngle;
        while (angle >= 360.0) angle -= 360.0;
        while (angle < 0.0) angle += 360.0;
        std::cout << "Повернули на " << dAngle << " град. Поточний кут: " << angle << " град." << std::endl;
    }

    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
        std::cout << "\nПеремістили в точку: (" << x << ", " << y << ")" << std::endl;
    }

    virtual void setScale(double factor) {
        if (factor > 0) {
            scale *= factor;
            std::cout << "Новий масштаб: " << scale << std::endl;
        }
    }

    double getX() const { return x; }
    double getY() const { return y; }
    double getAngle() const { return angle; }
    double getScale() const { return scale; }
    bool getIsVisible() const { return isVisible; }
};

class MyRectangle : public GeometricFigure {
private:
    double width;
    double height;

public:
    MyRectangle(double x, double y, double w, double h, double angle = 0.0, double scale = 1.0)
        : GeometricFigure(x, y, angle, scale), width(w), height(h) {
    }

    ~MyRectangle() override {
        std::cout << "\nДеструктор MyRectangle" << std::endl;
    }

    void show() override {
        isVisible = true;
        std::cout << "\nПрямокутник" << std::endl;
        std::cout << "Стан: " << (isVisible ? "видимий" : "невидимий") << std::endl;
        std::cout << "Центр: (" << x << ", " << y << ")" << std::endl;
        std::cout << "Базові розміри: " << width << " х " << height << std::endl;
        std::cout << "Масштаб: " << scale << " (з урахуванням масштабу: " << width * scale << " х " << height * scale << ")" << std::endl;
        std::cout << "Кут повороту: " << angle << " град." << std::endl;
        std::cout << "Площа: " << getArea() << std::endl;
    }

    void hide() override {
        isVisible = false;
        std::cout << "\nЗробили прямокутник невидимим" << std::endl;
    }

    double getArea() const {
        return (width * scale) * (height * scale);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Лабораторна робота (5 варіант)" << std::endl;
    std::cout << "Перевірка роботи віртуальних функцій" << std::endl;

    GeometricFigure* figure = new MyRectangle(10.0, 15.0, 40.0, 20.0, 0.0, 1.0);

    figure->show();
    figure->move(5.5, -3.0);
    figure->rotate(45.0);
    figure->setScale(1.5);
    figure->show();
    figure->hide();

    delete figure;

    return 0;
}