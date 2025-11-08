#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    int og_num = 0;
    int r = 0;
    get_info(&og_num, &r);
    if (r > 5 || r < 1) {
        printf("Ошибка: r вне диапазона\n");
        return INVALID_ARGUMENT;
    }
    char* result = conversion(og_num, r);
    if (!result) {
        return FAILED_TO_ALLOCATE_MEMORY;
    }
    
    printf("Итог: %s\n", result);
    free(result);
    return SUCCESS;
}