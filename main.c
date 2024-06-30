#include "big_file_sort.h"

int main() {

    //Read from file

    struct text text;
    struct text_by_lines text_by_lines;

    FILE * f = fopen("hamlet.txt", "r");

    text.size = file_len("hamlet.txt");

    text.text = malloc(text.size);
    printf("%s",text.text);

    text_by_lines.lines = read_file(&text, f);
    text_by_lines.text_by_lines = (char**)malloc(sizeof(char *) * text_by_lines.lines);

    fclose(f);

    //Parse text to array of lines and
    //Delete empty lines
    //Delete spaces in the begining of the line
    //Get lines in modify text
    text_by_lines.lines = parse_to_lines(&text_by_lines, &text);

    //Sort by begining
    qsort(text_by_lines.text_by_lines, text_by_lines.lines, sizeof(char*), str_cmp_by_begining);

    //Write to output file
    FILE * out = fopen("Out.txt","w");
    write_to_file(&text_by_lines, out);


    //Sort by end
    qsort(text_by_lines.text_by_lines, text_by_lines.lines, sizeof(char*), str_cmp_by_end);

    write_to_file(&text_by_lines, out);

    fclose(out);
    free(text_by_lines.text_by_lines);
    free(text.text);
}
