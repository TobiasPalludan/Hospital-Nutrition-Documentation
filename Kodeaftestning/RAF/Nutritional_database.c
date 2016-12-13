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
	double protein;
	double weight;
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
    float weight;
} searchTerm;

/* Prototypes */
ingredientPos* initialise_nutritional_database(int *indLen, FILE *dtb);
void index_database(FILE *dtb, int *indLen, ingredientPos *indexArr);
void load_index(FILE *ind, ingredientPos *indexArr, int indLen);
nutrition* ingredient_prompt(int indLen, ingredientPos indexArr[MAX_INDEX], FILE *dtb);
void stringarrToLowercase(char *stringArr);

void search_db(int noSearchTerms, double weight[10], int indLen, ingredientPos indexArr[MAX_INDEX], searchTerm foodArr[MAX_LINE_LEN], nutrition *dish, FILE *dtb);


int main(void)
{
	int indLen = 0;
	nutrition *meal;
	char dataFile[] = "Nutritional_database.txt";
	FILE *dtb;

	/* Open the database file and check if open */
	dtb = fopen(dataFile, "r+");
	if(dtb == NULL)
	{
		printf("No database with name \"%s\" exists!\n", dataFile);
		exit(EXIT_FAILURE);
	}

	ingredientPos *indexArr;

	indexArr = initialise_nutritional_database(&indLen, dtb);

	/* Ask for ingredient */
	meal = ingredient_prompt(indLen, indexArr, dtb);


	/* Prints the meal */
	printf("Dish name: %s \nKilojoules: %d \nProtein: %g \nWeight: %g\n", 
		   meal[0].ingredient, meal[0].kiloJoule, meal[0].protein, meal[0].weight);

	free(indexArr);
	free(meal);
	fclose(dtb);

	return 0;
}

ingredientPos* initialise_nutritional_database(int *indLen, FILE *dtb) 
{
	/* Variable initialisation */
	ingredientPos *indexArr = malloc(DATABASE_DEPTH * sizeof(ingredientPos));

	/* Index the database */
	index_database(dtb, indLen, indexArr);

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
		printf("%ld: %s\n", indexArr[i].position, indexArr[i].ingredientName);
}

nutrition *ingredient_prompt(int indLen, ingredientPos indexArr[MAX_INDEX], FILE *dtb)
{
	int i = 0, j = 0, temp;
	int noSearchTerms = 0;
	double weight[10];
	searchTerm foodArr[MAX_LINE_LEN];
	nutrition *dish = malloc(100 * sizeof(nutrition));

	/* A prompt that asks for the dish the user is making */
	i = 0;
	printf("What dish do you want to make?\n");
	scanf(" %[A-z, ]", dish[0].ingredient);
	dish[0].kiloJoule =  0;
	dish[0].protein =  0;
	dish[0].weight = 0;
	i++;
	noSearchTerms++;

    printf("Scan your ingredients and the amount eaten in grams. (Type 'Exit' or 'e' to stop):\n");

    do
    {
	/*  
	 *  Scan the ingredients you are using.
	 *  Does not matter if you are using uppercase or lowercase
	 */
        scanf(" %s", &foodArr[i].ingredientName);

        if (strcmp(foodArr[i].ingredientName, "Exit") == 0 || strcmp(foodArr[i].ingredientName, "e") == 0)
            break;

        scanf(" %lf", &weight[i]);

        /* Tobias er sej */
        
        noSearchTerms++;
        i++;
    } while (strcmp(foodArr[i - 1].ingredientName, "Exit") != 0);

	/* 
	 * These forloops converts the tempString and ingredient names in the index
	 * to lowercase. That is why it does not matter if you are using uppercase
	 * or lowercase in the scanf above.
	 */

	for(i = 0; i < noSearchTerms; i++)
	{
		stringarrToLowercase(foodArr[i].ingredientName);
	}
	for(i = 0; i < indLen; i++)
	{
		stringarrToLowercase(indexArr[i].ingredientName);
	}
	printf("\n");

	/* These forloops searches the input in the index. Each iteration is one ingredient */
	search_db(noSearchTerms, weight, indLen, indexArr, foodArr, dish, dtb);

	return dish;
}

void stringarrToLowercase(char *string)
{
	for(int i = 0; i < strlen(string); i++)
	{
		string[i] = tolower(string[i]);
	}
}

void search_db(int noSearchTerms, double weight[10], int indLen, ingredientPos indexArr[MAX_INDEX], searchTerm foodArr[MAX_LINE_LEN], nutrition *dish, FILE *dtb)
{
	int i = 0, j = 0, noHits = 0, temp = 0;
    char tempLine[MAX_LINE_LEN];
    

	for (i = 1; i < noSearchTerms; i++)
	{
		searchTerm searchArr[5];
		for (j = 0; j < indLen; j++)
		{
			/*
			 * This if statement uses needle and the haystack.
			 * it searches for a word in another word.
			 */ 
			if (strstr(indexArr[j].ingredientName, foodArr[i].ingredientName) != 0)
			{
				strcpy(searchArr[noHits].ingredientName, indexArr[j].ingredientName);
				searchArr[noHits].position = indexArr[j].position; // Saves position of the searchterm
				searchArr[noHits].weight = weight[i]; // Adds weight of the ingredient
				noHits++;
			}
		}

		/* In case there is several cases under the same search term */
		if (noHits > 1)
		{
			printf("You searched for \"%s\". I found %d hits:\n", foodArr[i].ingredientName, noHits);
			for (int i = 0; i < noHits; i++)
			{
				printf("%d: %s\n", i, searchArr[i].ingredientName);
			}
			printf("Print which one you would like: ");
			scanf(" %d", &temp);
		}

		/* Assign the value that you asked for to the dish */
		for(j = 0; j < noHits; j++)
		{
			if(temp == j)
			{
				printf("You choose: %s\n", searchArr[j].ingredientName);
				puts("");
				
				if(!fseek(dtb, searchArr[j].position, SEEK_SET))
					fgets(tempLine, MAX_LINE_LEN, dtb);
				else
					exit(EXIT_FAILURE);

				sscanf(tempLine, " %[^0-9] %d %lf %*lf", dish[i].ingredient, &dish[i].kiloJoule, &dish[i].protein);
				dish[i].weight = weight[i];

				dish[0].kiloJoule += (dish[i].weight / 100) * dish[i].kiloJoule;
				dish[0].protein   += (dish[i].weight / 100) * dish[i].protein;
				dish[0].weight	  += dish[i].weight;
			}
		}
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