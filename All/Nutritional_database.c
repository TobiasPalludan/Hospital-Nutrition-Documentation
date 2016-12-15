#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Nutritional_database.h"

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

	indexPos *indexArr;
	indexArr = index_database(&indLen, dtb);

	/* Ask for ingredient */
	meal = ingredient_prompt(indLen, indexArr, dtb);
	printf("Dish name: %s \nKiloJoules: %d kJ \nProtein: %g g \nWeight: %g g\nNo: %d ingredients\n",
		   meal[0].ingredient, meal[0].kiloJoule, meal[0].protein, meal[0].weight, meal[0].noIngredients);

	/* Free all dynamically allocated arrays, and close database */
	free(indexArr);
	free(meal);
	fclose(dtb);

	return 0;
}

/*
 * Param indLen is the length of the index array. Returned by the function as a parameter.
 * Param dtb is the pointer to the database file.

 * Return value is the index array containing name of the ingredient and it's position in the
 * database.
 */
indexPos* index_database(int *indLen, FILE *dtb)
{
	/*
	 * Only to be called once per runtime. Will load the index file,
	 * and return a pointer through parameter.
	 */
	indexPos *indexArr = malloc(DATABASE_DEPTH * sizeof(indexPos));
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

	printf("Index loaded with %d elements.\n", *indLen);

	return indexArr;
}

/*
 * Param indlen is the length of the index array. This value is from function index_database.
 * Param indexArr is the loaded array, from the index_database function.
 * Param dtb is the pointer to the database file.
 *
 * Return value is a struct with all necesarry information of the dish that was created.
 */
nutrition* ingredient_prompt(int indLen, indexPos indexArr[MAX_INDEX], FILE *dtb)
{
	int i = 0, j = 0, temp;
	int noSearchTerms = 0;
	double weight[10];
    searchTerm foodArr[MAX_LINE_LEN];
	nutrition *dish = malloc(100 * sizeof(nutrition));

	/* A prompt that asks for the dish the user is making */
	i = 0;
	printf("\nWhat dish do you want to make?\n");
	scanf(" %[A-z, ]", dish[0].ingredient);
	dish[0].kiloJoule  = 0;
	dish[0].protein  = 0;
	dish[0].weight = 0;
	i++;
	noSearchTerms++;

    puts("\nScan your ingredients and amount in grams. (Type 'Exit' or 'e' to stop):");
    puts("Example format: \"food 123\"");

	/*
	 *  Scan the ingredients you are using.
	 *  Does not matter if you are using uppercase or lowercase
	 */
    do
    {

        scanf(" %s", &foodArr[i].ingredientName);
        stringarrToLowercase(foodArr[i].ingredientName);

        if (strcmp(foodArr[i].ingredientName, "exit") == 0 || strcmp(foodArr[i].ingredientName, "e") == 0)
            break;

        scanf(" %lf", &weight[i]);

        noSearchTerms++;
        i++;
    } while (i < MAX_INGREDIENTS);

	/*
	 * These forloops converts the tempString and ingredient names in the index
	 * to lowercase. That is why it does not matter if you are using uppercase
	 * or lowercase in the scanf above.
	 */

	for(i = 0; i < indLen; i++)
	{
		stringarrToLowercase(indexArr[i].ingredientName);
	}
	printf("\n");

	/* These forloops searches the input in the index. Each iteration is one ingredient */
	find_database_value(noSearchTerms, indLen, indexArr, dtb, foodArr, dish, weight);

	return dish;
}

nutrition* find_database_value(int noSearchTerms, int indLen, indexPos indexArr[MAX_INDEX],
							   FILE *dtb, searchTerm foodArr[MAX_LINE_LEN], nutrition* dish, double weight[])
{
	int i, j, temp;
	char tempLine[MAX_LINE_LEN];
	for (i = 1; i < noSearchTerms; i++)
	{
		searchTerm searchArr[10];
		int noHits = 0;
		for (j = 0; j < indLen; j++)
		{
			/*
			 * Searches for all instances of the ingredient in the search array.
			 */
			if (strstr(indexArr[j].ingredientName, foodArr[i].ingredientName) != 0)
			{
				strcpy(searchArr[noHits].ingredientName, indexArr[j].ingredientName);
				searchArr[noHits].position = indexArr[j].position; // Saves position of the searchterm
				searchArr[noHits].weight = weight[i]; // Adds weight of the ingredient
				noHits++;
			}
		}

		temp = 0;
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

		/* Retrieve data from database. Feed it to the dish struct. */
		for(int j = 0; j < noHits; j++)
		{
			if(temp == j)
			{
				printf("You choose: %s\n\n", searchArr[j].ingredientName);

				if(!fseek(dtb, searchArr[j].position, SEEK_SET))
					fgets(tempLine, MAX_LINE_LEN, dtb);
				else
					exit(EXIT_FAILURE);

				sscanf(tempLine, " %[^0-9] %d %lf %*lf", dish[i].ingredient, &dish[i].kiloJoule, &dish[i].protein);
				dish[i].weight = weight[i];

				dish[i].kiloJoule  = (dish[i].weight / 100) * dish[i].kiloJoule;
				dish[0].kiloJoule += dish[i].kiloJoule;

				dish[i].protein   += (dish[i].weight / 100) * dish[i].protein;
				dish[i].protein    = dish[i].protein;

				dish[0].weight	  +=  dish[i].weight;
				dish[0].noIngredients = noSearchTerms - 1;
			}
		}
	}

	return dish;
}

void stringarrToLowercase(char *string)
{
	for(int i = 0; i < strlen(string); i++)
	{
		string[i] = tolower(string[i]);
	}
}
