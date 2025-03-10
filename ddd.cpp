#include "dasha.h"
#include <iostream>
#include <string>

using namespace std;
//проверка ввода на корректность (защита от дурака)
bool proverkavvoda(const string& chislo) {
    if (chislo.size() <= 20) {
        cout << "Число должно быть больше 20 символов!" << endl;
        return false;
    }

    bool nuli = true; // флаг для проверки, что строка состоит только из нулей
    for (char a : chislo) {
        if (a < '0' || a > '9') { // если символ не в диапазоне '0'-'9'
            cout << "число содержит недопустимые символы!" << endl;
            return false;
        }
        if (a != '0') { // если найден ненулевой символ
            nuli = false;
        }
    }
    if (nuli) { // если строка состоит из нулей
        cout << "число не может состоять только из нулей! " << endl;
        return false;
    }
    return true; 
}

// функция вычисляет остаток от деления длинного числа на обычное число
int ost(const string& num, int d) {
    int r = 0;
    for (char с : num) { // Поразрядно вычисляем остаток
        r = (r * 10 + (с - '0')) % d;
    }
    return r; // возвращаем остаток
}

// удаляем ведущие нули из строки
string udalenie(const string& str) {
    string result; // храним результат без ведущ нулей
    bool nol = false; // устанавливаем флаг для начала записи значимых символов
    for (char c : str) {
        if (c != '0' || nol) { // если найден знач. символ
            result += c;
            nol = true; // устанавливаем флаг значимого символа
        }
    }
    if (result.empty()) { // если строка полностью состоит из нулей
        return "0";
    }
    return result;
}

// функция для деления длинного числана обычное число
string divide(const string& num, int d) {
    string res; 
    int r = 0; // текущий остаток=0
    for (char с : num) {
        r = r * 10 + (с - '0'); // добавляем текущий разряд
        res += (r / d) + '0'; // вычисляем текущую цифру результата
        r %= d; // обновляем текущий остаток
    }
    // удаляем ведущие нули
    return udalenie(res);
}

// генерируем массив простых чисел до заданного предела
void gen(bool* ps, int lim) {
    for (int i = 0; i <= lim; ++i) {
        ps[i] = true; // в начеле все числа считаем простыми
    }
    ps[0] = ps[1] = false; // исключаем 0 и 1
    for (int i = 2; i * i <= lim; ++i) {
        if (ps[i]) { 
            for (int j = i * i; j <= lim; j += i) {
                ps[j] = false; // Помечаем кратные числа как составные
            }
        }
    }
}

// находим количество делителей длинного числа
int kolvodel(string num) {
    const int nachallim = 100000; // начальный лимит = 100000
    int clim = nachallim;

    // выделяем память для массива 
    bool* ps = new bool[clim + 1];
    gen(ps, clim); // генерируем массив

    int nacdel = 1; // начальное количество делителей

    bool isDivided = false; // флаг, показывающий, что число делится на хотя бы одно простое число

    while (num != "1") { // пока число не будет сведено к 1
        bool divided = false;

        // перебираем простые числа в массиве
        for (int p = 2; p <= clim; ++p) {
            if (ps[p]) { // если число является простым
                int pow = 0; // находим степень делителя
                while (ost(num, p) == 0) { // пока число делится без остатка
                    num = divide(num, p);
                    pow++; // степень увеличиваем
                    divided = true; // устанавливаем флаг делимости
                }
                nacdel *= (pow + 1); // учитываем множитель для количества делителей
            }
        }

        // если число не делится ни на одно простое из начального диапозона
        if (!divided) {
            // расширяем диапазон
            int newlim = clim * 2; // увеличиваем лимит проверки
            bool* newps = new bool[newlim + 1]; // создаем новый массив 
            gen(newps, newlim); // генерируем числа

            // освобождаем старый массив
            delete[] ps;
            ps = newps;
            clim = newlim; // обновляем предел

            // проверка, если число не делится и после расширения диапазона
            divided = false;
            for (int p = clim / 2 + 1; p <= clim; ++p) {
                if (ps[p] && ost(num, p) == 0) {
                    divided = true;
                    break;
                }
            }

            if (!divided) {
                // если число  не разложили, то оно простое
                nacdel = 2; // простое число имеет два делителя (1 и само себя)
                break;
            }
        }
    }

    // Освобождаем память
    delete[] ps;
    return nacdel; // Итоговое количество делителей
