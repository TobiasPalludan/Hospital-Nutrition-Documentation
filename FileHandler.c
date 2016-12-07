#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#define DEPARTMENT_SIZE 15
#define NAME_SIZE 30
#define ALLERGY_SIZE 50
#define PREFERENCES_SIZE 100
#define ILNESS_SIZE 100
#define TIME_STAMP_SIZE 13
#define DISH_NAME_SIZE 20
#define INGREDIENTS_SIZE 100
#define FILE_NAME_SIZE 20
#define LOG_FILE_SIZE 100

typedef struct personInfo {
	int id;
	char department[DEPARTMENT_SIZE];
	int cprNumber;
	char name[NAME_SIZE];
	char allergy[ALLERGY_SIZE];
	/*char preferences[PREFERENCES_SIZE];*/
}personInfo;

typedef struct foodIntake {
	int id;
	char timeStamp[TIME_STAMP_SIZE];
	char dishName[DISH_NAME_SIZE];
	char indgredients[INGREDIENTS_SIZE];
	int totalKJ;
	int percentageEaten;
}foodIntake;

typedef struct condition {
	int id;
	char timeStamp[TIME_STAMP_SIZE];
	int weight;
	int height;
	double bmi;
	int bmr;
	double temperature;
	char ilness[ILNESS_SIZE];
	char allergy[ALLERGY_SIZE];
}condition;

void add_food_intake(foodIntake intake);
void add_person(personInfo person);
void add_condition_log(condition conditionLog);
void make_folder(personInfo person);
void save_in_file(FILE *filePtr, char string[], char fileName[]);


int main(void)
{
	if (_mkdir("patients") == 0)
	{
		printf("made folder: patients\n");
	}
	else printf("Folder already exists\n");
	personInfo Casper = { 1, "Uranus", 666, "Casper", "Kris" };
	foodIntake feedCasper = { 1, "18:18", "TUANS MOR", "White sauce", 666, 9 };
	condition CasperErSygLog = { 1, "18:18", 17, 25, -0.15, 666, 99.9, "Kronisk diaré", "Stadig Kris" };
	add_person(Casper);
	add_food_intake(feedCasper);
	add_condition_log(CasperErSygLog);
	return 0;
}

void add_person(personInfo person)
{
	FILE *personFilePtr;
	make_folder(person);
	char fileName[FILE_NAME_SIZE];
	char log[LOG_FILE_SIZE];
	sprintf(fileName, "patients/%d/%d ID.txt", person.id, person.id); /*Creates file name from ID of the person*/
	sprintf(log, "%d, %s, %d, %s, %s\n", person.id, person.department, person.cprNumber, person.name, person.allergy);
	save_in_file(personFilePtr, log, fileName);
}

void add_food_intake(foodIntake intake)
{
	FILE *foodFilePtr;
	char fileName[FILE_NAME_SIZE];
	char log[LOG_FILE_SIZE];
	sprintf(fileName, "patients/%d/%d IntakeLog.txt", intake.id, intake.id); /*Creates file name from ID of the person*/
	sprintf(log, "%s, %s, %s, %d, %d\n", intake.timeStamp, intake.dishName, intake.indgredients, intake.totalKJ, intake.percentageEaten);
	save_in_file(foodFilePtr, log, fileName);
}

void add_condition_log(condition conditionLog)
{
	FILE *condtionFilePtr;
	char fileName[FILE_NAME_SIZE];
	char log[LOG_FILE_SIZE];
	sprintf(fileName, "patients/%d/%d condition.txt", conditionLog.id, conditionLog.id); /*Creates file name from ID of the person*/
	sprintf(log, "%d %s %d %d %lf %d %.2lf %s %s\n", conditionLog.id, conditionLog.timeStamp, conditionLog.weight, conditionLog.height, conditionLog.bmi, conditionLog.bmr, conditionLog.temperature, conditionLog.ilness, conditionLog.allergy); /*Creates file name from ID of the person*/
	save_in_file(condtionFilePtr, log, fileName);
}

void save_in_file(FILE *filePtr, char string[], char fileName[])
{
	if (filePtr != NULL)
	{
		filePtr = fopen(fileName, "a");
		fprintf(filePtr, string);
	}
	else
	{
		filePtr = fopen(fileName, "w");
		fprintf(filePtr, string);
	}
	fclose(filePtr);
}


void make_folder(personInfo person)
{
	char path[FILE_NAME_SIZE] = { "patients/" };
	char idPath[FILE_NAME_SIZE];
	itoa(person.id, idPath, 10);
	strcat(path, idPath);
	if (_mkdir(path)==0)
	{
		printf("made folder: %d\n", person.id);
	}
	else printf("Folder already exists\n");
}

/*
void add_person(personInfo person)
{
	FILE *personFilePtr;
	make_folder(person);
	char fileName[FILE_NAME_SIZE];
	sprintf(fileName, "%d/%d ID.txt", person.id, person.id);

	char log[LOG_FILE_SIZE];
	sprintf(log, "%d, %s, %d, %s, %s\n", person.id, person.department, person.cprNumber, person.name, person.allergy);

	if (personFilePtr != NULL)
	{
		personFilePtr = fopen(fileName, "a");
		fprintf(personFilePtr, log);
	}
	else
	{
		personFilePtr = fopen(fileName, "w");
		fprintf(personFilePtr, log);
	}
	fclose(personFilePtr);
}*/

/*void add_food_intake(foodIntake intake, personInfo person)
{
	FILE *foodFilePtr;
	char fileName[FILE_NAME_SIZE];
	sprintf(fileName, "%d/%d IntakeLog.txt", person.id, person.id); /*Creates file name from ID of the person*/
/*
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
}*/