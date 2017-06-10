// Write a program to copy a string as a const char* and std::string into another one.

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //malloc

int main()
{
    const char *a="Alfabet";
    char *b=malloc((strlen(a)+1)*sizeof(char));

    strcpy(b,a);

    printf("%s\n",a);
    printf("%s\n",b);

    return 0;
}