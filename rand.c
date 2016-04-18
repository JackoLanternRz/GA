#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main( int argc, char *argv[] )
{
	int a, i, swn, ctrl[20][2], ctrln;
	
	srand(time(NULL));
	

	// controller number	
	ctrln = atoi(argv[2]);
	// switch number
	swn = atoi(argv[1]);
	printf("%d,%d\n", ctrln, swn );

	for( i = 0 ; i < swn ; i++ )
	{
		// generate sw ID
		printf("%d", 5500+i );
		if( i < swn-1 )
			printf(",");
	}
	printf("\n");
	for( i = 0 ; i < swn ; i++ )
	{	
		a = 0;
		a = a + ( rand() % 10 ) * 1 ;
		a = a + ( rand() % 10 ) * 10 ;
		a = a + ( rand() % 10 ) * 100 ;
		a = a + ( rand() % 10 ) * 1000 ;
		if( (rand() % 10) <= 1 )
			a = a + 10000 ;	
		a /= 16;
		printf("%d", a);
		if( i < swn-1 )
			printf(",");
	}
	printf("\n");

	for( i = 0 ; i < swn ; i++ )
	{
		ctrl[i][0] = ( rand() % ctrln ) + 1 ;
		printf("%d", ctrl[i][0] );

		if( i < swn-1 )
			printf(",");
	}
	printf("\n");
	
	for( i = 0 ; i < swn ; i++ )
	{
		ctrl[i][1] = ( ( ctrl[i][0] + 1 ) % ctrln ) + 1 ;	
		
		printf("%d", ctrl[i][1] );

		if( i < swn-1 )
			printf(",");
	}
	printf("\n");
	return 0;
}
