#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 25
#define MAX_INGREDIENTS 50
#define MAX_LINE 50

typedef struct ingredient
{
    char ingredient[MAX_CHARS];
} ingredient;

/* Prototypes */
void retrieveIngredients();
void searchFunction();

int main(void)
{
    ingredient_prompt();

    return 0;
}

void ingredient_prompt(){
	int i = 0, counter = 0;
    char tempString[MAX_CHARS];
    ingredient food[MAX_LINE_LEN];

    printf("Scan your ingredients. (Type 'Exit' to stop):\n");

    do
    {
        scanf(" %s", tempString);
        strcpy(food[i].ingredient, tempString);
        i++;
        counter++;

        if (strcmp(tempString, "Exit") == 0)
            counter--;
            
    } while (strcmp(tempString, "Exit") != 0);

	search(counter);
}

void search(int counter)
{
	int i = 0, j = 0;
    char *food;

	for(i = 0; i < counter; i++){
		for(j = 0; j < ; j++){
			if (food = strstr(food[i].ingredient, indexArr.ingredientName) != NULL){
				printf("%s\n", indexArr[j].ingredientName);
			}
		}
	}
}