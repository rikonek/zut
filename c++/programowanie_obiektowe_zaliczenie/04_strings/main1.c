// Write a program to revert a string (const char*, std::string)

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //malloc

int main()
{
    const char *a="Alfabet";
    char *b=malloc((strlen(a)+1)*sizeof(char));

    for(int i=0;i<strlen(a);i++)
    {
        b[i]=a[strlen(a)-1-i];
    }

    printf("%s\n",a);
    printf("%s\n",b);

    return 0;
}