#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "laba.h"

// Наибольший общий делитель (НОД)
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Проверяет, имеет ли дробь x конечное представление в системе с основанием base
int has_finite_representation(double x, int base) {
    if (x <= 0.0 || x >= 1.0) {
        return OUT_OF_RANGE; // вне диапазона
    }

    const long long DENOM = 1000000000LL; // 10^9
    long long num = (long long)round(x * DENOM);
    long long den = DENOM;

    // Сократим дробь
    long long g = gcd(num, den);
    num /= g;
    den /= g;

    // Удалим из den все общие простые делители с base
    int b = base;
    // Находим НОД(den, base) и делим den на него, пока возможно
    long long d = gcd(den, b);
    while (d > 1) {
        while (den % d == 0) {
            den /= d;
        }
        d = gcd(den, b);
    }

    // Если после удаления всех общих делителей den == 1 → конечное представление
    return (den == 1);
}

// Основная функция с переменным числом аргументов
// Первый аргумент — основание системы счисления
// Второй — количество дробей
// Остальные — сами дроби (double)
void check_fractions(int base, int count, ...) {
    va_list args;
    va_start(args, count);

    printf("Base: %d\n", base);
    for (int i = 0; i < count; ++i) {
        double x = va_arg(args, double);
        int finite = has_finite_representation(x, base);
        printf("  %.10f -> %s\n", x, finite ? "finite" : "infinite");
    }

    va_end(args);
}

// Пример использования
int main() {
    // Проверим дроби в двоичной системе (основание 2)
    check_fractions(2, 4,
        0.5,      // 1/2 → конечная
        0.25,     // 1/4 → конечная
        0.1,      // 1/10 → бесконечная в двоичной
        0.75      // 3/4 → конечная
    );

    printf("\n");

    // В десятичной системе (основание 10)
    check_fractions(10, 3,
        0.1,      // конечная
        0.3333333333, // 1/3 → бесконечная
        0.125     // 1/8 → конечная (8 = 2^3, а 10 = 2*5 → OK)
    );

    return 0;
}