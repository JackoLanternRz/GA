#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i=0;
	char input[100], *num_str; 
	FILE *fp = fopen(argv[1], "r");
	while( EOF !=  fscanf(fp, "%s", input ) )
	{
		input[strlen(input)] = '\0';
		num_str = strtok(input, ",");
		//printf("(%s,%f) ", num_str, atof(num_str) );

		if ( atof(num_str) > 0 )
			i++;
	}
	printf("%d\n", i);
	return 0;
}
