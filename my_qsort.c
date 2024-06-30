#include "my_qsort.h"


//function swap content of 2 void pointers
static void swap(void * a, void* b, size_t size) {
    if (a == b)
        return;
    void * temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

//function to find middle value from 3 void pointers and compare function
static void * optimal_pivit(void * a, void * b, void * c, comp cmp) {
    if ((cmp(a,b) >= 0 && cmp(a,c) <= 0) || (cmp(a,b) <= 0 && cmp(a,c) >= 0))
        return a;
    else if ((cmp(b,a) >= 0 && cmp(b,c) <= 0) || (cmp(b,a) <= 0 && cmp(b,c) >=0 ))
        return b;
    return c;
}

//help funciton
static void * small_sort(void * start, void * end, size_t size, comp cmp) {

    void * pivit = optimal_pivit(start,
                                 end,
                                 start + ((end-start)/size>>1)*size,
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
//main function
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
