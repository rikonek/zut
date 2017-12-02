#include <stdio.h>
#include <string.h>

void print(int *array,int length)
{
    for(int i=0;i<length;i++)
    {
        printf("%d:",array[i]);
    }
    printf("\n");
}

int main()
{
    int a[10]={0,1,2,3,4,5,6,7,8,9};
    int b[10]={9,8,7,6,5,4,3,2,1,0};
    int as=sizeof(a)/sizeof(a[0]);
    int bs=sizeof(b)/sizeof(b[0]);
    int cs=as+bs;
    int c[cs];
    memset(c,0,sizeof(c));

    memcpy(&c,&a,sizeof(a));
    memcpy(&c[as],&b,sizeof(b));

    print(a,as);
    print(b,bs);
    print(c,cs);

    return 0;
}