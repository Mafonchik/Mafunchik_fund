#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "header.h"
#include "main.c"

// Макрос для проверки утверждений с выводом ошибки и завершением программы
#define ASSERT(expr) do { \
    if (!(expr)) { \
        fprintf(stderr, "ASSERTION FAILED: %s at %s:%d\n", #expr, __FILE__, __LINE__); \
        exit(1); \
    } \
} while(0)

// Тест функции memchr - поиск символа в памяти
void test_memchr() {
    const char s[] = "hello world";
    ASSERT(memchr(s, 'w', sizeof(s)) == s + 6);  // Находим 'w' на позиции 6
    ASSERT(memchr(s, 'x', sizeof(s)) == NULL);   // Несуществующий символ
    ASSERT(memchr(s, '\0', sizeof(s)) == s + 11); // Нулевой терминатор
}

// Тест функции memcmp - сравнение областей памяти
void test_memcmp() {
    const char a[] = "abc";
    const char b[] = "abd";
    ASSERT(memcmp(a, b, 3) < 0);  // a < b
    ASSERT(memcmp(a, a, 3) == 0); // a == a
    ASSERT(memcmp(b, a, 3) > 0);  // b > a
}

// Тест функции memcpy - копирование памяти
void test_memcpy() {
    char src[] = "hello";
    char dest[10] = {0};
    memcpy(dest, src, 6);  // Копируем 6 байт (включая '\0')
    ASSERT(strcmp(dest, "hello") == 0);
}

// Тест функции memset - заполнение памяти значением
void test_memset() {
    char buf[10];
    memset(buf, 'A', 5);  // Заполняем 5 байт символом 'A'
    buf[5] = '\0';        // Добавляем терминатор
    ASSERT(strcmp(buf, "AAAAA") == 0);
}

// Тест функции strncat - конкатенация строк с ограничением длины
void test_strncat() {
    char dest[20] = "hello";
    strncat(dest, " world", 6);  // Добавляем " world"
    ASSERT(strcmp(dest, "hello world") == 0);

    char dest2[10] = "hi";
    strncat(dest2, " there", 3); // Добавляем только " th"
    ASSERT(strcmp(dest2, "hi th") == 0);
}

// Тест функции strchr - поиск первого вхождения символа в строке
void test_strchr() {
    const char s[] = "hello";
    ASSERT(strchr(s, 'e') == s + 1);   // Находим 'e' на позиции 1
    ASSERT(strchr(s, 'x') == NULL);    // Несуществующий символ
    ASSERT(strchr(s, '\0') == s + 5);  // Нулевой терминатор
}

// Тест функции strncmp - сравнение строк с ограничением длины
void test_strncmp() {
    ASSERT(strncmp("abc", "abd", 3) < 0);   // abc < abd
    ASSERT(strncmp("abc", "abc", 5) == 0);  // Равные строки
    ASSERT(strncmp("abd", "abc", 3) > 0);   // abd > abc
    ASSERT(strncmp("ab", "abc", 5) < 0);    // Короткая строка меньше
}

// Тест функции strncpy - копирование строки с ограничением длины
void test_strncpy() {
    char dest[10];
    strncpy(dest, "hi", 5);  // Копируем 5 символов
    ASSERT(strcmp(dest, "hi") == 0);
    // Проверяем что остальные символы заполнены нулями
    ASSERT(dest[2] == '\0');
    ASSERT(dest[3] == '\0');
    ASSERT(dest[4] == '\0');
}

// Тест функции strspn - длина префикса из допустимых символов
void test_strspn() {
    ASSERT(strspn("aaabbb", "ab") == 6);  // Все символы из множества "ab"
    ASSERT(strspn("aaaccc", "ab") == 3);  // Только первые 3 символа
    ASSERT(strspn("xyz", "ab") == 0);     // Ни одного символа из множества
    ASSERT(strspn("", "ab") == 0);        // Пустая строка
}

// Тест функции strerror - получение строки описания ошибки
void test_strerror() {
    // Проверим несколько известных ошибок
    ASSERT(strcmp(strerror(0), "Success") == 0 || strcmp(strerror(0), "Undefined error: 0") == 0);
    ASSERT(strcmp(strerror(EPERM), "Operation not permitted") == 0);
    ASSERT(strcmp(strerror(ENOENT), "No such file or directory") == 0);
}

// Тест функции strlen - вычисление длины строки
void test_strlen() {
    ASSERT(strlen("hello") == 5);
    ASSERT(strlen("") == 0);
    ASSERT(strlen("a") == 1);
}

// Тест функции strpbrk - поиск любого символа из множества
void test_strpbrk() {
    ASSERT(strpbrk("xyz", "aeiou") == NULL);     // Нет гласных
    ASSERT(strpbrk("hello", "xyz") == NULL);     // Нет символов из "xyz"
    ASSERT(strpbrk("hello", "h") == "hello");    // Находим 'h' в начале
}

// Тест функции strrchr - поиск последнего вхождения символа
void test_strrchr() {
    const char s[] = "hello world";
    ASSERT(strrchr(s, 'o') == s + 7);    // Последняя 'o' на позиции 7
    ASSERT(strrchr(s, 'x') == NULL);     // Несуществующий символ
    ASSERT(strrchr(s, '\0') == s + 11);  // Нулевой терминатор
}

// Тест функции strstr - поиск подстроки
void test_strstr() {
    const char h[] = "hello world";
    ASSERT(strstr(h, "world") == h + 6);  // Находим "world"
    ASSERT(strstr(h, "lo wo") == h + 3);  // Находим "lo wo"
    ASSERT(strstr(h, "xyz") == NULL);     // Несуществующая подстрока
    ASSERT(strstr(h, "") == h);           // Пустая подстрока
}

// Тест функции strtok - разбиение строки на токены
void test_strtok() {
    char s1[] = "a,b,c";
    char *token = strtok(s1, ",");
    ASSERT(strcmp(token, "a") == 0);
    token = strtok(NULL, ",");
    ASSERT(strcmp(token, "b") == 0);
    token = strtok(NULL, ",");
    ASSERT(strcmp(token, "c") == 0);
    token = strtok(NULL, ",");
    ASSERT(token == NULL);

    // Проверка с несколькими разделителями
    char s2[] = "  foo  bar  ";
    token = strtok(s2, " ");
    ASSERT(strcmp(token, "foo") == 0);
    token = strtok(NULL, " ");
    ASSERT(strcmp(token, "bar") == 0);
    token = strtok(NULL, " ");
    ASSERT(token == NULL);
}

// Главная функция - запуск всех тестов
int main(void) {
    test_memchr();
    test_memcmp();
    test_memcpy();
    test_memset();
    test_strncat();
    test_strchr();
    test_strncmp();
    test_strncpy();
    test_strspn();
    test_strerror();
    test_strlen();
    test_strpbrk();
    test_strrchr();
    test_strstr();
    test_strtok();

    printf("✅ All tests passed!\n");
    return 0;
}