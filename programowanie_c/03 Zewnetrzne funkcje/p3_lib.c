#include <stdio.h>
#include "p3_lib.h"

int moja_funkcja(int argc, char *argv[])
{
	for(int i=0;i<argc;i++)
	{
		puts(argv[i]);
	}
	return 0;
}

