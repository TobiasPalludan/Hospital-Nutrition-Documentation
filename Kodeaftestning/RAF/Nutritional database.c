#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 15
#define DATABASE 10

typedef struct nutrition 
{
	char  ingredient[MAX_CHARS];
	int   kiloJoule;
	float protein;
} nutrition;

nutrition load_ingredient(char *ingredient, int kiloJoule, float protein)
{
	nutrition result;
	strcpy(result.ingredient, ingredient);
	result.kiloJoule = kiloJoule;
	result.protein = protein;

	return result;
}

int main(void)
{
	char ingredient;
	char filename[] = "Nutritional database.txt";
	int len = 0;
	int i, j;
	person ID[DATABASE];
	int position[DATABASE][1];

	printf("Enter the name of the ingredient that you want to retrieve information about: ");
	scanf(" %s", &patient);
	
	FILE *ifp;
	ifp = fopen(filename, "w+");

	for (i = 0; i < DATABASE; i++)
	{
		len = ftell(ifp);
		fprintf(ifp, "%s\t%s\t%d\n",
				ID[i].firstName, ID[i].lastName, ID[i].yearBorn);
		
		for (j = 0; j < 1; j++)
		{
			position[i][j] = len;
			printf("position[%d][%d] = %d\n", i, j, len);
		}
	}

	fseek(ifp, position[1][0], SEEK_SET);

	fclose(ifp);

	return 0;
}