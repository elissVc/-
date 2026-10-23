#include <iostream>
#include "MyTime.h"
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Time t1, t2;
    int choice;
    long secs;

    cout << "Ініціалізація початкового часу" << endl;
    t1.Read();

    do {
        cout << "\nМеню" << endl;
        cout << "Поточний час: "; t1.Display();
        cout << "1. Додати секунди\n";
        cout << "2. Відняти секунди\n";
        cout << "3. Перевести в загальні секунди\n";
        cout << "4. Перевести у хвилини (з округленням)\n";
        cout << "5. Порівняти з іншим часом та знайти різницю\n";
        cout << "0. Вийти з програми\n";
        cout << "Оберіть дію: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Скільки секунд додати? ";
            cin >> secs;
            t1.addSeconds(secs);
            cout << "Новий час: "; t1.Display();
            break;
        case 2:
            cout << "Скільки секунд відняти? ";
            cin >> secs;
            t1.subtractSeconds(secs);
            cout << "Новий час: "; t1.Display();
            break;
        case 3:
            cout << "Час у секундах: " << t1.toSeconds() << endl;
            break;
        case 4:
            cout << "Час у хвилинах: " << t1.toMinutesRounded() << endl;
            break;
        case 5: {
            cout << "\nВведіть другий час для порівняння:\n";
            t2.Read();
            cout << "\nРезультати порівняння:" << endl;
            cout << "Різниця: " << t1.differenceInSeconds(t2) << " секунд(и)." << endl;
            int cmp = t1.compare(t2);
            if (cmp == 1) cout << "Перший час більший за другий.\n";
            else if (cmp == -1) cout << "Перший час менший за другий.\n";
            else cout << "Час однаковий.\n";
            break;
		}
        case 0:
            cout << "Завершення роботи\n";
            break;
        default:
            cout << "Помилка. Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}