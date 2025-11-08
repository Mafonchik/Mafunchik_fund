#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 4096
#define TARGET_WIDTH 80

// Удаляет завершающий \n, если есть
void chomp(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}

// Проверяет, состоит ли строка только из пробелов или пуста
int is_blank(const char *s) {
    while (*s) {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}

// Разбивает строку на слова и записывает указатели в массив words (макс. max_words)
// Возвращает количество слов
int split_into_words(char *line, char *words[], int max_words) {
    int count = 0;
    char *token = strtok(line, " \t");
    while (token != NULL && count < max_words) {
        words[count++] = token;
        token = strtok(NULL, " \t");
    }
    return count;
}

// Выравнивает слова по ширине до TARGET_WIDTH
void justify_line(FILE *out, char *words[], int word_count) {
    if (word_count == 0) return;
    if (word_count == 1) {
        fprintf(out, "%s\n", words[0]);
        return;
    }

    // Считаем общую длину всех слов
    int total_chars = 0;
    for (int i = 0; i < word_count; i++) {
        total_chars += strlen(words[i]);
    }

    int total_spaces = TARGET_WIDTH - total_chars;
    int gaps = word_count - 1;
    int base_spaces = total_spaces / gaps;
    int extra = total_spaces % gaps;

    for (int i = 0; i < word_count; i++) {
        fprintf(out, "%s", words[i]);
        if (i < gaps) {
            int spaces = base_spaces + (i < extra ? 1 : 0);
            for (int j = 0; j < spaces; j++)
                fputc(' ', out);
        }
    }
    fputc('\n', out);
}

void process_line(FILE *out, char *paragraph) {
    char buf[MAX_LINE];
    strcpy(buf, paragraph);

    char *words[MAX_LINE / 2]; // достаточно для слов в строке
    int word_count = split_into_words(buf, words, MAX_LINE / 2);

    if (word_count == 0) return;

    // Собираем строки по 80 символов
    int i = 0;
    while (i < word_count) {
        // Начинаем новую строку
        int current_len = 0;
        int start = i;
        // Собираем максимальное количество слов, чтобы уложиться в 80
        while (i < word_count) {
            int word_len = strlen(words[i]);
            int new_len = current_len + word_len + (current_len > 0 ? 1 : 0); // +1 для пробела
            if (new_len > TARGET_WIDTH) break;
            current_len = new_len;
            i++;
        }

        // Если это последняя строка абзаца — не выравниваем
        if (i >= word_count) {
            // Просто выводим слова через один пробел
            for (int j = start; j < i; j++) {
                if (j > start) fputc(' ', out);
                fputs(words[j], out);
            }
            fputc('\n', out);
        } else {
            // Выравниваем по ширине
            // Нужно временно сохранить слова [start, i)
            char *temp_words[MAX_LINE / 2];
            int temp_count = i - start;
            for (int j = 0; j < temp_count; j++) {
                temp_words[j] = words[start + j];
            }
            justify_line(out, temp_words, temp_count);
        }
    }
}

int main() {
    char input_path[MAX_LINE];
    char output_path[MAX_LINE];

    printf("Введите путь к входному файлу: ");
    if (!fgets(input_path, sizeof(input_path), stdin)) {
        fprintf(stderr, "Ошибка чтения входного пути.\n");
        return 1;
    }
    chomp(input_path);

    printf("Введите путь к выходному файлу: ");
    if (!fgets(output_path, sizeof(output_path), stdin)) {
        fprintf(stderr, "Ошибка чтения выходного пути.\n");
        return 1;
    }
    chomp(output_path);

    FILE *in = fopen(input_path, "r");
    if (!in) {
        perror("Не удалось открыть входной файл");
        return 1;
    }

    FILE *out = fopen(output_path, "w");
    if (!out) {
        perror("Не удалось создать выходной файл");
        fclose(in);
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), in)) {
        chomp(line);
        if (is_blank(line)) {
            // Пустая строка — сохраняем как есть
            fputc('\n', out);
        } else {
            process_line(out, line);
        }
    }

    fclose(in);
    fclose(out);
    printf("Форматирование завершено. Результат записан в '%s'.\n", output_path);
    return 0;
}