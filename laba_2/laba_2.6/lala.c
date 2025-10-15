#include <stdio.h>
#include <string.h>

struct Student {
    unsigned int id;
    char name[30];
    char surname[30];
    char group[30];
    char* grades;
} Student;

int main() {
    
    char file_name[100];
    scanf("%s", file_name);
    FILE* file;
    file = fopen(file_name, "r");

    fclose(file);
    return 0; 
}