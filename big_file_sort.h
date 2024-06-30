#ifndef BIG_FILE_SORT_H
#define BIG_FILE_SORT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>
#include "my_qsort.h"


struct text {
    char * text;
    off_t size;
};


struct text_by_lines {
    char ** text_by_lines;
    size_t lines;
};


void write_to_file(struct text_by_lines *text_by_lines, FILE* out);

off_t file_len(char * file_name);

size_t read_file(struct text *text, FILE * f);
size_t parse_to_lines(struct text_by_lines * text_by_lines, struct text * text);

int str_cmp_by_end(const void * a, const void * b);

int str_cmp_by_begining(const void * a, const void * b);

void qsort(void * ptr, size_t count, size_t size, int (*comp)(const void*, const void*));

#endif // BIG_FILE_SORT_H
