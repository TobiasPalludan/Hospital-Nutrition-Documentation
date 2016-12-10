#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 50
#define MAX_CHARS 25
#define DATABASE_DEPTH 15
#define MAX_INDEX 100


/* Structs */
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

typedef struct ingredient
{
    char ingredient[MAX_CHARS];
} ingredient;

/* Prototypes */
ingredientPos initialise_nutritional_database(int *p_counter);
void index_database(FILE *dtb, int *indLen, ingredientPos *indexArr);
//nutrition load_ingredient(char *ingredient, int kiloJoule, float protein);
void load_index(FILE *ind, ingredientPos *indexArr, int indLen);
void ingredient_prompt(int tempCounter, ingredientPos indexArr[MAX_INDEX]);
void search(ingredient a, ingredientPos b);

int main(void)
{
	int *p_counter;
	int tempCounter;
	p_counter = &tempCounter;

	ingredientPos indexArr[MAX_INDEX];

	initialise_nutritional_database(p_counter);
	/* Ask for ingredient */
	ingredient_prompt(tempCounter, indexArr);
	//retrieveIngredients();

	return 0;
}

ingredientPos initialise_nutritional_database(int *p_counter) {
	/* Variable initialisation */
	char ingredient[MAX_CHARS];
	char dataFile[] = "Nutritional_database.txt";
	int len = 0, indLen = 0;
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
	index_database(dtb, &indLen, indexArr);

	fclose(dtb);
	free(indexArr);

	return *indexArr;
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

void ingredient_prompt(int tempCounter, ingredientPos indexArr[MAX_INDEX]){
	int i = 0, j = 0, counter = 0;
    char tempString[MAX_CHARS];
    ingredient foodArr[MAX_LINE_LEN];

    printf("Scan your ingredients. (Type 'Exit' to stop):\n");

    do
    {
        scanf(" %s", tempString);
        strcpy(foodArr[i].ingredient, tempString);
        i++;
        counter++;

        if (strcmp(tempString, "Exit") == 0)
            counter--;
        
    } while (strcmp(tempString, "Exit") != 0);

	printf("\nPrinted:\n");

	for (i = 0; i < counter; i++)
	{
		printf("%s\n", foodArr[i].ingredient);
	}

	for (i = 0; i < counter; i++)
	{
		for (j = 0; j < tempCounter; j++)
		{
			if (strstr(indexArr[j].ingredientName, foodArr[i].ingredient))
			{
				printf("%s\n", indexArr[j].ingredientName);
			}
		}
	}
}


void search(ingredient a, ingredientPos b)
{
	if (strstr(b.ingredientName, a.ingredient))
	{
		printf("%s\n", b.ingredientName);
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