#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <string.h>

// Функция сравнения строк с обработкой NULL
int string_equal(const char* a, const char* b) {
    if (!a && !b) return 1;
    if (!a || !b) return 0;
    return strcmp(a, b) == 0;
}

// Запуск одного теста
void run_test(const char* category, int num, int r, const char* expected) {
    printf("ВВОД: num = %d, r = %d; ОЖИДАЕМЫЙ РЕЗУЛЬТАТ = %s\n", num, r, expected);
    char* result = conversion(num, r);
    if (string_equal(result, expected)) {
        printf("ИТОГ: УСПЕХ. РЕЗУЛЬТАТ = %s\n", result ? result : "(null)");
    } else {
        printf("ИТОГ: НЕУДАЧА. РЕЗУЛЬТАТ = %s\n", result ? result : "(null)");
    }
    free(result);
}

int main() {
    printf("===ПОЛОЖИТЕЛЬНЫЕ ЧИСЛА===\n");
    run_test("positive", 10, 1, "1010");
    run_test("positive", 15, 2, "33");
    run_test("positive", 100, 3, "164");
    run_test("positive", 255, 4, "FF");
    run_test("positive", 1023, 5, "VV");

    printf("\n===ОТРИЦАТЕЛЬНЫЕ ЧИСЛА===\n");
    run_test("negative", -1, 1, "-1");
    run_test("negative", -10, 2, "-22");
    run_test("negative", -100, 3, "-164");
    run_test("negative", -255, 4, "-FF");
    run_test("negative", -1023, 5, "-VV");

    printf("\n===НУЛЬ===\n");
    run_test("zero", 0, 1, "0");
    run_test("zero", 0, 5, "0");

    printf("\n===ГРАНИЧНЫЕ ЗНАЧЕНИЯ===\n");
    run_test("edge", 1, 1, "1");
    run_test("edge", -1, 5, "-1");
    run_test("edge", 31, 5, "V");
    run_test("edge", 16, 4, "10");
    run_test("edge", 8, 3, "10");

    return 0;
}