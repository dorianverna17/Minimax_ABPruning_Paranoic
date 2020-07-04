#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cerinta1.h"
#include "cerinta2.h"
#include "cerinta3.h"
#include "bonus.h"

int main(int argc, char *argv[])
{
	FILE *file_in, *file_out;

	file_in = fopen(argv[2], "r");
	file_out = fopen(argv[3], "w");
	if (strcmp(argv[1], "-c1") == 0)
		cerinta1(file_in, file_out);
	else if (strcmp(argv[1], "-c2") == 0)
		cerinta2(file_in, file_out);
	else if (strcmp(argv[1], "-c3") == 0)
		cerinta3(file_in, file_out);
	else if (strcmp(argv[1], "-b") == 0)
		bonus(file_in, file_out);
	fclose(file_in);
	fclose(file_out);
	return 0;
}
