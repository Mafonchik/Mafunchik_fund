#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "header.hpp"

// a
void *memchr(const void *str, int c, size_t n) {
    const unsigned char *p = (const unsigned char *)str;
    unsigned char uc = (unsigned char)c;
    for (size_t i = 0; i < n; i++) {
        if (p[i] == uc) {
            return (void *)(p + i);
        }
    }
    return NULL;
}
// b
int memcmp(const void* str1, const void* str2, size_t n) {
    const unsigned char *p1 = (const unsigned char *)str1;
    const unsigned char *p2 = (const unsigned char *)str2;
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        } 
    }
    return 0;
}
// c
void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *dst = (unsigned char *)dest;
    const unsigned char* src_bytes = (const unsigned char *)src;

    for (size_t i = 0; i < n; i++) {
        dst[i] = src_bytes[i];
    }

    return dest;
}
// d
void* memset(void* str, int c, size_t n) {
    unsigned char *string = (unsigned char *)str;
    unsigned char ch = (unsigned char)c;
    for (size_t i = 0; i < n; i++) {
        string[i] = ch;
    }
    return str;
}
// e
char *strncat(char *dest, const char *src, size_t n) {
    char *og_dest = dest;
    
    // Находим конец строки dest
    while (*dest != '\0') {
        dest++;
    }
    
    // Копируем до n символов из src
    while (n > 0 && *src != '\0') {
        *dest = *src;
        dest++;
        src++;
        n--;
    }
    
    // Добавляем завершающий нулевой символ
    *dest = '\0';
    
    return og_dest;
}
// f
char *strchr(const char *str, int c) {
    unsigned char uc = (unsigned char)c;
    
    while (*str != '\0') {
        if ((unsigned char)*str == uc) {
            return (char *)str;
        }
        str++;
    }
    
    if (uc == '\0') {
        return (char *)str;
    }
    
    return NULL;
}
// g
int strncmp(const char *str1, const char *str2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];
        if (c1 != c2) {
            return (c1 > c2) ? 1 : -1;
        }
        if (c1 == '\0') {
            break;
        }
    }
    return 0;
}
// h
char *strncpy(char *dest, const char *src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}
// i
size_t strspn(const char *str1, const char *str2) {
    _Bool charset[256] = { 0 };
    for (const unsigned char *c = (const unsigned char *)str2; *c; c++) {
        charset[*c] = 1;
    }
    const unsigned char *start = (const unsigned char *)str1;
    const unsigned char *curr;
    for (curr = start; charset[*curr]; curr++) {};
    return curr - start;
}
// j
// char *strerror(int errnum) ---> to realize
// k
size_t strlen(const char *str) {
    if (str == NULL) return 0;
    
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
//l
char *strpbrk(const char *str1, const char *str2) {
    _Bool charset[256] = {0};
    for (const unsigned char *c = (const unsigned char *)str2; *c; c++) {
        charset[*c] = 1;
    }
    for (const unsigned char *p = (const unsigned char *)str1; *p; p++) {
        if (charset[*p]) {
            return (char *)p;
        }
    }
    return NULL;
}
//m
char *strrchr(const char *str, int c) {
    const char *last = NULL;
    unsigned char uc = (unsigned char)c;
    for (const unsigned char *p = (const unsigned char *)str; ; p++) {
        if (*p == uc) {
            last = (const char *)p;
        }
        if (*p == '\0') {
            break;
        }
    }
    return (char *)last;
}
//n
char *strstr(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;
    for ( ; *haystack; haystack++) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }
        if (!*n) return (char *)haystack;
    }
    return NULL;
}
//o
char *strtok(char *str, const char *delim) {
    static char *next_token = NULL;

    // Если передана новая строка — начинаем с неё
    if (str != NULL) {
        next_token = str;
    }

    // Если нет строки и нет сохранённой позиции — завершаем
    if (next_token == NULL || *next_token == '\0') {
        return NULL;
    }

    // Пропускаем начальные разделители
    const char *d;
    while (*next_token != '\0') {
        d = delim;
        while (*d != '\0') {
            if (*next_token == *d) {
                break;
            }
            d++;
        }
        if (*d == '\0') {
            // Текущий символ — не разделитель → начало токена
            break;
        }
        next_token++;
    }

    // Если дошли до конца строки — нет токена
    if (*next_token == '\0') {
        next_token = NULL;
        return NULL;
    }

    // Указатель на начало токена
    char *token_start = next_token;

    // Ищем конец токена (следующий разделитель или конец строки)
    while (*next_token != '\0') {
        d = delim;
        while (*d != '\0') {
            if (*next_token == *d) {
                // Найден разделитель — заменяем на '\0' и выходим
                *next_token = '\0';
                next_token++; // следующий вызов начнётся после разделителя
                return token_start;
            }
            d++;
        }
        next_token++;
    }

    // Достигли конца строки — возвращаем последний токен
    next_token = NULL;
    return token_start;
}