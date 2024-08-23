#include <stdlib.h>
#include <stdio.h>

int main() {

    char * a = malloc(100);
    char * b = a+99;

    printf("%d",(int)(b-a));

}
