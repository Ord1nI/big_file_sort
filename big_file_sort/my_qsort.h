#ifndef MY_Q_SORT_H
#define MY_Q_SORT_H

#include <stdlib.h>
#include <string.h>

#ifndef __COMPAR_FN_T
# define __COMPAR_FN_T

typedef int (*comp) (const void *, const void *);

#endif //__COMPAR_FN_T

static void * optimal_pivit(void * a, void * b, void * c, comp cmp);
static void swap(void * a, void * b, size_t size);

static void * small_sort(void * start, void * end, size_t size, comp cmp);

static void _qsort(void* start, void* end, size_t size, comp cmp);

void my_qsort(void * ptr, size_t count, size_t size, comp cmp);



#endif // MY_Q_SORT_H
