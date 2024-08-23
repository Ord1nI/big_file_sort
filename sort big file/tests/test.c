#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>

/* void sort(char ** text_by_lines, sizt_t lines, int dir) { */

/*     for(size_t i = 0; i < lines; i++) { */
/*         for(size_t q = i+1; q < lines; q++) { */
/*             if(strcmp(text_by_lines[i], text_by_lines[q])*dir > 0) { */
/*                 char * tmp = text_by_lines[i]; */
/*                 text_by_lines[i] = text_by_lines[q]; */
/*                 text_by_lines[q] = tmp; */
/*             } */
/*         } */
/*     } */

/* } */

int str_cmp_by_begining(const void * a, const void * b) {
    char* arg1 = *(char **)a;
    char* arg2 = *(char **)b;

    while ((isalpha(*arg1) == 0) && *arg1 != '\0')
        (arg1)++;

    while ((isalpha(*arg2) == 0) && *arg2 != '\0')
        (arg2)++;

    return (strcmp(arg1,arg2));
}

int str_cmp_by_end(const void * a, const void * b) {
    char* arg1 = *(char **)a;
    char* arg2 = *(char **)b;

    size_t len1 = strlen(arg1);
    size_t len2 = strlen(arg2);

    int min_len = (len1 < len2) ? len1 : len2;

    arg1 += len1-1;
    arg2 += len2-1;

    while ((isalpha(*arg1) == 0) && *arg1 != '\0')
        (arg1)--;

    while ((isalpha(*arg2) == 0) && *arg2 != '\0')
        (arg2)--;

    for (int i = 0; i < min_len; i++) {
        if (*arg1 != *arg2) return *arg1 - *arg2;
        arg1--;
        arg2--;
    }

    return (0);
}

size_t parse_to_lines(char *** text_by_lines, char * text, off_t size) {
    char ** temp_text_by_lines = *text_by_lines;
    size_t lines = 0;

    *temp_text_by_lines = strtok(text,"\n");

    while (*temp_text_by_lines) {
        temp_text_by_lines++;
        lines++;
        *temp_text_by_lines = strtok(NULL,"\n");
    }
    
    return (lines);
}

off_t file_len(char * file_name) {
    struct stat st;
    stat(file_name, &st);

    return (st.st_size);
}

void write_to_file(char *** text_by_lines, size_t lines, FILE* out) {
    char ** tmp_text_by_lines = *text_by_lines;
    for (size_t i = 0; i < lines; i++) {
        fwrite(tmp_text_by_lines[i], 1, strlen(tmp_text_by_lines[i]), out);
        fputc('\n', out);
    }
}



int main() {

    //Read from file

    FILE * f = fopen("hamlet.txt", "r");
    
    char ** text_by_lines = malloc(sizeof(char*)*5000);

    off_t text_size = file_len("hamlet.txt");
    
    char * text = malloc(text_size);
    fread(text, 1, text_size, f);

    fclose(f);

    //Parse text to array of lines and
    //Delete empty lines
    //Delete spaces in the begining of the line
    //Get lines in modify text
    size_t lines = parse_to_lines(&text_by_lines, text, text_size);
    printf("%d",lines);

    //Sort by begining
    qsort(text_by_lines, lines, sizeof(char*), str_cmp_by_begining);

    //Write to output file
    FILE * out = fopen("Out.txt","w");
    write_to_file(&text_by_lines, lines, out);


    //Sort by end
    qsort(text_by_lines, lines, sizeof(char*), str_cmp_by_end);

    write_to_file(&text_by_lines, lines, out);

    fclose(out);
    free(text_by_lines);
    free(text);
}
