#include "ee.h" 
#include <iostream>

using namespace std;

bool ee::Init(double a, double b) {
    if (a == 0) {
        cout << "Помилка" << endl;
        return false;
    }
    first = a;
    second = b;
    return true;
}

void ee::Read() {
    double a, b;
    do {
        cout << "Введіть A: ";
        cin >> a;
        cout << "Введіть B: ";
        cin >> b;
    } while (!Init(a, b));
}

void ee::Display() const {
    cout << "y = " << first << "x ";
    if (second >= 0) {
        cout << "+ " << second << endl;
    }
    else {
        cout << "- " << -second << endl;
    }
}

double ee::function(double x) const {
    return first * x + second;
}