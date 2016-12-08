#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 50
#define MAX_CHARS 25
#define DATABASE 10

typedef struct nutrition 
{
	char  ingredient[MAX_CHARS];
	int   kiloJoule;
	float protein;
} nutrition;

/* Prototyper */
void indexDatabase(FILE *ind, char indexFile[MAX_CHARS], FILE *dtb);
nutrition load_ingredient(char *ingredient, int kiloJoule, float protein);

int main(void)
{
	/* Variable initialisation */
	char *ingredient;
	char dataFile[] = "ANutritional_database.txt";
	char indexFile[] = "Nutritional_index.txt";
	int len = 0;
	int i, j;
	int position[DATABASE][1];
	FILE *dtb, *ind;

	/* Open the database file and check if open */
	dtb = fopen(dataFile, "r+");
	if(dtb == NULL)
	{
		puts("Could not open file, and could not make a new. Pointer to database is lost.");
		exit(EXIT_FAILURE);
	}

	/* Open the index file, or index the database if no file is present */
	ind = fopen(indexFile, "r");
	if(ind == NULL)
	{
		puts("Could not find index file. Creating one...");
		indexDatabase(ind, indexFile, dtb);
	}
	
	//loadIndex(ind);


	/* Ask for ingredient */
	printf("Enter the name of the ingredient that you want to retrieve information about: ");
	scanf(" %s", &ingredient);
	
	
	/* Pull the data from the database */
	fclose(dtb);
	fclose(ind);

	return 0;
}

void indexDatabase(FILE *ind, char indexFile[MAX_CHARS], FILE *dtb)
{
	/* 
	 * Only reached if no index file is currently present.
	 * Index file should be deleted after the database has been altered.
	 */
	char tempString[MAX_LINE_LEN];
	char *fgetsPtr;
	int i;

	/* Create an index file */
	ind = fopen(indexFile, "w");

	/* Database is open. We check if it's empty. If not we skip the first descriptive line */
	fgetsPtr = fgets(tempString, MAX_LINE_LEN, dtb);
	if(fgetsPtr == NULL) {
		puts("The database is completely empty.")
		exit(EXIT_FAILURE);
	}

	/* We retrieve the lines in the database one by one, and work on those */
	do 
	{
		fgetsPtr = fgets(tempString, MAX_LINE_LEN, dtb);

	} while (fgetsPtr != NULL)
}

nutrition load_ingredient(char *ingredient, int kiloJoule, float protein)
{
	nutrition result;
	strcpy(result.ingredient, ingredient);
	result.kiloJoule = kiloJoule;
	result.protein = protein;

	return result;
}