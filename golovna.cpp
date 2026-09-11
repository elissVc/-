#include <iostream>
#include <windows.h>
#include "ee.h" 

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ee eq;

    eq.Read();
    eq.Display();

    double x;
    cout << "\nÂâåä³òü x: ";
    cin >> x;

    double y = eq.function(x);
    cout << "Ïðè x = " << x << ", y = " << y << endl;

    return 0;
}