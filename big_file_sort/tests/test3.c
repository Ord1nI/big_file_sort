#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef int (*comp) (const void *, const void *);

static void swap(void * a, void* b, size_t size) {
    if (a == b)
        return;
    void * temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

int cmp(const void* a,const void* b) {
    int t_a = *(int *)a;
    int t_b = *(int *)b;
    return t_a - t_b;
}

static void * optimal_pivit(void * a, void * b, void * c, comp cmp) {
    if ((cmp(a,b) >= 0 && cmp(a,c) <= 0) || (cmp(a,b) <= 0 && cmp(a,c) >= 0))
        return a;
    else if ((cmp(b,a) >= 0 && cmp(b,c) <= 0) || (cmp(b,a) <= 0 && cmp(b,c) >=0 ))
        return b;
    return c;
}


static void * small_sort(void * start, void * end, size_t size, comp cmp) {

    void * pivit = optimal_pivit(start,
                                 end,
                                 start + ((end-start)/size/2)*size,
                                 cmp);


    swap(pivit, end, size);
    pivit = end;
    end-=size;

    while(start < end) {

        while(cmp(start, pivit) <= 0 && start < end)
            start+=size;

        while(cmp(end, pivit) > 0 && start < end)
            end-=size;

        swap(start,end,size);
    }

    swap(start,pivit,size);
    return(start);
}

static void _qsort(void* start, void* end, size_t size, comp cmp) {
    if (start < end) {
        void * part = small_sort(start, end, size, cmp);

        _qsort(start, part-size, size, cmp);
        _qsort(part+size, end, size, cmp);
    }
}
void my_qsort(void * ptr, size_t count, size_t size, comp cmp) {
    _qsort(ptr, ptr + ((count-1) * size), size, cmp);
}

int main() {

    int a[] = {1,345,1065,24897,2,597,18,508,1659,3};
    void* pa = a;

    my_qsort(a, 10, sizeof(int), cmp);
    for (int i = 0; i < 10; i++){
        printf("%d\n",a[i]);
    }
}
