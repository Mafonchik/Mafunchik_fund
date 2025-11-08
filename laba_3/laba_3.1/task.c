#include <stdio.h>
#include <stdlib.h>
#include "header.h"
/* Реализуйте функцию перевода числа из десятичной системы счисления в систему
счисления с основанием 2𝑟 , 𝑟 = 1, … . , 5. При реализации функции разрешается
использовать битовые операции и операции обращения к памяти, запрещается
использовать стандартные арифметические операции. Продемонстрируйте
работу реализованной функции*/

void get_info(int *num, int *r) {
    printf("Введите число: ");
    scanf("%d", num);
    printf("Введите r(1-5): ");
    scanf("%d", r);
}

void reverse_string(char* num, int size) {
    for (int i = 0; i < size / 2; i++) {
        char temp = num[i];
        num[i] = num[size - 1 - i];
        num[size - 1 - i] = temp;
    }
}

void increase_memory(char** num, int new_size) {
    char* temp = realloc(*num, new_size);
    if (!temp) {
        free(*num);
        *num = NULL;
        return;
    }
    *num = temp;
}

int sign(int n) {
    n = ~n;
    int bit;
    for (bit = 1; bit && (bit & n); bit <<= 1) {
        n ^= bit; // или n &= ~bit;
    }
    return n ^ bit; // или n | bit
}

char* conversion(int og_num, int r) {
    if (og_num == 0) {
        char* result = malloc(2 * sizeof(char)); // "0\0"
        if (!result) return NULL;
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    int is_neg = 0;
    if (og_num < 0) {
        og_num = sign(og_num);
        is_neg = 1;
    }

    char* result = malloc(sizeof(char) * INIT_CAP);
    int ost;
    int size = 0;
    int cap = INIT_CAP;
    switch (r) {
        case 5:
            ost = 31;
            break;
        case 4:
            ost = 15;
            break;
        case 3:
            ost = 7;
            break;
        case 2:
            ost = 3;
            break;
        default:
        ost = 1;
        break;
    }

    while (og_num != 0) {
        if (size >= cap) { 
            cap <<= 1;
            increase_memory(&result, cap * sizeof(char));
            if (!result) return NULL;
}
        int digit = og_num & ost;
        // Преобразуем цифру в символ
        if (digit < 10) {
            result[size++] = '0' + digit;
        } else {
            result[size++] = 'A' + (digit - 10);
        }
        og_num >>= r;
    }
    if (is_neg) {
        result[size++] = '-';
    }
    reverse_string(result, size);
    result[size] = '\0';
    return result;

}