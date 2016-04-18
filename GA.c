#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
int dfa( int sw_paknum[][4], int ctrln, int swn )
{
	int i, *c_cost, sum=0, avg=0, D=0;
	c_cost =  malloc( sizeof(int)*ctrln );	
	for( i = 0 ; i < swn ; i++ )
	{
		c_cost[ sw_paknum[i][2] ] = c_cost[ sw_paknum[i][2] ] + sw_paknum[i][1];
		c_cost[ sw_paknum[i][3] ] = c_cost[ sw_paknum[i][3] ] + sw_paknum[i][1];	
	}	
	for( i = 0 ; i < ctrln ; i++ )
	{
		sum = sum + c_cost[i];
	}
	printf( "sum = %d\n", sum );
	avg = (int)(sum/ctrln);
	printf( "avg = %d\n", avg );

	for( i = 0 ; i < ctrln ; i++ )
	{	
		printf("%d ", c_cost[i+1] );
		// controller index starts from 1
		D = D + c_cost[i+1] - avg;
	}
	printf("\n");
	return D;
}

int main(int argc, char *argv[] )
{
	// dif dimansion(D) D1 == switch number, D2-1 == switch ID, D2-2 == switch packet,
	//  D2-3up == linked controller index 
	int sw_paknum[30][4];
	char input[1000], *str_sw_pkn, *str_ctrln, *str_swn;
	int i, j, ctrln, swn, Dold;
	
	ctrln = 0;
	swn = 0;
	Dold = 0;
	FILE *fp = fopen( argv[1], "r");

	// get file data
	fscanf(fp, "%s", input );	//printf("%s\n", input );
	str_ctrln = strtok( input, "," ) ;
	ctrln = atoi( str_ctrln );
	str_swn = strtok( NULL, "," ) ;
	swn = atoi( str_swn );		//printf( "c=%d s=%d\n", ctrln, swn );
	i = 0;
	while( EOF !=  fscanf(fp, "%s", input ) )
	{
		input[strlen(input)] = '\0';	//printf("%s\n", input);
		j = 0;
		str_sw_pkn = strtok(input, ",");
		while( str_sw_pkn != NULL )
		{
			sw_paknum[j][i]	= atoi( str_sw_pkn );	//printf("%d ", sw_paknum[j][i] );
			j++;
			str_sw_pkn = strtok(  NULL , "," );
		}	
		
		i++;
	}
	// end of get file data

	//for( j = 0 ; j < 4 ; j++ )
	//{	
		for( i = 0 ; i < swn ; i++ )
		{
			printf("%d ", sw_paknum[i][1] );	
		}
		printf("\n");
	//}
	
	Dold = dfa( sw_paknum, ctrln, swn );
	printf( "%d\n", Dold );
	return 0;
}
