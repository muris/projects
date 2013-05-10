#include <stdio.h>
#include "RecordManager.h"

void Output(struct data *p);

int main()
{
	
	printf("******************************************\n");
	printf("*        Record Manager Application      *\n");
	printf("*                 Xinyi He               *\n");
	printf("******************************************\n");
	char c;
	do
	{
		printf("\n");
		printf("a. Open database\n");
		printf("b. Get first record\n");
		printf("c. Get next record \n");
		printf("d. Get previous record\n");
		printf("e. Get Nth record\n");
		printf("f. Insert record\n");
		printf("g. Bulk insert records in file\n");
		printf("h. Delete record\n");
		printf("i. Update record\n");
		printf("j. Find record with first attribute value\n");
		printf("k. Show catalog file\n");
		printf("l. Get first page\n");
		printf("m. Get next page\n");
		printf("n. Show buf stats\n");
		printf("o. Commit changes\n");
		printf("p. Exit\n");
		printf("Please press letter to choose an action.\n");
		c = getchar();
		fflush(stdin);

		char filename[100];

		switch (c)
		{
			//a. Open database
		case 'a':
			{
				printf("Please input the database name (don't include extension): ");				
				gets(filename);
				OpenStore(filename);
				break;
			}
			//b. Get first record
		case 'b':
			{
				Output(FirstRec());
				break;
			}
			//c. Get next record
		case 'c':
			{
				Output(NextRec());
				break;
			}
			//d. Get previous record
		case 'd':
			{
				Output(PriorRec());
				break;
			}
			//e. Get Nth record
		case 'e':
			{
				printf("\nInput N: ");
				int n;
				scanf("%d", &n);
				Output(NRec(n));
				fflush(stdin);
				break;
			}
			//f. Insert record
		case 'f':
			{
				printf("\nInput a comma-delimited Record:\n");
				char statement[100];
				scanf("%s", &statement);
				fflush(stdin);
				InsertRec(statement);				
				break;
			}
			//g. Bulk insert records in file
		case 'g':
			{
				printf("\nInput the filename(include extension): ");
				char file[100];
				scanf("%s", &file);
				InsertRecFromFile(file);
				fflush(stdin);
				break;
			}
			//h. Delete record
		case 'h':
			{
				DeleteRec();
				break;
			}
			//i. Update record
		case 'i':
			{
				printf("\nInput a comma-delimited Record:\n");
				char statement[100];
				scanf("%s", &statement);
				fflush(stdin);
				UpdateRec(statement);
				break;
			}
			//j. Find record with first attribute value
		case 'j':
			{
				printf("\nInput value:\n");
				char statement[100];
				scanf("%s", &statement);
				fflush(stdin);
				SearchRec(statement);
				break;
			}
			//k. Show catalog file
		case 'k':
			{
				DisplyCatFile(filename);
				break;
			}
			//l. Get first page
		case 'l':
			{
				GetPage(0);
				break;
			}
			//m. Get next page
		case 'm':
			{
				GetPage(1);
				break;
			}
			//n. Show buf stats
		case 'n':
			{
				ShowBuf();
				break;
			}
			//o. Commit changes
		case 'o':
			{
				Commit(filename);
				break;
			}
			//p. Exit
		case 'p':
			{
				CloseStore(filename);
			}
		};
	}while(c != 'p');

	return 0;
}

void Output(struct data *p)
{
	struct data *temp = p;
	while (temp != NULL)
	{
		printf("%s\t", temp->record);
		temp = temp->nextcolumndata;
	}
	printf("\n");
}