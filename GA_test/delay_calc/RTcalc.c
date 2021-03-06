#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
	int i, j, loading[1500][3];
	float RT[150], algrt[1500][3], algavgrt[1500];
	char input[100], *str_rt, *str_ld;
	
	FILE *rtfp = fopen("RT.csv", "r");
	i = 0;
	while( EOF != fscanf(rtfp, "%s", input ) )
	{
		input[strlen(input)] = '\0';
		str_rt = strtok( input, "," );
		RT[i] = atof(str_rt); 	 //printf("%f ", RT[i] );
		i++;
	}
	fclose(rtfp);

	FILE *ldfp = fopen(argv[1], "r");
	i=0;
	j=0;
	while( EOF != fscanf(ldfp, "%s", input) )
	{
		input[strlen(input)] = '\0';
		str_ld = strtok( input, "," );
		loading[i][j] = atoi(str_ld);
		j++;
		str_ld = strtok( NULL, "," );
		loading[i][j] = atoi(str_ld);
		j++;
		str_ld = strtok( NULL, "," );
		loading[i][j] = atoi(str_ld);
		j=0;	//printf("%d %d %d\t", loading[i][0], loading[i][1], loading[i][2] );
		i++;	
	}
	fclose(ldfp);

	//FILE *wldfp = fopen( argv[2], "w" );
	for( i = 0 ; i < 1500 ; i++ )
	{
		for( j = 0 ; j < 3 ; j++ )
		{	
			if( loading[i][j] > 100 )
				loading[i][j] = 100;
			algrt[i][j] =  RT[loading[i][j]]; 
			//fprintf(wldfp, "%f,", RT[loading[i][j]] );	
		}
		//fprintf(wldfp, "\n");
	}
	//fclose(wldfp);
	
	FILE *wldfp = fopen( argv[2], "w" );
	float sum = 0;
	for( i = 0 ; i < 1500 ; i++ )
	{
		sum = 0;
		for( j = 0 ; j < 3 ; j++ )
		{
			sum = sum + algrt[i][j];
		}
		algavgrt[i] = (float)sum/3; 
		fprintf(wldfp, "%f\n", algavgrt[i]);
	}
	fclose(wldfp);


	return 0;
}
