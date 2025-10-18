// удалить дупликаты из массива
/*
#include <stdlib.h>
#include <stdio.h>

int* dupl(int* arr, int size, int newSize) {
    int cnt = 0;
    _Bool flag = 0;
    if (!arr || size <= 0 || !newSize) {
        return NULL;
    }
    int* new_arr = (int *)malloc(sizeof(int) * size);
    if (!new_arr) {
        return NULL;
    }
    for (size_t i = 0; i < size; ++i) {
        flag = 0;
        for (size_t j = 0; j < cnt; ++j) {
            if (arr[i] == new_arr[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            new_arr[cnt++] = arr[i];
        }
    }
    int* result = realloc(new_arr, cnt * sizeof(int));
    if (!result) {
        newSize = cnt;
        return new_arr;
    }
    newSize = cnt;
    return result;
}



void printarr(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
}

void test() {
    int arr[7] = {0, 2, 5, 6, 5, 2, 9};
    int newsz = 0;
    int* result = dupl(arr, 7, newsz); 
    printarr(result, newsz);
}

int main() {
    test();
    return 0;
}
*/

