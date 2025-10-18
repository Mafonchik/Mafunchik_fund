#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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

double round(double x) {
    return (long long)(x + 0.5);
}

// Проверяет, имеет ли дробь x конечное представление в системе с основанием base
int has_finite_representation(double x, int base) {
    if (x <= 0.0 || x >= 1.0) {
        return OUT_OF_RANGE;
    }

    const long long DENOM = 1000000000LL;
    long long num = (long long)round(x * DENOM);
    long long den = DENOM;

    long long g = gcd(num, den);
    num /= g;
    den /= g;

    // Удалим из den все общие простые делители с base
    int b = base;
    long long d = gcd(den, b);
    while (d > 1) {
        while (den % d == 0) {
            den /= d;
        }
        d = gcd(den, b);
    }

    // Если после удаления всех общих делителей den == 1 -- конечное представление
    return (den == 1);
}

void check_fractions(int base, int count, ...) {
    if (base < 2) {
        return;
    }
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


// Функция для запуска тестов
void run_tests() {
    printf("=== ТЕСТИРОВАНИЕ ===\n\n");
    
    // Тест 1: Двоичная система
    printf("Тест 1: Двоичная система (base = 2)\n");
    check_fractions(2, 6,
        0.5,      // конечная
        0.25,     // конечная
        0.125,    // конечная
        0.1,      // бесконечная 
        1.0/3, // бесконечная 
        0.75      // конечная
    );
    printf("\n");

    // Тест 2: Десятичная система
    printf("Тест 2: Десятичная система (base = 10)\n");
    check_fractions(10, 6,
        0.0000000000000000000000000001,      // конечная 
        0.125,    // конечная 
        0.25,     // конечная
        0.3333333333333333333333333333333333333333333333333,      // конечная
        0.0625    // конечная
    );
    printf("\n");

    // Тест 3: Восьмеричная система
    printf("Тест 3: Восьмеричная система (base = 8)\n");
    check_fractions(8, 5,
        0.5,      // конечная 
        0.125,    // конечная
        0.25,     // конечная
        0.1,      // бесконечная 
        0.0625    // конечная
    );
    printf("\n");

    // Тест 4: Шестнадцатеричная система
    printf("Тест 4: Шестнадцатеричная система (base = 16)\n");
    check_fractions(255, 5,
        1.0/255,      // конечная 
        255,     // конечная 
        0.125,    // конечная 
        0.0625,   // конечная 
        0.1       // бесконечная 
    );
    printf("\n");

}

int main() {
    run_tests();
    return 0;
}