#include "big_file_sort.h"


int str_cmp_by_begining(const void * a, const void * b) {
    char* arg1 = *(char **)a;
    char* arg2 = *(char **)b;
    
    size_t len1 = strlen(arg1);
    size_t len2 = strlen(arg2);

    int min_len;


    while ((isalpha(*arg1) == 0) && len1 > 1) {
        (arg1)++;
        len1--;
    }

    while ((isalpha(*arg2) == 0) && len2 > 1) {
        (arg2)++;
        len2--;
    }

    min_len = (len1 < len2) ? len1 : len2;

    for (int i = 0; i < min_len; i++) {
        if (*arg1 != *arg2) return *arg1 - *arg2;
        arg1++;
        arg2++;
    }

    return (0);
}

int str_cmp_by_end(const void * a, const void * b) {
    char* arg1 = *(char **)a;
    char* arg2 = *(char **)b;

    size_t len1 = strlen(arg1);
    size_t len2 = strlen(arg2);

    int min_len;

    arg1 += len1-1;
    arg2 += len2-1;

    while ((isalpha(*arg1) == 0) && len1 > 1) {
        (arg1)--;
        len1--;
    }

    while ((isalpha(*arg2) == 0) && len2 > 1) {
        (arg2)--;
        len2--;
    }
    min_len = (len1 < len2) ? len1 : len2;

    for (int i = 0; i < min_len; i++) {
        if (*arg1 != *arg2) return *arg1 - *arg2;
        arg1--;
        arg2--;
    }

    return (0);
}

size_t parse_to_lines(struct text_by_lines *text_by_lines, struct text * text) {
    char ** temp_text_by_lines = text_by_lines->text_by_lines;
    size_t i =0;

    *temp_text_by_lines = strtok(text->text,"\n");

    while (*temp_text_by_lines) {
        i++;
        temp_text_by_lines++;
        *temp_text_by_lines = strtok(NULL,"\n");
    }
    return i;
}

off_t file_len(char * file_name) {
    struct stat st;
    stat(file_name, &st);

    return (st.st_size);
}
//Function reads content of file and return number of lines in file
size_t read_file(struct text *text, FILE * f) {
    char * temp_text = text->text;
    size_t lines = 0;

    for(int i = 0; i < text->size; i++) {

        *temp_text = (char)fgetc(f);

        if (*temp_text == '\n')
            lines++;

        temp_text++;
    }
    return (lines);
}

//Function writes text devided by lines to file
void write_to_file(struct text_by_lines *text_by_lines, FILE* out) {
    
    char ** tmp_text_by_lines = text_by_lines->text_by_lines;

    for (size_t i = 0; i < text_by_lines->lines; i++) {
        fwrite(tmp_text_by_lines[i], 1, strlen(tmp_text_by_lines[i]), out);
        fputc('\n', out);
    }
}

