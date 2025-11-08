#include "../include/header.h"
#include <stdio.h>

float calculate_average_grade(Student *student) {
    if (!student || !student->grades) return 0.0f;
    int sum = 0;
    for (int i = 0; i < GRADES_COUNT; i++) {
        sum += student->grades[i];
    }
    return (float)sum / GRADES_COUNT;
}

float calculate_global_average(Student *students, int student_count) {
    if (!students || student_count <= 0) return 0.0f;
    float total = 0.0f;
    for (int i = 0; i < student_count; i++) {
        total += calculate_average_grade(&students[i]);
    }
    return total / student_count;
}

enum errors log_student_by_id(Student *students, int student_count, int id, const char *log_file) {
    int idx = find_student_by_id(students, student_count, id);
    if (idx == -1) return FAILED_TO_FIND_STUDENT;

    FILE *log = fopen(log_file, "a");
    if (!log) return FAILED_TO_OPEN_FILE;

    Student *s = &students[idx];
    float avg = calculate_average_grade(s);
    fprintf(log, "Student ID %u: %s %s, Group: %s, Average: %.2f\n",
            s->id, s->name, s->surname, s->group, avg);
    fclose(log);
    return SUCCESS;
}

enum errors log_students_above_average(Student *students, int student_count, const char *log_file) {
    float global_avg = calculate_global_average(students, student_count);
    FILE *log = fopen(log_file, "a");
    if (!log) return FAILED_TO_OPEN_FILE;

    fprintf(log, "\nStudents with average grade above %.2f:\n", global_avg);
    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (calculate_average_grade(&students[i]) > global_avg) {
            fprintf(log, "%s %s\n", students[i].surname, students[i].name);
            found = 1;
        }
    }
    if (!found) {
        fprintf(log, "(none)\n");
    }
    fclose(log);
    return SUCCESS;
}