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
		printf("[ERROR] failed to road the data files\n");
	fseek(fp, 0L, SEEK_SET);//initialize file position pointer 
	
	//1.2 list generation (use function list_genList() )
	list = list_genList();
	ndPtr = list;
	
	//1.3 read each movie data from the file and add it to the linked list
	while (1) 
	{	
		fscanf(fp,"%s%s%d%f",name,country,&runTime,&score); //read name, country, runtime and score
		mvInfo = mv_genMvInfo(name, score, runTime, country); //generate a movie info instance(mvInfo) with function mv_genMvInfo()
		list_addNext(mvInfo, ndPtr); //generate a next node with a movie info
		ndPtr = list_getNextNd(ndPtr);//change ndPtr to point next node
		if(fgetc(fp) == -1)  //if the file is end, finish adding node
			break;
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
		while (getchar() != '\n');
		
		int len;
		char inputs[10];
		float inputf;
		int inputn;
		void *cmpList, *usList;
		
		//2.2 print a movie data : use functions of movie.c and linkedList.c
		switch(option)
		{
			case 1: //print all the movies
				printf("printing all the movies in the list.....\n\n\n");
				
				cmpList = list_genList();
				ndPtr = list;
				len = 0;
				printf("-------------------------------------------------\n");
				len = list_repeatFunc(mv_print,ndPtr);
				printf("\t- totally %d movies are listed!\n", len);
				break;
				
			case 2://print specific country movies
				cmpList = list_genList(); // make a new list
				usList = cmpList;
				ndPtr = list;
				len = 0;
				printf("select a country : ");
				scanf("%s", inputs); //input country
				while (getchar() != '\n'); //clean buffer
	
				while (1)
				{	
					ndPtr = list_getNextNd(ndPtr);
					if(!(strcmp(mv_getCountry(list_getNdObj(ndPtr)), inputs))) //compare input country with mv_country of node
					{
						list_addNext(list_getNdObj(ndPtr), usList); //copy mv_info to new list
						usList = list_getNextNd(usList);	
					}
					if(list_isEndNode(ndPtr))
						break;
				}
				
				printf("-------------------------------------------------\n");
				len = list_repeatFunc(mv_print,cmpList);
				printf("\t- totally %d movies are listed!\n", len);
				break;
				
			case 3://print specific runtime movies
				cmpList = list_genList();
				usList = cmpList;
				ndPtr = list;
				len = 0;
				printf("input runtime : ");
				scanf("%d", &inputn); // input runtime
				while (getchar() != '\n'); // clean buffer
				
				while (1)
				{	
					ndPtr = list_getNextNd(ndPtr);
					if(mv_getRunTime(list_getNdObj(ndPtr)) > inputn) //compare input runtime with mv_country of node
					{
						list_addNext(list_getNdObj(ndPtr), usList);
						usList = list_getNextNd(usList);	
					}
					if(list_isEndNode(ndPtr))
						break;
				}
				
				printf("-------------------------------------------------\n");
				len = list_repeatFunc(mv_print,cmpList);
				printf("\t- totally %d movies are listed!\n", len);
				break;
				
			case 4://print specific score movies
				
				cmpList = list_genList();
				usList = cmpList;
				ndPtr = list;
				len = 0;
				printf("input score : ");
				scanf("%f", &inputf); //input score
				while (getchar() != '\n'); //clean buffer
				
				while (1)
				{	
					ndPtr = list_getNextNd(ndPtr);
					if(mv_getScore(list_getNdObj(ndPtr)) > inputf)//compare input score with mv_score of node
					{
						list_addNext(list_getNdObj(ndPtr), usList); 
						usList = list_getNextNd(usList);	
					}
					if(list_isEndNode(ndPtr))
						break;
				}
				
				printf("-------------------------------------------------\n");
				len = list_repeatFunc(mv_print,cmpList);
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
