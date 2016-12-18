#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Nutritional_database.h"

/*
 * Function will read line by line in the database 
 * and store the information of the given line in [i]'d cell in index array.
 *
 * Input: Param indLen is the length of the index array. Returned by the function as a parameter.
 *        Param dtb is the pointer to the database file, which is created in the function "int main(void)".
 *
 * Output: Return value is the index array containing name of the ingredient and it's position in the
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
	/*Thereby we find the amount of line = amount of ingredients and its properties
	  aswell as the ingredients position in the database*/
	do
	{
		/* Get the position of the pointer*/
		position = ftell(dtb);
		/* Reads a line in the database and stores the pointer to check if it's the end of file */
		/*We read the line dtb is pointing at, then stores the read information in tempString*/
		fgetsPtr = fgets(tempString, MAX_LINE_LEN, dtb);
		/*If the pointer is at end of file, there is no more to read, and therefore pointer == NULL and we break*/
		if(fgetsPtr == NULL)
			break;

		/*Keeps the information about the position and name in the program to sort it*/
		/*We assign IndexArr[i].ingredientName to the string stored in tempString. Thereby IndexArr[i].ingredientName 
		  will contain information about the ingredient of the line which just got read*/
		sscanf(tempString, " %[^0-9]", indexArr[*indLen].ingredientName);

		/*We also store the position, which is used to acces the ingredient in the database file*/
		indexArr[*indLen].position = position;

    /*Increments indLen, so the info about next ingredient will be stored
      in the next cell of the array IndexArr[i].ingredientName*/
		*indLen += 1;
	} while (fgetsPtr != NULL);
  /*Serive info*/
	printf("Index loaded with %d elements.\n", *indLen);
  
  /*Returns array containing information about the ingredient
    and the position of it in the database file*/
	return indexArr;
}

/*
 * Function takes input from user about the dish and its ingredients. By calling find_database_value
 * we search for the ingredients in the database and thereby finds the ingredients properties. Next 
 * returns the information about the ingredients through pointers and stores the returned information 
 * from find_database_value in an array of structs called dish in ingredient_prompt which will be returned
 * as pointer in the function ingredient_prompt
 *
 * Input: Param indlen is the length of the index array. This value is from function index_database.
 *        Param indexArr is the loaded array, from the index_database function.
 *        Param dtb is the pointer to the database file.
 *
 * Output: Return value is a struct with all necesarry information of the dish that was created.
 */
nutrition* ingredient_prompt(int indLen, indexPos indexArr[MAX_INDEX], FILE *dtb)
{
	int i = 0, j = 0, temp;
	int noSearchTerms = 0;
	double weight[10];
         searchTerm foodArr[MAX_LINE_LEN];
         nutrition *dish = malloc(100 * sizeof(nutrition));

	/* A prompt that asks for the dish the user is making. */
	i = 0;
	printf("\nWhat dish do you want to make?\n");
	scanf(" %[A-z, ]", dish[0].ingredient);
	dish[0].kiloJoule  = 0;
	dish[0].protein  = 0;
	dish[0].fat = 0;
	dish[0].weight = 0;
	i++;
	/*noSearchTerms counts amount of input from user*/
	noSearchTerms++;

    puts("\nScan your ingredients and amount in grams. (Type 'Exit' or 'e' to stop):");
    puts("Example format: \"food 123\"");

	/*
	 *  Scan the ingredients you are using.
	 *  Does not matter if you are using uppercase or lowercase
	 */
    do
    {   
    	  /*Scans for ingredients and stores input in foodArr[i].ingredientName*/
        scanf(" %s", &foodArr[i].ingredientName);
        /*Convert input to lowecase*/
        stringarrToLowercase(foodArr[i].ingredientName);
        
        /*Checks if user wants to exit*/
        if (strcmp(foodArr[i].ingredientName, "exit") == 0 || strcmp(foodArr[i].ingredientName, "e") == 0)
            break;
        
        /*Scans for weight of the ingredient*/
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

	/* These forloops (those in find_database_value) searches the input in the index. Each iteration is one ingredient */
	/*This function changes the information stored in dish by the help of pointers*/
	find_database_value(noSearchTerms, indLen, indexArr, dtb, foodArr, dish, weight);

	return dish;
}
/*Searches the database for the ingredients entered by the user in ingredient_prompt
 and assigns new value about the ingredients to the values stored in dish by the help of pointers*/

/*Input: noSearchTerms is the amount of input from the user. indlen is the length of the index array. 
  indexArr is the loaded array, from the index_database function. FILE *dtb is the filepointer to the datebase file
  foodArr is the array which contains the ingredients. nutrition* dish is the pointer to the array where information
  about the dish is stored. weight is the array which holds information about the weight of each ingredient 

  Output: no return, but assigns new value to the values stored in dish by the help of pointers */
nutrition* find_database_value(int noSearchTerms, int indLen, indexPos indexArr[MAX_INDEX],
							   FILE *dtb, searchTerm foodArr[MAX_LINE_LEN], nutrition* dish, double weight[])
{
	int i, j, temp, noErrors = 0;
	char tempLine[MAX_LINE_LEN];
	for (i = 1; i < noSearchTerms; i++)/*for (i = 0; i < noSearchTerms-1; i++)*/
	{
		searchTerm searchArr[10];
		int noHits = 0;
		for (j = 0; j < indLen; j++)
		{
			/*
			 * Searches for all instances of the ingredient in the search array.
			 * If the ingredient is found the ingriendient, its position and weight
			 * gets copied into searchArr[noHits].
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
		/*If ingredient is in database*/
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
		/*If ingredient isnt in database*/
		else if (noHits == 0)
		{
			printf("Error! Ingredient %s could not be recognized. Trying to continue!\n\n", foodArr[i].ingredientName);
			noErrors++;
			continue;
		}

		/* Retrieve data from database. Assign it to the dish struct. */
		for(int j = 0; j < noHits; j++)
		{
			if(temp == j)
			{
				printf("You choose: %s\n\n", searchArr[j].ingredientName);

        /*Sets pointer to the position of the ingredient and reads the information on that line and stores it in tempLine*/
				if(!fseek(dtb, searchArr[j].position, SEEK_SET))
					fgets(tempLine, MAX_LINE_LEN, dtb);
				else
					exit(EXIT_FAILURE);
        
        /*Scans the string an assignt different part of the string to the dish struct*/
				sscanf(tempLine," %[^0-9] %d %lf %lf", dish[i].ingredient, &dish[i].kiloJoule, &dish[i].protein, &dish[i].fat);
				
				/*Stores the amount of protein, fat and kiloJoule aswell as weight for each ingredient in dish[i]. 
				  It also sums it all together and stores the values in dish[0]. Which then desribes how much
				  protein, fat and kiloJoule that is in the meal. */
				dish[i].weight = weight[i];

				dish[i].kiloJoule  = (dish[i].weight / 100) * dish[i].kiloJoule;
				dish[0].kiloJoule += dish[i].kiloJoule;

				dish[i].protein   = (dish[i].weight / 100) * dish[i].protein;
				dish[0].protein   += dish[i].protein;

				dish[i].fat = (dish[i].weight / 100) * dish[i].fat;
				dish[0].fat += dish[i].fat;

				dish[i].weight	  =  dish[i].weight;
				dish[0].noIngredients = noSearchTerms - 1 - noErrors;
			}
		}
	}
  /*SLETTES DA DISH BLIVER ÆNDRET GENNEM POINTER. LAV FUNKTION TIL VOID */
	return dish;
}
/*Converts the string into lowercase*/
/*Input: a string
  Output: the same string with only lowercase letters*/
void stringarrToLowercase(char *string)
{
	for(int i = 0; i < strlen(string); i++)
	{
		string[i] = tolower(string[i]);
	}
}
