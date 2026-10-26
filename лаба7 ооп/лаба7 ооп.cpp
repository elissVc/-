#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <windows.h>

using namespace std;


class EmptyException {};

class ParamException {
public:
    int num, den;
    ParamException(int n, int d) : num(n), den(d) {}
};

class InheritedException : public invalid_argument {
public:
    int num, den;
    InheritedException(int n, int d, const string& msg)
        : invalid_argument(msg), num(n), den(d) {
    }
};

int getIntegerPart1(int n, int d) {
    if (d == 0 || abs(n) < abs(d)) {
        throw EmptyException();
    }
    return n / d;
}

int getIntegerPart2(int n, int d) throw(ParamException) {
    if (d == 0 || abs(n) < abs(d)) {
        throw ParamException(n, d);
    }
    return n / d;
}

int getIntegerPart3(int n, int d) throw(invalid_argument) {
    if (d == 0) {
        throw invalid_argument("Ділення на нуль");
    }
    if (abs(n) < abs(d)) {
        throw invalid_argument("Дріб не є неправильним");
    }
    return n / d;
}

int getIntegerPart4(int n, int d) throw(InheritedException) {
    if (d == 0) {
        throw InheritedException(n, d, "Ділення на нуль");
    }
    if (abs(n) < abs(d)) {
        throw InheritedException(n, d, "Дріб не є неправильним");
    }
    return n / d;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n, d;

    cout << "Варіант 10" << endl;

    cout << "Функція 1 (без специфікації)" << endl;
    cout << "Введіть чисельник: "; cin >> n;
    cout << "Введіть знаменник: "; cin >> d;
    try {
        int result = getIntegerPart1(n, d);
        cout << "Результат: ціла частина дорівнює " << result << "\n" << endl;
    }
    catch (EmptyException&) {
        cout << "Дріб правильний або знаменник = 0\n" << endl;
    }

    cout << "Функція 2 (специфікація throw(ParamException))" << endl;
    cout << "Введіть чисельник: "; cin >> n;
    cout << "Введіть знаменник: "; cin >> d;
    try {
        int result = getIntegerPart2(n, d);
        cout << "Результат: ціла частина дорівнює " << result << "\n" << endl;
    }
    catch (ParamException& e) {
        cout << "Помилкові параметри. Чисельник="<< e.num << ", Знаменник=" << e.den << "\n" << endl;
    }

    cout << "Функція 3 (специфікація throw(std::invalid_argument))" << endl;
    cout << "Введіть чисельник: "; cin >> n;
    cout << "Введіть знаменник: "; cin >> d;
    try {
        int result = getIntegerPart3(n, d);
        cout << "Результат: ціла частина дорівнює " << result << "\n" << endl;
    }
    catch (invalid_argument& e) {
        cout << "Помилка: " << e.what() << "\n" << endl;
    }

    cout << "Функція 4 (специфікація throw(InheritedException))" << endl;
    cout << "Введіть чисельник: "; cin >> n;
    cout << "Введіть знаменник: "; cin >> d;
    try {
        int result = getIntegerPart4(n, d);
        cout << "Результат: ціла частина дорівнює " << result << "\n" << endl;
    }
    catch (InheritedException& e) {
        cout << "Помилка: " << e.what()
            << " (Введені числа: " << e.num << " та " << e.den << ")\n" << endl;
    }

    return 0;
}