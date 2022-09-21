#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

#define MSG "* running cpubench with seed %s mode %s using %s with size %s and %s threads with debug %s...\n"

#define USAGE "usage: ./cpubench <seed> <mode> <type> <size> <threads> <debug> \n" \
"     - seed: 0 \n" \
"     - mode: flops / matrix \n" \
"     - type: single / double \n" \
"     - size: 256 / 1024 / 4096 / 16386 -- MegaFlops / array dimension \n" \
"     - threads: 1 / 2 / 4 \n" \
"     - debug: true / false \n" \


#define MEGAFLOPS 1000000
#define MEGABYTES 1024*1024

int DEBUG = false;


//MUST MODIFY TO SATISFY ASSIGNMENT BELOW THIS LINE//
//=================================================//

const int SIZE = 256;


// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]
//may want to print periodic status to the screen to verify the rate of progress
void multiply_double(int size, double mat1[size][size], double mat2[size][size], double res[size][size])
{
    int i, j, k;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            res[i][j] = 0;
            for (k = 0; k < size; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

void multiply_int(int size, int mat1[size][size], int mat2[size][size], int res[size][size])
{
    int i, j, k;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            res[i][j] = 0;
            for (k = 0; k < size; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}


void compute_flops_int(int size)
{
	int index, index2;
	int result;
	int loops = size;
	for (index=0;index<loops;index++)
	{
		for (index2=0;index2<MEGAFLOPS;index2++)
			result = index2+1;
	}
	if (DEBUG)
		printf("%d\n",result);
	
}

void compute_flops_double(int size)
{
	int index, index2;
	double result;
	int loops = size;
	for (index=0;index<loops;index++)
	{
		for (index2=0;index2<MEGAFLOPS;index2++)
			result = index2+1.0;
	}
	if (DEBUG)
		printf("%lf\n",result);
	
}

//=================================================//
//MUST MODIFY TO SATISFY ASSIGNMENT ABOVE THIS LINE//


int compute_checksum_static_double(int size, double res[size][size]){
	if (DEBUG)
		printf("compute_checksum...");
	int checksum = 0;
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
                checksum += (int) res[i][j];
        }
    }
    return checksum;
}

int compute_checksum_static_int(int size, int res[size][size]){
	if (DEBUG)
	printf("compute_checksum...");
	int checksum = 0;
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
                checksum += res[i][j];
        }
    }
    return checksum;
}


int compute_checksum_dynamic_double(int size, double** res){
	if (DEBUG)
	printf("compute_checksum...");
	int checksum = 0;
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
                checksum += (int) res[i][j];
        }
    }
    return checksum;
}

int compute_checksum_dynamic_int(int size, int** res){
	if (DEBUG)
	printf("compute_checksum...");
	int checksum = 0;
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
                checksum += res[i][j];
        }
    }
    return checksum;
}


int main(int argc, char **argv)
{
	int checksum = 0;
	time_t t;
	srand((unsigned) time(&t));
    if (argc != 7) 
    {
        printf(USAGE);
		printf("mode=-1 type=-1 size=-1 threads=-1 time=-1 throughput=-1 checksum=-1\n");
        exit(1);
    } 
    else 
    {
    	
    	int seed = atoi(argv[1]);
		srand(seed);
    	
		int mode = -1;
        if(strcmp(argv[2],"flops") == 0)
        	mode = 0;
        else if(strcmp(argv[2],"matrix") == 0)
        	mode = 1;
        else
        	mode = -1;

		int type = -1;
        if(strcmp(argv[3],"single") == 0)
        	type = 0;
        else if(strcmp(argv[3],"double") == 0)
        	type = 1;
        else
        	type = -1;


        int size = atoi(argv[4]);
        int num_threads = atoi(argv[5]);

        if(strcmp(argv[6],"true") == 0)
        	DEBUG = true;
        else if(strcmp(argv[6],"false") == 0)
        	DEBUG = false;
        else
        {
        	printf("error in DEBUG argument, must be either true or false; exiting...\n");
			printf("mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-2\n",argv[2],argv[3],size,num_threads);
			exit(-1);
		}	
		
		if (DEBUG)
    		printf(MSG, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
		

		struct timeval start, end;

		if (mode == 0 && type == 0)
		{	
			gettimeofday(&start, NULL);
			compute_flops_int(size);
		    gettimeofday(&end, NULL);
		}
		else if (mode == 0 && type == 1)
		{	
			gettimeofday(&start, NULL);
			compute_flops_double(size);
		    gettimeofday(&end, NULL);
		}		
		else if (mode == 1 && type == 0)
		{	
		
			if (size != SIZE)
			{
				if (DEBUG)
					printf("you specified a size of %d, but there is a constant SIZE set to %d; your code is not correct, and must be updated to take the size parameter from the command line; exiting...", size, SIZE);
				else
					printf("mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-3\n",argv[2],argv[3],size,num_threads);
				exit(-1);
			}
			size_t len = 0;
			int i, j;//, k;
  
			len = sizeof(double *) * SIZE * SIZE * 3;
			if (DEBUG)
				printf("allocating %lf GB memory...\n",len*3.0/(1024*1024*1024)); 

//MUST MODIFY TO SATISFY ASSIGNMENT BELOW THIS LINE//
//=================================================//
	
			int arr1[SIZE][SIZE];
			int arr2[SIZE][SIZE];
			int arr3[SIZE][SIZE];
			//set to false if dynamic memory allocation is used
			bool STATIC = true;

//=================================================//
//MUST MODIFY TO SATISFY ASSIGNMENT ABOVE THIS LINE//


			for (i = 0; i < SIZE; i++) 
				for (j = 0; j < SIZE; j++) 
				{
					arr1[i][j] = (int)((rand()*1.0/rand())*10.0); 
					arr2[i][j] = (int)((rand()*1.0/rand())*10.0); 
					arr3[i][j] = 0.0; 
				}
		
		
			gettimeofday(&start, NULL);
			multiply_int(size,arr1,arr2,arr3);
		    gettimeofday(&end, NULL);
		    
			if (STATIC == true)
				checksum = compute_checksum_static_int(size, arr3);
			else
				checksum = compute_checksum_dynamic_int(size, arr3);
		    
		    
		}
		else if (mode == 1 && type == 1)
		{	
			//must change to take parameter from command line		
			if (size != SIZE)
			{
				if (DEBUG)
					printf("you specified a size of %d, but there is a constant SIZE set to %d; your code is not correct, and must be updated to take the size parameter from the command line; exiting...", size, SIZE);
				else
					printf("mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-4\n",argv[2],argv[3],size,num_threads);
					
				return -1;
			}
			size_t len = 0;
			int i, j;//, k;
  
			len = sizeof(double *) * SIZE * SIZE * 3;
			if (DEBUG)
				printf("allocating %lf GB memory...\n",len*3.0/(1024*1024*1024)); 

//MUST MODIFY TO SATISFY ASSIGNMENT BELOW THIS LINE//
//=================================================//
	
			double arr1[SIZE][SIZE];
			double arr2[SIZE][SIZE];
			double arr3[SIZE][SIZE];
			//set to false if dynamic memory allocation is used
			bool STATIC = true;

	//=================================================//
	//MUST MODIFY TO SATISFY ASSIGNMENT ABOVE THIS LINE//


			for (i = 0; i < SIZE; i++) 
				for (j = 0; j < SIZE; j++) 
				{
					arr1[i][j] = (double)rand()/rand(); 
					arr2[i][j] = (double)rand()/rand();  
					arr3[i][j] = 0.0; 
				}
		
		
			gettimeofday(&start, NULL);
			multiply_double(size,arr1,arr2,arr3);
		    gettimeofday(&end, NULL);

			if (STATIC == true)
				checksum = compute_checksum_static_double(size, arr3);
			else
				checksum = compute_checksum_dynamic_double(size, arr3);
		    
		    
		}
		else
		{
			if (DEBUG)
        	{
        		printf(USAGE);
				printf("unrecognized option, exiting...\n");
			}
			else
				printf("mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-6\n",argv[2],argv[3],size,num_threads);
				
        	exit(1);
		}

		double elapsed_time_sec = (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))/1000000.0;
		double num_giga_ops = 0;
		
		if (size*MEGAFLOPS < 0)
		{
			if (DEBUG)
				printf("error in size, check for overflow; exiting...\n");
			else
				printf("mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-7\n",argv[2],argv[3],size,num_threads);
			exit(1);
		}
		if (elapsed_time_sec < 0)
		{
			if (DEBUG)
				printf("error in elapsed time, check for proper timing; exiting...\n");
			else
				printf("mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-8\n",argv[2],argv[3],size,num_threads);
			exit(1);
		}
		if (elapsed_time_sec == 0)
		{
			if (DEBUG)
				printf("elapsed time is 0, check for proper timing or make sure to increase amount of work performed; exiting...\n");
			else
				printf("mode=%s type=%s size=%d threads=%d time=0.0 throughput=0.0 checksum=-9\n",argv[2],argv[3],size,num_threads);
			exit(1);
		}
			
		
		if (mode == 0)
			num_giga_ops = size*1000.0/MEGAFLOPS;
		else if (mode == 1)
			num_giga_ops = size*size*size*1.0/(MEGABYTES*1024.0);
		double throughput = num_giga_ops/elapsed_time_sec;
		printf("mode=%s type=%s size=%d threads=%d time=%lf throughput=%lf checksum=%d\n",argv[2],argv[3],size,num_threads,elapsed_time_sec,throughput,checksum);
 
    }

    return 0;
}