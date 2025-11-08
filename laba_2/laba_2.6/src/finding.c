#include "../include/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_student_by_id(Student *students, int student_count, int id) {
    if (!students || student_count <= 0)
        return -1;
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == (unsigned int)id) {
            return i;
        }
    }
    return -1;
}

int find_student_by_name(Student *students, int student_count, char *name, int *buf) {
    if (!students || student_count <= 0 || !buf) {
        return INCORRECT_BASE;
    }

    int buf_size = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            buf[buf_size] = i;
            buf_size++;
        }
    }

    if (buf_size == 0) {
        return FAILED_TO_FIND_STUDENT;
    }

    return SUCCESS;
}

int find_student_by_surname(Student *students, int student_count, char *surname, int *buf) {
    if (!students || student_count <= 0 || !buf) {
        return INCORRECT_BASE;
    }

    int buf_size = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].surname, surname) == 0) {
            buf[buf_size] = i;
            buf_size++;
        }
    }

    if (buf_size == 0) {
        return FAILED_TO_FIND_STUDENT;
    }

    return SUCCESS;
}

int find_student_by_group(Student *students, int student_count, char *group, int *buf) {
    if (!students || student_count <= 0 || !buf) {
        return INCORRECT_BASE;
    }

    int buf_size = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].group, group) == 0) {
            buf[buf_size] = i;
            buf_size++;
        }
    }

    if (buf_size == 0) {
        return FAILED_TO_FIND_STUDENT;
    }

    return SUCCESS;
}