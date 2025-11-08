#pragma once

#include <stddef.h>

#define NAME_SIZE 100
#define SURNAME_SIZE 100
#define GROUPNAME_SIZE 100
#define GRADES_COUNT 5

typedef struct Student {
    unsigned int id;
    char name[NAME_SIZE];
    char surname[SURNAME_SIZE];
    char group[GROUPNAME_SIZE];
    unsigned char *grades;
} Student;

enum errors {
    SUCCESS,
    FAILED_TO_OPEN_FILE,
    FAILED_TO_ALLOCATE_MEMORY,
    FAILED_TO_FIND_STUDENT,
    INCORRECT_BASE,
};
// main
void print_menu(void);
void handle_find_by_id(Student *students, int student_count);
void handle_find_by_name(Student *students, int student_count);
void handle_find_by_surname(Student *students, int student_count);
void handle_find_by_group(Student *students, int student_count);
void handle_sort_students(Student *students, int student_count);
void handle_log_by_id(Student *students, int student_count, const char *log_file);
void handle_log_above_average(Student *students, int student_count, const char *log_file);
void print_all_students(Student *students, int student_count);

// Загрузка и освобождение
enum errors add_students(const char *file_name, int *student_count, Student **students);
enum errors free_students(Student *students, int student_count);

// Поиск (возвращают индекс или -1 для ID; SUCCESS/ошибки для остальных)
int find_student_by_id(Student *students, int student_count, int id);
int find_student_by_name(Student *students, int student_count, char *name, int *buf);
int find_student_by_surname(Student *students, int student_count, char *surname, int *buf);
int find_student_by_group(Student *students, int student_count, char *group, int *buf);

// Сортировка
enum sort_field {
    SORT_BY_ID,
    SORT_BY_NAME,
    SORT_BY_SURNAME,
    SORT_BY_GROUP
};

int compare_by_id(const void *a, const void *b);
int compare_by_name(const void *a, const void *b);
int compare_by_surname(const void *a, const void *b);
int compare_by_group(const void *a, const void *b);

void sort_students(Student *students, int student_count, enum sort_field field);

// Работа с оценками
float calculate_average_grade(Student *student);
float calculate_global_average(Student *students, int student_count);

// Логирование
enum errors log_student_by_id(Student *students, int student_count, int id, const char *log_file);
enum errors log_students_above_average(Student *students, int student_count, const char *log_file);