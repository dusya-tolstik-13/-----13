#include <iostream>
#include "dasha.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    string chislo;

    cout << "Данная программа вычисляет количество делителей n-значного числа (n > 20)." << endl;
    cout << "Введите n-значное натуральное число (n > 20): ";
    cin >> chislo;

    // Проверка на корректность (защита от дурака)
    if (!proverkavvoda(chislo)) {
        return 1; // завершаем выполнение программы, если ввод некорректен
    }
    // находим количество делителей
    int delit = kolvodel(chislo);
    cout << "Количество делителей числа " << chislo << ": " << delit << endl;

    return 0;
}
