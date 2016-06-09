#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#include<math.h>
#include <sys/time.h>
int dfa( int sw_paknum[][4], int ctrln, int swn, int org )
{
	int i, *c_cost, sum=0, avg=0, D=0;
	c_cost =  malloc( sizeof(int)*(ctrln+1) );	
	for( i = 0 ; i < swn ; i++ )
	{
		c_cost[ sw_paknum[i][2] ] = c_cost[ sw_paknum[i][2] ] + sw_paknum[i][1];
		c_cost[ sw_paknum[i][3] ] = c_cost[ sw_paknum[i][3] ] + sw_paknum[i][1];	
	}	
	for( i = 1 ; i <= ctrln ; i++ )
	{
		sum = sum + c_cost[i];
	}
	//printf( "sum = %d\n", sum );
	avg = (int)(sum/ctrln);	
	/*if( org == 1 )	
		printf( "avg = %d\n", avg );*/

	for( i = 1 ; i <= ctrln ; i++ )
	{	
		// controller index starts from 1
		/*if( org == 1 )
			printf("c[%d]=%d ", i, c_cost[i] );*/
		D = D + abs(c_cost[i] - avg);
	}
	/*if( org == 1 )
		printf("\n");*/
	return D;
}

float lbm( int sw_paknum[][4], int ctrln, int swn )
{
	int i, *c_cost, sum=0, max_c_cost=0;
	float LBM=0;
	c_cost =  malloc( sizeof(int)*(ctrln+1) );	
	for( i = 0 ; i < swn ; i++ )
	{
		c_cost[ sw_paknum[i][2] ] = c_cost[ sw_paknum[i][2] ] + sw_paknum[i][1];
		c_cost[ sw_paknum[i][3] ] = c_cost[ sw_paknum[i][3] ] + sw_paknum[i][1];	
	}	
	for( i = 1 ; i <= ctrln ; i++ )
	{
		sum = sum + c_cost[i];
		if( c_cost[i] >= max_c_cost )
			max_c_cost = c_cost[i];
	}

	LBM = max_c_cost / (float)(sum/ctrln) ;
	

	/*if( org == 1 )
		printf("\n");*/
	return LBM;
}

int rand_a_c(int ctrln, int had_c)
{
	int n;
	//printf("had_c=%d ", had_c);
	while(1)
	{
		if( ( n = ((rand()%ctrln)+1) ) != had_c )
		{
			//printf("n=%d\n", n);
			return n;
		}
	}
}

int main(int argc, char *argv[] )
{
	// dif dimansion(D) D1 == switch number, D2-1 == switch ID, D2-2 == switch packet,
	//  D2-3up == linked controller index 
	int sw_paknum[20][4];
	char input[1000], *str_sw_pkn, *str_ctrln, *str_swn;
	int i, j, k, l, ctrln, swn, D, Dold, f;
	float Df;
	ctrln = 0;
	swn = 0;
	D = 0;
	FILE *wfp = fopen( argv[2], "w");
	FILE *pak_fp = fopen( argv[3], "w" );

	// get file data
	//fscanf(fp, "%s", input );	//printf("%s\n", input );
	//str_ctrln = strtok( input, "," ) ;
	//ctrln = atoi( str_ctrln );
	//str_swn = strtok( NULL, "," ) ;
	//swn = atoi( str_swn );		//printf( "c=%d s=%d\n", ctrln, swn );
	ctrln = 3;
	swn = 20;


	//struct timeval t1, t2;
   	//double timecost;
	// start timer
    	//gettimeofday(&t1, NULL);
	for( f = 0 ; f < atoi(argv[1]) ; f++  )
	{	
		char file[100];
		sprintf(file, "%d.txt", f );
		//printf("%s ", file );
		FILE *fp = fopen( file, "r" );
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
		//Dold = dfa( sw_paknum, ctrln, swn, 1 );
		for( i = 0 ; i < swn ; i++ )
		{
			sw_paknum[i][2] = (i%3) + 1 ;
			sw_paknum[i][3] = ((sw_paknum[i][3] + 1) % 3 )+ 1;
		}
		/*for( i = 0 ; i < swn ; i++ )
			printf("%d ", sw_paknum[i][3] );	
		printf("\n");
		for( i = 0 ; i < swn ; i++ )
			printf("%d ", sw_paknum[i][4] );	
		printf("\n");*/
		//D = dfa( sw_paknum, ctrln, swn, 0 );
		//Df = ( (float)(Dold - D) / Dold ) + 0.12;
		float LBM=0;
		int *c_cost = malloc( sizeof(int)*(ctrln+1) );
		
		LBM = lbm( sw_paknum, ctrln, swn );

		for( i = 0 ; i < swn ; i++ )
		{
			c_cost[ sw_paknum[i][2] ] = c_cost[ sw_paknum[i][2] ] + sw_paknum[i][1];
			c_cost[ sw_paknum[i][3] ] = c_cost[ sw_paknum[i][3] ] + sw_paknum[i][1];	
		}
		
		fprintf( wfp, "%f,\n", LBM );

		for( i = 1 ; i < (ctrln+1) ; i++ )
		{
			fprintf( pak_fp, "%d,", c_cost[i] );
		}
		fprintf( pak_fp, "\n" );
		

		fclose(fp);
	}
	fclose(wfp);
	fclose(pak_fp);
	

	// stop timer
    	//gettimeofday(&t2, NULL);
	//timecost = timecost += (t2.tv_usec - t1.tv_usec) / 5000;
	//printf("Code time cost: %f\n", timecost);

	return 0;
}





