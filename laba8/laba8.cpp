#include <iostream>
#include <windows.h>
using namespace std;

class Triad {
protected:
    int first;
    int second;
    int third;

public:
    Triad(int f = 0, int s = 0, int t = 0) {
        first = f;
        second = s;
        third = t;
    }

    virtual ~Triad() {}

    int compare(const Triad& other) const {
        if (first > other.first) return 1;
        if (first < other.first) return -1;

        if (second > other.second) return 1;
        if (second < other.second) return -1;

        if (third > other.third) return 1;
        if (third < other.third) return -1;

        return 0;
    }

    void print() const {
        cout << "(" << first << ", " << second << ", " << third << ")";
    }

    int getFirst() const { return first; }
    int getSecond() const { return second; }
    int getThird() const { return third; }
};

class Date : public Triad {
public:
    Date(int year, int month, int day) : Triad(year, month, day) {}

    bool operator==(const Date& other) const { return compare(other) == 0; }
    bool operator!=(const Date& other) const { return compare(other) != 0; }
    bool operator>(const Date& other) const { return compare(other) == 1; }
    bool operator<(const Date& other) const { return compare(other) == -1; }
    bool operator>=(const Date& other) const { return compare(other) >= 0; }
    bool operator<=(const Date& other) const { return compare(other) <= 0; }

    void printDate() const {
        cout << third << "." << second << "." << first;
    }
};

Triad processTriad(const Triad& obj) {
    cout << "Отримано об'єкт як базову трійку: ";
    obj.print();
    cout << "\n";

    Triad newObj(obj.getFirst() + 1, obj.getSecond() + 1, obj.getThird() + 1);
    return newObj;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Створення об'єктів:\n";
    Triad t1(1, 2, 3);
    cout << "Базовий клас Triad: ";
    t1.print();

    Date d1(2023, 10, 25);
    Date d2(2024, 1, 1);
    cout << "\nПохідний клас Date (Дата 1): ";
    d1.printDate();
    cout << "\nПохідний клас Date (Дата 2): ";
    d2.printDate();
    cout << "\n\n";

    cout << "Порівняння дат:\n";
    cout << "Порівнюємо Дату 1 (" << d1.getThird() << "." << d1.getSecond() << "." << d1.getFirst() << ") ";
    cout << "та Дату 2 (" << d2.getThird() << "." << d2.getSecond() << "." << d2.getFirst() << "):\n";

    if (d1 < d2) {
        cout << "Дата 1 передує Даті 2 (вона менша)\n";
    }
    if (d1 != d2) {
        cout << "Ці дві дати не однакові\n";
    }
    if (d2 > d1) {
        cout << "Дата 2 йде після Дати 1 (вона більша)\n";
    }
    cout << "\n";

    cout << "Демонстрація принципу підстановки:\n";
    cout << "Передаємо об'єкт Date (Дату 1) у функцію, яка очікує базовий клас Triad\n";

    Triad result = processTriad(d1);

    cout << "Результат: Функція успішно повернула новий об'єкт базового класу: ";
    result.print();
    cout << "\n\n";

    return 0;
}