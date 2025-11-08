#include "../include/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <log_file>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *log_file = argv[2];

    Student *students = NULL;
    int student_count = 0;

    enum errors err = add_students(input_file, &student_count, &students);
    if (err != SUCCESS) {
        fprintf(stderr, "Error loading students: %d\n", err);
        return 1;
    }

    // Очистка лог-файла
    fclose(fopen(log_file, "w"));

    int choice;
    char buffer[100];

    while (1) {
        print_menu();
        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        choice = atoi(buffer);

        if (choice == 0) break;

        switch (choice) {
            case 1: handle_find_by_id(students, student_count); break;
            case 2: handle_find_by_name(students, student_count); break;
            case 3: handle_find_by_surname(students, student_count); break;
            case 4: handle_find_by_group(students, student_count); break;
            case 5: handle_sort_students(students, student_count); break;
            case 6: handle_log_by_id(students, student_count, log_file); break;
            case 7: handle_log_above_average(students, student_count, log_file); break;
            default: printf("Invalid command.\n");
        }
    }

    free_students(students, student_count);
    printf("Goodbye!\n");
    return 0;
}

void print_menu(void) {
    printf("\n=== Student Management ===\n");
    printf("1. Find student by ID\n");
    printf("2. Find students by name\n");
    printf("3. Find students by surname\n");
    printf("4. Find students by group\n");
    printf("5. Sort students\n");
    printf("6. Log student by ID to trace file\n");
    printf("7. Log students above average to trace file\n");
    printf("0. Exit\n");
    printf("Enter command: ");
}

void handle_find_by_id(Student *students, int student_count) {
    int id;
    printf("Enter student ID: ");
    scanf("%d", &id);
    getchar(); // consume newline

    int idx = find_student_by_id(students, student_count, id);
    if (idx == -1) {
        printf("Student not found.\n");
    } else {
        Student *s = &students[idx];
        printf("Found: %s %s (ID: %u, Group: %s)\n",
               s->name, s->surname, s->id, s->group);
    }
}

void handle_find_by_name(Student *students, int student_count) {
    char name[100];
    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    int *buf = calloc(student_count, sizeof(int));
    if (!buf) {
        printf("Memory error\n");
        return;
    }

    int res = find_student_by_name(students, student_count, name, buf);
    if (res == SUCCESS) {
        printf("Found students:\n");
        for (int i = 0; i < student_count && buf[i] != 0; i++) {
            Student *s = &students[buf[i]];
            printf("- %s %s (ID: %u)\n", s->name, s->surname, s->id);
        }
    } else {
        printf("No students found with name '%s'\n", name);
    }
    free(buf);
}

void handle_find_by_surname(Student *students, int student_count) {
    char surname[100];
    printf("Enter surname: ");
    fgets(surname, sizeof(surname), stdin);
    surname[strcspn(surname, "\n")] = 0;

    int *buf = calloc(student_count, sizeof(int));
    if (!buf) {
        printf("Memory error\n");
        return;
    }

    int res = find_student_by_surname(students, student_count, surname, buf);
    if (res == SUCCESS) {
        printf("Found students:\n");
        for (int i = 0; i < student_count && buf[i] != 0; i++) {
            Student *s = &students[buf[i]];
            printf("- %s %s (ID: %u)\n", s->name, s->surname, s->id);
        }
    } else {
        printf("No students found with surname '%s'\n", surname);
    }
    free(buf);
}

void handle_find_by_group(Student *students, int student_count) {
    char group[100];
    printf("Enter group: ");
    fgets(group, sizeof(group), stdin);
    group[strcspn(group, "\n")] = 0;

    int *buf = calloc(student_count, sizeof(int));
    if (!buf) {
        printf("Memory error\n");
        return;
    }

    int res = find_student_by_group(students, student_count, group, buf);
    if (res == SUCCESS) {
        printf("Found students:\n");
        for (int i = 0; i < student_count && buf[i] != 0; i++) {
            Student *s = &students[buf[i]];
            printf("- %s %s (ID: %u)\n", s->name, s->surname, s->id);
        }
    } else {
        printf("No students found in group '%s'\n", group);
    }
    free(buf);
}

void handle_sort_students(Student *students, int student_count) {
    printf("Sort by:\n1. ID\n2. Name\n3. Surname\n4. Group\n");
    int sort_opt;
    scanf("%d", &sort_opt);
    getchar();

    enum sort_field field;
    switch (sort_opt) {
        case 1: field = SORT_BY_ID; break;
        case 2: field = SORT_BY_NAME; break;
        case 3: field = SORT_BY_SURNAME; break;
        case 4: field = SORT_BY_GROUP; break;
        default:
            printf("Invalid option\n");
            return;
    }

    sort_students(students, student_count, field);
    printf("Students sorted. Current list:\n");
    print_all_students(students, student_count);
}

void print_all_students(Student *students, int student_count) {
    for (int i = 0; i < student_count; i++) {
        printf("%d. ID: %u | Name: %s %s | Group: %s\n",
               i + 1,
               students[i].id,
               students[i].name,
               students[i].surname,
               students[i].group);
    }
}

void handle_log_by_id(Student *students, int student_count, const char *log_file) {
    int id;
    printf("Enter ID to log: ");
    scanf("%d", &id);
    getchar();

    enum errors err = log_student_by_id(students, student_count, id, log_file);
    if (err == SUCCESS) {
        printf("Student logged to %s\n", log_file);
    } else {
        printf("Failed to log student (error %d)\n", err);
    }
}

void handle_log_above_average(Student *students, int student_count, const char *log_file) {
    enum errors err = log_students_above_average(students, student_count, log_file);
    if (err == SUCCESS) {
        printf("Above-average students logged to %s\n", log_file);
    } else {
        printf("Failed to log (error %d)\n", err);
    }
}