#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 50
#define MAX_CHARS 25
#define DATABASE_DEPTH 15
#define MAX_INDEX 100


/* Structs */
typedef struct nutrition 
{
	char  dish[MAX_CHARS];
	char  ingredient[MAX_CHARS];
	int   kiloJoule;
	float protein;
} nutrition;

typedef struct ingredientPos
{
	char ingredientName[MAX_CHARS];
	long int position;
} ingredientPos;

typedef struct searchTerm
{
    char ingredientName[MAX_CHARS];
    long int position;
} searchTerm;

/* Prototypes */
ingredientPos* initialise_nutritional_database(int *indLen);
void index_database(FILE *dtb, int *indLen, ingredientPos *indexArr);
void load_index(FILE *ind, ingredientPos *indexArr, int indLen);
nutrition* ingredient_prompt(int indLen, ingredientPos indexArr[MAX_INDEX]);
void stringarrToLowercase(char *stringArr);

int main(void)
{
	int indLen = 0;

	ingredientPos *indexArr;

	indexArr = initialise_nutritional_database(&indLen);
	/* Ask for ingredient */
	ingredient_prompt(indLen, indexArr);
	//retrieveIngredients();
	free(indexArr);

	return 0;
}

ingredientPos* initialise_nutritional_database(int *indLen) {
	/* Variable initialisation */
	char dataFile[] = "Nutritional_database.txt";
	ingredientPos *indexArr = malloc(DATABASE_DEPTH * sizeof(ingredientPos));
	FILE *dtb;

	/* Open the database file and check if open */
	dtb = fopen(dataFile, "r+");
	if(dtb == NULL)
	{
		printf("No database with name \"%s\" exists!\n", dataFile);
		exit(EXIT_FAILURE);
	}

	/* Index the database */
	index_database(dtb, indLen, indexArr);
	fclose(dtb);

	return indexArr;
}

void index_database(FILE *dtb, int *indLen, ingredientPos *indexArr)
{
	/* 
	 * Only reached if no index file is currently present.
	 * Index file should be deleted after the database has been altered.
	 */
	char tempString[MAX_LINE_LEN];
	char *fgetsPtr;
	int position;
	int i;

	puts("Loading index...");

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
		printf("%d: %s\n", indexArr[i].position, indexArr[i].ingredientName);
}

nutrition *ingredient_prompt(int indLen, ingredientPos indexArr[MAX_INDEX])
{
	int i = 0, j = 0, l = 0, counter = 0;
	int searchTermCounter = 0;
	double multiplier = 0;
	float protein = 0, kiloJoule = 0;
    char tempString[MAX_CHARS];
	char dataFile[] = "Nutritional_database.txt";
    searchTerm foodArr[MAX_LINE_LEN];
	nutrition *load_dish = malloc(100 * sizeof(nutrition));
	nutrition *load_ingredient = malloc(100 * sizeof(nutrition));

	FILE *ifp;

	/* Opens the file to eads the database and recieve the different information */
	ifp = fopen(dataFile, "r");
	while (!feof(ifp))
	{
		fscanf(ifp, " %[^0-9] %d %f %*f", load_ingredient[i].ingredient, &load_ingredient[i].kiloJoule, &load_ingredient[i].protein);
		i++;
		counter++;
	}
	/* A prompt that asks for the dish the user is making */
	i = 0;
	printf("What dish do you want to make?\n");
	scanf(" %[A-z, ]", load_dish[i].dish);

    printf("Scan your ingredients. (Type 'Exit' to stop):\n");

    do
    {
	/*  
	 *  Scan the ingredients you are using.
	 *  Does not matter if you are using uppercase or lowercase
	 */
        scanf(" %s", tempString);
        strcpy(foodArr[i].ingredientName, tempString);
        i++;
        searchTermCounter++;

        if (strcmp(tempString, "Exit") == 0)
            searchTermCounter--;
        
    } while (strcmp(tempString, "Exit") != 0);

	/* 
	 * These forloops converts the tempString and ingredient names in the index
	 * to lowercase. That is why it does not matter if you are using uppercase
	 * or lowercase in the scanf above.
	 */

	for(i = 0; i < searchTermCounter; i++)
	{
		stringarrToLowercase(foodArr[i].ingredientName);
	}
	for(i = 0; i < indLen; i++)
	{
		stringarrToLowercase(indexArr[i].ingredientName);
	}
	printf("\n");

	/* These forloops searches the input in the index */

	for (i = 0; i < searchTermCounter; i++)
	{
		ingredientPos searchArr[5];
		int noHits = 0;
		for (j = 0; j < indLen; j++)
		{
			/*
			 * This if statement uses needle and the haystack.
			 * it searches for a word in another word.
			 */ 
			if (strstr(indexArr[j].ingredientName, foodArr[i].ingredientName) != 0)
			{
				strcpy(searchArr[noHits].ingredientName, indexArr[j].ingredientName);
				searchArr[noHits].position = indexArr[j].position;
				noHits++;

				printf("%s\n", indexArr[j].ingredientName);
				foodArr[i].position = indexArr[j].position;

				printf("How much did you eat of this (in grams)?\n");
				scanf(" %lf", &multiplier);
				printf("\n");

				/* Passes to tempoary values */
				kiloJoule += load_ingredient[l].kiloJoule * (multiplier / 100);
				protein += load_ingredient[l].protein * (multiplier / 100);
				l++;
			}
		}
		if (noHits > 1)
		{
			for (int i = 0; i < noHits; i++)
			{
				printf("%d %s\n", i, searchArr[i].ingredientName);
			}

		}
	}
	/* passes the values to stuct */
	i = 0;
	load_dish[i].kiloJoule = kiloJoule;
	load_dish[i].protein = protein;
	printf("Meal served: %s\nkJ: %d\nProtein: %.2f\n", 
			load_dish[i].dish, load_dish[i].kiloJoule, load_dish[i].protein);

	return load_dish;
}

void stringarrToLowercase(char *string)
{
	for(int i = 0; i < strlen(string); i++)
	{
		string[i] = tolower(string[i]);
	}
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