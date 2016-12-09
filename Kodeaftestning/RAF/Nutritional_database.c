#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 50
#define MAX_CHARS 25
#define DATABASE_DEPTH 15

typedef struct nutrition 
{
	char  ingredient[MAX_CHARS];
	int   kiloJoule;
	float protein;
} nutrition;

typedef struct ingredientPos
{
	char ingredientName[MAX_CHARS];
	long int position;
} ingredientPos;

/* Prototyper */
void initialise_nutritional_database();
void index_database(FILE *ind, char indexFile[MAX_CHARS], FILE *dtb, 
					int *indLen, ingredientPos *indexArr);
//nutrition load_ingredient(char *ingredient, int kiloJoule, float protein);
void load_index(FILE *ind, ingredientPos *indexArr, int indLen);

int main(void)
{
	initialise_nutritional_database();
	/* Ask for ingredient */
	//retrieveIngredients();

	
	/* Find database position in index file */


	/* Pull the data from the database */

	return 0;
}

void initialise_nutritional_database() {
	/* Variable initialisation */
	char ingredient[MAX_CHARS];
	char dataFile[] = "ANutritional_database.txt";
	char indexFile[] = "Nutritional_index.txt";
	int len = 0, indLen = 0;
	ingredientPos indexArr[DATABASE_DEPTH];
	FILE *dtb, *ind;

	/* Open the database file and check if open */
	dtb = fopen(dataFile, "r+");
	if(dtb == NULL)
	{
		printf("No database with name \"%s\" exists!\n", dataFile);
		exit(EXIT_FAILURE);
	}

	/* Open the index file, or index the database if no file is present */
	ind = fopen(indexFile, "r");
	if(ind == NULL)
	{
		puts("Could not find index file. Creating one...");
		index_database(ind, indexFile, dtb, &indLen, indexArr);
	} else {
		load_index(ind, indexArr, indLen);
	}

	fclose(dtb);
	fclose(ind);
}

void index_database(FILE *ind, char indexFile[MAX_CHARS], FILE *dtb, 
					int *indLen, ingredientPos *indexArr)
{
	/* 
	 * Only reached if no index file is currently present.
	 * Index file should be deleted after the database has been altered.
	 */
	char tempString[MAX_LINE_LEN];
	char *fgetsPtr;
	int position;
	int i;

	/* Create an index file */
	ind = fopen(indexFile, "w");

	/* Database is open. We check if it's empty. If not we skip the first descriptive line */
	fgetsPtr = fgets(tempString, MAX_LINE_LEN, dtb);
	if(fgetsPtr == NULL) {
		puts("The database is completely empty.");
		exit(EXIT_FAILURE);
	}

	/* We retrieve the lines in the database one by one */
	do
	{
		/* Get the position */
		position = ftell(dtb);
		/* Reads a line in the database and stores the pointer to check if it's the end of file */
		fgetsPtr = fgets(tempString, MAX_LINE_LEN, dtb);
		if(fgetsPtr == NULL)
			break;

		/* Keeps the information about the position and name in the program to sort it */
		sscanf(tempString, " %[^0-9]", indexArr[*indLen].ingredientName);
		indexArr[*indLen].position = position;

		*indLen += 1;
	} while (fgetsPtr != NULL);

	for(i = 0; i < *indLen; i++) 
		fprintf(ind, "%d: %s\n", indexArr[i].position, indexArr[i].ingredientName);
	
	/* Closing the index file for writing, and reopen for the rest of the functions to read it */
	freopen(indexFile, "r", ind);
}

void load_index(FILE *ind, ingredientPos *indexArr, int indLen)
{
	int posLen = 10, i = 0;
	char *fgetsPtr;
	/* Name of the ingredient + 10 for the position */
	char tempString[MAX_CHARS + posLen];

	do
	{
		fgetsPtr = fgets(tempString, MAX_CHARS + posLen, ind);
		if (fgetsPtr == NULL)
			break;

		sscanf(tempString, " %ld : %[^\0]", &indexArr[i].position, indexArr[i].ingredientName);

		i++;

	} while(fgetsPtr != NULL);
}

/*
nutrition load_ingredient(char *ingredient, int kiloJoule, float protein)
{
	nutrition result;
	strcpy(result.ingredient, ingredient);
	result.kiloJoule = kiloJoule;
	result.protein = protein;

	return result;
}*/