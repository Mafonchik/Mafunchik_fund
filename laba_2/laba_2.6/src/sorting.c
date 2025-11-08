#include "../include/header.h"
#include <stdlib.h>
#include <string.h>

int compare_by_id(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    if (sa->id < sb->id) return -1;
    if (sa->id > sb->id) return 1;
    return 0;
}

int compare_by_name(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    return strcmp(sa->name, sb->name);
}

int compare_by_surname(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    return strcmp(sa->surname, sb->surname);
}

int compare_by_group(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    return strcmp(sa->group, sb->group);
}

void sort_students(Student *students, int student_count, enum sort_field field) {
    if (!students || student_count <= 0) return;

    int (*comparator)(const void *, const void *) = NULL;
    switch (field) {
        case SORT_BY_ID:       comparator = compare_by_id;       break;
        case SORT_BY_NAME:     comparator = compare_by_name;     break;
        case SORT_BY_SURNAME:  comparator = compare_by_surname;  break;
        case SORT_BY_GROUP:    comparator = compare_by_group;    break;
        default: return;
    }
    qsort(students, (size_t)student_count, sizeof(Student), comparator);
}