#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 25
#define MAX_INGREDIENTS 50
#define MAX_LINE 50

typedef struct nutrition 
{
	char  ingredient[MAX_CHARS];
	int   kiloJoule;
	float protein;
} nutrition;

typedef struct ingredient
{
    char ingredient[MAX_CHARS];
} ingredient;

/* Prototypes */
void retrieveIngredients();
nutrition load_ingredient(char *ingredient, int kiloJoule, float protein);

int main(void)
{
    retrieveIngredients();

    return 0;
}

void retrieveIngredients()
{
    int i = 0, counter = 0;
    char tempString[MAX_CHARS];
    ingredient food[MAX_INGREDIENTS];

    printf("Scan your ingredients. (Type 'Exit' to exit):\n");

    do
    {
        scanf(" %s", tempString);
        strcpy(food[i].ingredient, tempString);
        i++;
        counter++;

        if (strcmp(tempString, "Exit") == 0)
        {
            counter--;
        }
        
    } while (strcmp(tempString, "Exit") != 0);

    printf("\nThe ingredients printed:\n");
    for (i = 0; i < counter; i++){
        printf("%s\n", food[i].ingredient); 
    }

/*
    printf("How many ingredients do you want to input: ");
    scanf(" %d", &temp);
*/

/*
    for (i = 0; i < temp; i++)    {
        scanf(" %s %d %f", &ingredient, &kiloJoule, &protein);
        load_ingredient(&ingredient, kiloJoule, protein);
    }

    for (i = 0; i < temp; i++)
    {
        printf("%s %d %f\n", load_ingredient[i].ingredient, load_ingredient[i].kiloJoule, load_ingredient[i].protein);
    }
*/

    
}

/*
nutrition load_ingredient(char *ingredient, int kiloJoule, float protein)
{
	nutrition result;
	strcpy(result.ingredient, ingredient);
	result.kiloJoule = kiloJoule;
	result.protein = protein;

	return result;
}
*/