#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "RecordManager.h"

struct column *pc=NULL;
struct table *pt=NULL;
struct data *pd=NULL;

struct data *pcur = NULL;
struct data *pagehead = NULL;
struct data *pageend = NULL;

int pagesize = 0;

//create and initialize the file to hold the database
void CreateStore(char *filename)
{
	FILE *fp = fopen(filename, "w");
	char attr1[] = "snum\tint\r\n";
	char attr2[] = "lname\tchar\t6\tNULL\r\n";
	char attr3[] = "fname\tchar\t5\tNULL\r\n";
	char attr4[] = "GPA\tfloat\r\n";
	fputs(attr1, fp);
	fputs(attr2, fp);
	fputs(attr3, fp);
	fputs(attr4, fp);

	char *fname = (char *)malloc(sizeof(char)*strlen(filename));
	int i = 0;
	for (; filename[i] != '.'; i++)
	{
		fname[i] = filename[i];
	}
	fname[i] = '\0';
	fname = strcat(fname, ".db");
	
	FILE *fpp = fopen(fname, "w");
	free(fname);
	fclose(fpp);
	fclose(fp);
}

//open the file containing the database
void OpenStore(char *filename)
{
	FreeSpace();

	char file[100];
	strcpy(file, strcat(filename, ".cat"));
	FILE *fp = fopen(file, "r");
	if (fp == NULL)
	{
		CreateStore(file);
		fp = fopen(file, "r");
	}
	
	pt = (struct table *)malloc(sizeof(struct table));
	pc = (struct column *)malloc(sizeof(struct column));
	pt->firstcolumn = pc;

	struct column *pcol1 = pc;
	struct column *pcol2 = pc;

	strcpy(pt->tablename, "table");

	char p_tlen[8];
	char p_nlen[10];
	int i = 0;
	char c;
	c = fgetc(fp);
	do
	{
		//save column name
		for (i = 0; !isspace(c) && c != EOF; i++)
		{
			pcol1->col_name[i] = c;
			c = fgetc(fp);
		}
		pcol1->col_name[i] = '\0';
		//save column type
		c = fgetc(fp);
		for (i = 0; !isspace(c) && c != EOF; i++)
		{
			pcol1->type[i] = c;
			c = fgetc(fp);
		}
		pcol1->type[i] = '\0';
		//save column type's length. For int or float, it is 4.
		if (pcol1->type[0] == 'i' || pcol1->type[0] == 'f')
		{
			pcol1->len = 4;
		}
		else
		{
			int j = 0;
			c = fgetc(fp);
			for(j = 0; !isspace(c) && c != EOF; j++)
			{
				p_tlen[j] = c;
				c = fgetc(fp);
			}
			p_tlen[j] = '\0';
			pcol1->len = atoi(p_tlen);
		}
		//save null or not null. isNull is 0 means it is not null, otherwise it is 1. 
		c = fgetc(fp);
		if (isspace(c) || c == EOF)
		{
			pcol1->isNull = 0;
		}
		else
		{			
			for (i = 0; c != '\r' && c != '\n' && c != EOF; i++)
			{
				p_nlen[i] = c;
				c = fgetc(fp);
			}
			p_nlen[i] = '\0';
			if (strcmp(p_nlen, "NOT NULL") == 0)
			{
				pcol1->isNull = 0;
			}
			else if (strcmp(p_nlen, "NULL") == 0)
			{
				pcol1->isNull = 1;
			}
			c = fgetc(fp);
		}	
		c = fgetc(fp);
		if ( c == EOF)
		{
			pcol1->nextcolumn = NULL;
		}
		else
		{
			pcol2 = (struct column *)malloc(sizeof(struct column));
			pcol1->nextcolumn = pcol2;
			pcol1 = pcol1->nextcolumn;
			fseek(fp, -1, SEEK_CUR);
		}
	} while( (c = fgetc(fp)) != EOF);
	fclose(fp);

	//insert records from .db file
	char *frecord = (char *)malloc(sizeof(char) * strlen(filename));
	int x = 0;
	for (; filename[x] != '.'; x++)
	{
		frecord[x] = filename[x];
	}
	frecord[x] = '\0';
	strcat(frecord, ".db");
	InsertRecFromFile(frecord);
	pcur = pd;

	pcol1 = pc;
	int size = 0;
	while (pcol1 != NULL)
	{
		size += pcol1->len;
		pcol1 = pcol1->nextcolumn;
	}
	pagesize = 80/size;
	pagehead = pd;

	pageend = pagehead;
	int ii = 0;

	if (pd != NULL)
	{
		//Set the end of page
		for (i = 0; i < pagesize; i++)
		{
			if (pageend->nextrowdata != NULL)
			{
				pageend = pageend->nextrowdata;
			}
			else
			{
				break;
			}
		}
	}
}

//get first record in the physical order
struct data *FirstRec()
{
	pcur = pd;
	return pd;
}

//get next record in the physical order
struct data *NextRec()
{
	if (pcur != NULL)
	{
		if (pcur->nextrowdata != NULL)
		{
			pcur = pcur->nextrowdata;
			return pcur;
		}
		else
		{
			printf("\nThe current record is the last one.\n");
			return NULL;
		}
	}
	else
	{
		printf("\nThe current record is not known.\n");
		return NULL;
	}
}
struct data *NRec(int n)
{
	struct data *p = pd;

	for (int i = 0; i < n; i++)
	{
		if (p != NULL)
		{
			p = p->nextrowdata;
		}
		else
		{
			break;
		}
	}
	if (p != NULL)
	{
		pcur = p;
		return p;
	}
	else
	{
		printf("\nThere are fewer than N records in the database.\n");
		return NULL;
	}

}

//get previous record in the physical order
struct data * PriorRec()
{
	struct data *p = pd;
	if (pcur != NULL)
	{

		if (pcur != pd)
		{
			while(p->nextrowdata != pcur)
			{
				p = p->nextrowdata;
			}
			pcur = p;
			return p;
		}
		else
		{
			printf("\nThe current record is the first one.\n");
			return NULL;
		}
	}
	else
	{
		printf("\nThe current record is not known.\n");
		return NULL;
	}
}
//insert a new record
void InsertRec(char *stat)
{
	struct column *pcol = pc;
	struct data *prerow = pc->firstdata;
	struct data *pdata1;
	struct data *pdata2;
	int n = 0;//number of column
	while (pcol != NULL)
	{
		n++;
		pcol = pcol->nextcolumn;
	}
	int n_comma = 0;
	int i = 0;
	for (i = 0; i < strlen(stat); i++)
	{
		if (stat[i] == ',')
		{
			n_comma++;
		}
	}
	if (n_comma != n - 1)
	{
		printf("\nThe record is not valid.\n");
	}
	else
	{
		prerow = pd;
		while (prerow->nextrowdata != NULL)
		{
			prerow = prerow->nextrowdata;
		}
		int nline = prerow->i_ID + 1;
		pdata1 = (struct data*)malloc(sizeof(struct data));
		pdata2 = pdata1;
		pcol = pc;
		int index = 0;
		int j = 0;
		pcur = pdata1;

		while (pcol != NULL && index < strlen(stat))
		{
			if (strcmp(pcol->type, "char") != 0)
			{
				pdata1->record = (char *)malloc(100 * sizeof(char));
			}
			else
			{
				pdata1->record = (char *)malloc(sizeof(char) * (pcol->len+1));
			}				
			for (j = 0; stat[index] != ',' && stat[index] != '\0'; j++, index++)
			{
				pdata1->record[j] = stat[index];					
			}
			pdata1->record[j] = '\0';
			pdata1->i_ID = nline;
			pdata1->nextrowdata = NULL;
			pdata1->nextcolumndata = NULL;

			if (nline > 1)
			{
				prerow->nextrowdata = pdata1;	
				prerow = prerow->nextcolumndata;
			}
			else//it is the first row in the database
			{
				pcol->firstdata = pdata1;
			}

			if (pcol->nextcolumn != NULL)//it is not the last column
			{
				pdata2 = (struct data*)malloc(sizeof(struct data));
				pdata1->nextcolumndata = pdata2;				
				pdata1 = pdata1->nextcolumndata;
			}
			else
			{
				pdata1->nextcolumndata = NULL;
			}
			pcol = pcol->nextcolumn;		
			index++;
		}

		PrintTable();
	}
}
//delete current record
void DeleteRec()
{
	if (pcur != NULL)
	{
		struct data *prior = pd;
		struct data *last = pd;
		struct data *lastprior = pd;
		struct data *del1 = pcur;
		struct data *del2 = del1;
		
		if (pcur != prior)//more than 1 record
		{
			while (prior->nextrowdata != pcur)
			{
				prior = prior->nextrowdata;
			}
			while (last->nextrowdata != NULL)
			{
				last = last->nextrowdata;
			}
			while (lastprior->nextrowdata != last)
			{
				lastprior = lastprior->nextrowdata;
			}

			if (pcur->nextrowdata != NULL)//currect record is not the last one
			{
				struct data *tmp = last;
				while (prior != NULL)
				{
					prior->nextrowdata = last;
					if (lastprior != pcur)
					{					
						last->nextrowdata = pcur->nextrowdata;
						lastprior->nextrowdata = NULL;

						pcur = pcur->nextcolumndata;
						lastprior = lastprior->nextcolumndata;
					}
					prior = prior->nextcolumndata;
					last = last->nextcolumndata;
				}
				pcur = tmp;
				while (del1 != NULL)
				{
					del1 = del1->nextcolumndata;
					free(del2->record);
					free(del2);
					del2 = del1;
				}
			}
			else
			{
				pcur = prior;
				while (del1 != NULL)
				{
					del1 = del1->nextcolumndata;
					free(del2->record);
					free(del2);
					del2 = del1;
				}
				while (prior != NULL)
				{
					prior->nextrowdata = NULL;
					prior = prior->nextcolumndata;
				}
			}
		}
		else
		{
		}
		PrintTable();
	}
	else
	{
		printf("\nThe current record is not known.\n");
	}
}
//replace the current record with the new one
void UpdateRec(char *stat)
{
	if (pcur != NULL)
	{
		struct column *pcol = pc;		
		struct data *pdata1 = pcur;
	
		int n = 0;//number of column
		while (pcol != NULL)
		{
			n++;
			pcol = pcol->nextcolumn;
		}
		int n_comma = 0;
		int i = 0;
		for (i = 0; i < strlen(stat); i++)
		{
			if (stat[i] == ',')
			{
				n_comma++;
			}
		}
		if (n_comma != n - 1)
		{
			printf("\nThe record is not valid.\n");
		}
		else
		{
			pcol = pc;
			int index = 0;
			int j = 0;

			while (pcol != NULL && index < strlen(stat))
			{
				//delete old record and allocate a new space
				free(pdata1->record);

				if (strcmp(pcol->type, "char") != 0)
				{
					pdata1->record = (char *)malloc(100 * sizeof(char));
				}
				else
				{
					pdata1->record = (char *)malloc(sizeof(char) * (pcol->len+1));
				}
				for (j = 0; stat[index] != ',' && stat[index] != '\0'; j++, index++)
				{
					pdata1->record[j] = stat[index];					
				}
				pdata1->record[j] = '\0';

				pcol = pcol->nextcolumn;
				pdata1 = pdata1->nextcolumndata;
				index++;
			}

			PrintTable();
		}
	}
	else
	{
		printf("\nThe current record is not known.\n");
	}
}
//make sure all changes are propagated to disk and close the database
void CloseStore(char *file)
{	
	Commit(file);
	FreeSpace();
}
//insert records from file
void InsertRecFromFile(char *filename)
{
	struct table *ptable = pt;
	struct column *pcolhead = ptable->firstcolumn;
	struct column *pcol = pcolhead;
	struct data *prerow;
	struct data *pdata1;
	struct data *pdata2;

	int nline = 1; // number of records
	FILE *fp = fopen(filename, "r");
	char c;
	if (fp != NULL)
	{
		c = fgetc(fp);
		if (c != EOF)
		{
			if (pd == NULL)
			{
				pd = (struct data*)malloc(sizeof(struct data));
				prerow = pd;
				pdata1 = pd;
			}
			else
			{
				prerow = pd;
				while (prerow->nextrowdata != NULL)
				{
					prerow = prerow->nextrowdata;
				}
				nline = prerow->i_ID + 1;
				pdata1 = (struct data*)malloc(sizeof(struct data));
			}
			pdata2 = pdata1;
			pcur = pdata1;
		}
		int i = 0;	

		while (c != EOF)
		{
			while (pcol != NULL)
			{
				//allocate space for data
				if (strcmp(pcol->type, "char") != 0)
				{
					pdata1->record = (char *)malloc(100 * sizeof(char));
				}
				else
				{
					pdata1->record = (char *)malloc(sizeof(char) * (pcol->len+1));
				}

				
				for (i = 0; !isspace(c) && c != EOF; i++)
				{
					if ((strcmp(pcol->type, "char") == 0 && i < pcol->len) || strcmp(pcol->type, "char") != 0)
					{
						pdata1->record[i] = c;
						c = fgetc(fp);
					}
					else
					{
						break; //data is longer than its size 
					}
				}//At the end of loop, c is not a char
				pdata1->record[i] = '\0';
				pdata1->i_ID = nline;
				pdata1->nextrowdata = NULL;
				pdata1->nextcolumndata = NULL;
				
				if (nline > 1)
				{
					prerow->nextrowdata = pdata1;	
					prerow = prerow->nextcolumndata;
				}
				else//it is the first row in the database
				{
					pcol->firstdata = pdata1;
				}

				if (pcol->nextcolumn != NULL)//it is not the last column
				{
					pdata2 = (struct data*)malloc(sizeof(struct data));
					pdata1->nextcolumndata = pdata2;				
					pdata1 = pdata1->nextcolumndata;
				}
				else
				{
					pdata1->nextcolumndata = NULL;
				}
				pcol = pcol->nextcolumn;				
				c = fgetc(fp);
				
			}//end-while(pcol!=null)
			
			while (isspace(c))
			{
				c = fgetc(fp);
			}
			if (!feof(fp))
			{
				pcol = pcolhead;
				nline++;
				pd = pc->firstdata;
				prerow = pd;
				for (int k = 1; k < nline - 1; k++)
				{
					prerow = prerow->nextrowdata;
				}
				pdata1 =  (struct data*)malloc(sizeof(struct data));
			}
		}//end-while(c != EOF)		

		fclose(fp);
	}

	PrintTable();
}

void PrintTable()
{
	struct data *p1 = pd;
	struct data *p2 = pd;

	printf("\n\n");
	while (p2 != NULL)
	{
		while (p1 != NULL)
		{
			printf("%s\t", p1->record);
			p1 = p1->nextcolumndata;
		}
		p2 = p2->nextrowdata;
		p1 = p2;
		printf("\n");
	}
}

//Find record with first attribute value
void SearchRec(char *stat)
{
	struct data *pdata1 = pd;
	struct data *pdata2 = pdata1;

	while (pdata1 != NULL)
	{
		if (strcmp(pdata2->record, stat) == 0)
		{
			while (pdata2 != NULL)
			{
				printf("\n\n%s\t", pdata2->record);
				pdata2 = pdata2->nextcolumndata;
			}
			printf("\n");
		}
		pdata1 = pdata1->nextrowdata;
		pdata2 = pdata1;
	}
}

void DisplyCatFile(char *file)
{
	FILE *fp = fopen(file, "r");
	
	if (fp)
	{
		char str[1000];
		printf("\n\n");
		do
		{
			fgets(str, 1000, fp);
			if (!feof(fp))
			{
				printf("%s\n", str);
			}
		}while (!feof(fp));
	}
	fclose(fp);
}
void Commit(char *file)
{
	char *fname = (char *)malloc(sizeof(char)*strlen(file));
	int i = 0;
	for (; file[i] != '.'; i++)
	{
		fname[i] = file[i];
	}
	fname[i] = '\0';
	fname = strcat(fname, ".db");
	
	FILE *fp = fopen(fname, "w");

	struct data *pdata1 = pd;
	struct data *pdata2 = pdata1;
	while (pdata1 != NULL)
	{
		while (pdata2 != NULL)
		{
			fprintf(fp, "%s\t", pdata2->record);
			pdata2 = pdata2->nextcolumndata;			
		}
		fprintf(fp, "\n");
		pdata1 = pdata1->nextrowdata;
		pdata2 = pdata1;		
	}
	fclose(fp);
}
void FreeSpace()
{
	if (pd != NULL)
	{
		struct data *p1 = pd;
		struct data *p2 = p1->nextrowdata;
		struct data *p3 = p1->nextcolumndata;

		while (p2 != NULL)
		{
			while ( p3 != NULL)
			{
				free(p1->record);
				free(p1);
				p1 = p3;
				p3 = p3->nextcolumndata;
			}
			if (p1 != NULL)
			{
				free(p1->record);
				free(p1);
			}
			p1 = p2;
			p3 = p1->nextcolumndata;
			p2 = p1->nextrowdata;
		}
		while (p3 != NULL)
		{
			free(p1->record);
			free(p1);
			p1 = p3;
			p3 = p3->nextcolumndata;
		}
		if (p1 != NULL)
		{
			free(p1->record);
			free(p1);
		}
		struct column *pcol = pc->nextcolumn;
		while (pcol != NULL)
		{
			free(pc);
			pc = pcol;
			pcol = pcol->nextcolumn;
		}
		if (pc != NULL)
		{
			free(pc);
		}
		if (pt != NULL)
		{
			free(pt);
		}
	}
	pt = NULL;
	pc = NULL;
	pd = NULL;
	pagesize = 0;
	pagehead = NULL;
	pageend = NULL;
}
void GetPage(int x)
{
	//x == 0 means it gets the first page, otherwise gets next page
	if (x == 0)
	{
		pagehead = pd;
	}
	else
	{
		pagehead = pageend;
	}
	pageend = pagehead;
	int i = 0;

	struct data *pdata1 = pagehead;
	struct data *pdata2 = pdata1;

	if (pagehead != NULL)
	{
		printf("\n\nPage:\n");
		//Set the end of page
		for (i = 0; i < pagesize; i++)
		{
			if (pageend->nextrowdata != NULL)
			{
				pageend = pageend->nextrowdata;
			}
			else
			{
				break;
			}
		}

		if (pagehead != pageend)
		{
			while (pdata1 != pageend && pdata1 != NULL)
			{
				while (pdata2 != NULL)
				{
					printf("%s\t", pdata2->record);
					pdata2 = pdata2->nextcolumndata;
				}
				printf("\n");
				pdata1 = pdata1->nextrowdata;
				pdata2 = pdata1;
			}
		}
		else
		{
			pdata2 = pdata1;
			while (pdata2 != NULL)
			{
				printf("%s\t", pdata2->record);
				pdata2 = pdata2->nextcolumndata;
			}
			printf("\n");
		}
	}
}

void ShowBuf()
{
	printf("Current Page:\n");
	
	int i = 0;

	struct data *pdata1 = pagehead;
	struct data *pdata2 = pdata1;

	if (pagehead != NULL)
	{
		if (pagehead != pageend)
		{
			while (pdata1 != pageend && pdata1 != NULL)
			{
				while (pdata2 != NULL)
				{
					printf("%s\t", pdata2->record);
					pdata2 = pdata2->nextcolumndata;
				}
				printf("\n");
				pdata1 = pdata1->nextrowdata;
				pdata2 = pdata1;
			}
		}
		else
		{
			pdata2 = pdata1;
			while (pdata2 != NULL)
			{
				printf("%s\t", pdata2->record);
				pdata2 = pdata2->nextcolumndata;
			}
			printf("\n");
		}
	}
}