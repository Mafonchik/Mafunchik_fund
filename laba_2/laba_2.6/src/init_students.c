#include "../include/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum errors add_students(const char *file_name, int *student_count, Student **students) {
    FILE *fptr = fopen(file_name, "r");
    if (!fptr) {
        return FAILED_TO_OPEN_FILE;
    }

    char buffer[1024];
    int st_cnt = 0;

    while (fgets(buffer, sizeof(buffer), fptr)) {
        st_cnt++;
    }

    rewind(fptr);

    *students = (Student *)malloc(st_cnt * sizeof(Student));
    if (!*students) {
        fclose(fptr);
        return FAILED_TO_ALLOCATE_MEMORY;
    }

    int st_read = 0;
    while (st_read < st_cnt && fgets(buffer, sizeof(buffer), fptr)) {
        buffer[strcspn(buffer, "\n")] = 0;
        char *token = strtok(buffer, " ");
        if (token) {
            (*students)[st_read].id = (unsigned int)atoi(token);

            token = strtok(NULL, " ");
            if (token) {
                strncpy((*students)[st_read].name, token, NAME_SIZE - 1);
                (*students)[st_read].name[NAME_SIZE - 1] = '\0';
            } else {
                (*students)[st_read].name[0] = '\0';
            }

            token = strtok(NULL, " ");
            if (token) {
                strncpy((*students)[st_read].surname, token, SURNAME_SIZE - 1);
                (*students)[st_read].surname[SURNAME_SIZE - 1] = '\0';
            } else {
                (*students)[st_read].surname[0] = '\0';
            }

            token = strtok(NULL, " ");
            if (token) {
                strncpy((*students)[st_read].group, token, GROUPNAME_SIZE - 1);
                (*students)[st_read].group[GROUPNAME_SIZE - 1] = '\0';
            } else {
                (*students)[st_read].group[0] = '\0';
            }

            (*students)[st_read].grades = (unsigned char *)malloc(GRADES_COUNT * sizeof(unsigned char));
            if ((*students)[st_read].grades) {
                for (int i = 0; i < GRADES_COUNT; i++) {
                    token = strtok(NULL, " ");
                    if (token) {
                        (*students)[st_read].grades[i] = (unsigned char)atoi(token);
                    } else {
                        (*students)[st_read].grades[i] = 0;
                    }
                }
            } else {
                // Если не удалось выделить память под оценки — обнуляем
                for (int i = 0; i < GRADES_COUNT; i++) {
                    (*students)[st_read].grades[i] = 0;
                }
            }
        }
        st_read++;
    }

    *student_count = st_read;
    fclose(fptr);
    return SUCCESS;
}

enum errors free_students(Student *students, int student_count) {
    if (!students) return SUCCESS;
    for (int i = 0; i < student_count; i++) {
        free(students[i].grades);
    }
    free(students);
    return SUCCESS;
}