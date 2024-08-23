#include <stdio.h>
#include <stdlib.h>
#include "my_qsort.h"
#include <time.h>

int cmp(const void* a,const void* b) {
    int t_a = *(int *)a;
    int t_b = *(int *)b;
    return t_a - t_b;
}

int main() {

    const int size = 10000000;
    int * array = malloc(size*sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
            array[i] = rand();
    }



    my_qsort(array, size, sizeof(array[0]), cmp);
    /* for (int i = 0; i < size; i++) { */
    /*         printf("%d\n", array[i]); */
    /* } */
}
