#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEPARTMENT_SIZE 15
#define NAME_SIZE 30
#define ALLERGY_SIZE 50
#define PREFERENCES_SIZE 100
#define TIME_STAMP_SIZE 13
#define DISH_NAME_SIZE 20
#define INGREDIENTS_SIZE 100

typedef struct personInfo {
	int id;
	char department[DEPARTMENT_SIZE];
	int cprNumber;
	char name[NAME_SIZE];
	int height;
	char allergy[ALLERGY_SIZE];
	/*char preferences[PREFERENCES_SIZE];*/
}personInfo;

typedef struct foodIntake {
	char timeStamp[TIME_STAMP_SIZE];
	char dishName[DISH_NAME_SIZE];
	char indgredients[INGREDIENTS_SIZE];
	int totalKJ;
	int percentageEaten;
}foodIntake;

void add_food_intake(foodIntake intake, personInfo person);

int main(void)
{
	personInfo Casper = { 1, "Uranus", 666, "Casper", 54, "Kris" };
	foodIntake feedCasper = { "18:18", "TUANS MOR", "White sauce", 9001, 9 };
	add_food_intake(feedCasper, Casper);
	return 0;
}

void add_food_intake(foodIntake intake, personInfo person)
{
	
	FILE *foodFilePtr;
	//char foodFileString[] = "%d, %d", person->height, person->id;

	if (foodFilePtr != NULL)
	{
		foodFilePtr = fopen("testIndtake.txt", "a");
		fprintf(foodFilePtr, "%s, %s, %s, %d, %d\n", intake.timeStamp, intake.dishName, intake.indgredients, intake.totalKJ, intake.percentageEaten);
		//fprintf(foodFilePtr, "%d, %s, %d, %s, %d, %s\n", Casper.id, Casper.department, Casper.cprNumber, Casper.name, Casper.height, Casper.allergy);
	}
	else
	{
		printf("File not open");
		foodFilePtr = fopen("testIndtake.txt", "w+");
		fprintf(foodFilePtr, "%s, %s, %s, %d, %d\n", intake.timeStamp, intake.dishName, intake.indgredients, intake.totalKJ, intake.percentageEaten);
		//fprintf(foodFilePtr, "%d, %s, %d, %s, %d, %s\n", Casper.id, Casper.department, Casper.cprNumber, Casper.name, Casper.height, Casper.allergy);
	}


	fclose(foodFilePtr);
}