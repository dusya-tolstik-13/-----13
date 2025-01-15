#pragma once
#ifndef dasha_h
#include <string>

using namespace std;

// проверка на корректность (защита от дурака)
bool proverkavvoda(const string& chislo);

// функция вычисляет остаток от деления длинного числа на обычное число
int ost(const string& num, int d);

// удаляем ведущие нули из строки
string udalenie(const string& str);

// функция для деления длинного числа на обычное число
string divide(const string& num, int d);

// генерируем массив простых чисел до заданного предела
void gen(bool* ps, int lim);

// находим количество делителей длинного числа
int kolvodel(string num);

#endif 
