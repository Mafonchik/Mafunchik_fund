#ifndef HEADER
#define HEADER
#define INIT_CAP 256

enum errors {
    SUCCESS,
    INVALID_ARGUMENT,
    FAILED_TO_ALLOCATE_MEMORY,
};

void get_info(int *num, int *r);
void reverse_string(char* num, int size);
void increase_memory(char** num, int new_size);
int sign(int n);
char* conversion(int og_num, int r);

#endif