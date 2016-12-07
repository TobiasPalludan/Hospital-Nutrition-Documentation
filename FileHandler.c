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
#define FILE_NAME_SIZE 20

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
void add_person(personInfo person);

int main(void)
{
	personInfo Casper = { 3, "Uranus", 666, "Casper", 54, "Kris" };
	foodIntake feedCasper = { "18:18", "TUANS MOR", "White sauce", 9001, 9 };
	add_food_intake(feedCasper, Casper);
	add_person(Casper);
	return 0;
}

void add_food_intake(foodIntake intake, personInfo person)
{
	
	FILE *foodFilePtr;

	char fileName[FILE_NAME_SIZE];
	sprintf(fileName, "%d IntakeLog.txt", person.id); /*Creates file name from ID of the person*/

	if (foodFilePtr != NULL)
	{
		foodFilePtr = fopen(fileName, "a");
		fprintf(foodFilePtr, "%s, %s, %s, %d, %d\n", intake.timeStamp, intake.dishName, intake.indgredients, intake.totalKJ, intake.percentageEaten);
	}
	else
	{
		printf("File not open");
		foodFilePtr = fopen(fileName, "w");
		fprintf(foodFilePtr, "%s, %s, %s, %d, %d\n", intake.timeStamp, intake.dishName, intake.indgredients, intake.totalKJ, intake.percentageEaten);
	}
	fclose(foodFilePtr);
}

void add_person(personInfo person)
{
	FILE *personFilePtr;

	char fileName[FILE_NAME_SIZE];
	sprintf(fileName, "ID %d.txt", person.id); /*Creates file name from ID of the person*/

	if (personFilePtr != NULL)
	{
		personFilePtr = fopen(fileName, "a");
		fprintf(personFilePtr, "%d, %s, %d, %s, %d, %s\n", person.id, person.department, person.cprNumber, person.name, person.height, person.allergy);
	}
	else
	{
		personFilePtr = fopen(fileName, "w");
		fprintf(personFilePtr, "%d, %s, %d, %s, %d, %s\n", person.id, person.department, person.cprNumber, person.name, person.height, person.allergy);
	}

	fclose(personFilePtr);

}