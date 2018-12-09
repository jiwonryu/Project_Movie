#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"
#include "linkedList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	FILE *fp; //FILE pointer for reading movie data 
	char name[200]; //movie name
	char country[10]; //movie country
	int runTime; //movie runtime
	float score; //movie score
	
	int exit_flag = 0; //flag variable for while loop
	int option; //user input option
	void *list, *mvInfo; //pointers for linked list and a specific structure instance for a movie data
	void *ndPtr; //void pointer for linked list node
	
	
	//1. reading the movie.dat-----------------------------
	printf("Reading the data files...\n");
	//1.1 FILE open
	fp = fopen("movie.dat", "r");
	if(fgetc(fp) == -1) //file open succes?
	{
		printf("[ERROR] failed to road the data files\n");
	}
	fseek(fp, 0L, SEEK_SET);
	
	//1.2 list generation (use function list_genList() )
	list = list_genList();
	ndPtr = list;
	//1.3 read each movie data from the file and add it to the linked list
	while (1 /* read name, country, runtime and score*/ )
	{	
		fscanf(fp,"%s%s%d%f",name,country,&runTime,&score);
		mvInfo = mv_genMvInfo(name, score, runTime, country);
		list_addNext(mvInfo, ndPtr);
	
	//generate a movie info instance(mvInfo) with function mv_genMvInfo()
		if(fgetc(fp) == -1)
		{
			//list_addTail(mvInfo, ndPtr);
			break;
		}
	}

	//1.4 FILE close
	fclose(fp);
	
	printf("Read done! %d items are read\n", list_len(list));
	
	//2. program start
	
	while(exit_flag == 0) 
	{
		//2.1 print menu message and get input option
		printf("\n\n\n------------------ Menu ------------------\n");
		printf("1. print all the movies\n");
		printf("2. search for specific country movies\n");
		printf("3. search for specific runtime movies\n");
		printf("4. search for specific score movies\n");
		printf("5. exit\n");
		printf("------------------ Menu ------------------\n\n");
		printf("-- select an option : ");
		scanf("%d", &option);		
		
		switch(option)
		{
			case 1: //print all the movies
				printf("printing all the movies in the list.....\n\n\n");
				
				ndPtr = list;
				int len = 0;
				
				//while ( list_isEndNode(ndPtr) == 0 ) //repeat until the ndPtr points to the end node
				//{
					printf("-------------------------------------------------\n");
					len = list_repeatFunc(mv_print,ndPtr);
						
					//2.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					//get object of ndPtr to mvInfo void pointer
					//print the contents of the mvInfo
				//}
				
				printf("\t- totally %d movies are listed!\n", len);
				
				break;
				
				
			case 5:
				printf("Bye!\n\n");
				exit_flag = 1;
				break;
				
			default:
				printf("wrong command! input again\n");
				break;
		}
	}
	
	return 0;
}
