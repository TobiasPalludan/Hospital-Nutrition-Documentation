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

#define FILE_PATH "patients/"
#define INDEX_FILE_NAME "PatientIndex.txt"


typedef struct personInfo 
{
	int id;
	char department[DEPARTMENT_SIZE];
	int cprNumber;
	char name[NAME_SIZE];
	char allergy[ALLERGY_SIZE];
	/*char preferences[PREFERENCES_SIZE];*/
}personInfo;

typedef struct foodIntake 
{
	int id;
	char timeStamp[TIME_STAMP_SIZE];
	char dishName[DISH_NAME_SIZE];
	char indgredients[INGREDIENTS_SIZE];
	int totalKJ;
	int percentageEaten;
}foodIntake;

typedef struct condition 
{
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
void make_patient_folder(char *string);
void make_folder(personInfo person);
void save_in_file(FILE *filePtr, char string[], char fileName[]);
void update_index_file(personInfo person);


int main(void)
{
	make_patient_folder(FILE_PATH);

	/* remove this when fucntions for adding real patients is there*/
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

	update_index_file(person);
	make_folder(person);

	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE];

	sprintf(fileName, "%s/%d/%d ID.txt", FILE_PATH, person.id, person.id); /*Creates file name from ID of the person*/
	sprintf(log, "%d, %s, %d, %s, %s\n", person.id, person.department, person.cprNumber, person.name, person.allergy);
	save_in_file(personFilePtr, log, fileName);
}

void add_food_intake(foodIntake intake)
{
	FILE *foodFilePtr;
	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE];
	sprintf(fileName, "%s/%d/%d IntakeLog.txt", FILE_PATH, intake.id, intake.id); /*Creates file name from ID of the person*/
	sprintf(log, "%s, %s, %s, %d, %d\n", intake.timeStamp, intake.dishName, intake.indgredients, intake.totalKJ, intake.percentageEaten);
	save_in_file(foodFilePtr, log, fileName);
}

void add_condition_log(condition conditionLog)
{
	FILE *condtionFilePtr;
	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE];
	sprintf(fileName, "%s/%d/%d condition.txt", FILE_PATH, conditionLog.id, conditionLog.id); /*Creates file name from ID of the person*/
	sprintf(log, "%d %s %d %d %lf %d %.2lf %s %s\n", conditionLog.id, conditionLog.timeStamp, conditionLog.weight, conditionLog.height, conditionLog.bmi, conditionLog.bmr, conditionLog.temperature, conditionLog.ilness, conditionLog.allergy); /*Creates file name from ID of the person*/
	save_in_file(condtionFilePtr, log, fileName);
}

void save_in_file(FILE *filePtr, char string[], char fileName[])
{
	if (filePtr != NULL)
	{
		filePtr = fopen(fileName, "a");
		fprintf(filePtr, string);
	} else
	{
		filePtr = fopen(fileName, "w");
		fprintf(filePtr, string);
	}
	fclose(filePtr);
}

void make_patient_folder(char *string)
{
	if (_mkdir(string) == 0)
	{
		printf("made folder: %s\n", string);
	}
	else printf("Folder already exists\n");
}

void make_folder(personInfo person)
{
	char path[FILE_NAME_SIZE] = { FILE_PATH },
		 idPath[FILE_NAME_SIZE];

	itoa(person.id, idPath, 10);
	strcat(path, idPath);

	if (_mkdir(path)==0)
	{
		printf("made folder: %d\n", person.id);
	} else printf("Folder already exists\n");
}

void update_index_file(personInfo person)
{
	FILE *indexFilePtr;
	char indexInfo[NAME_SIZE],
		 fileName[NAME_SIZE] = { FILE_PATH };

	sprintf(fileName, "%s%s", fileName, INDEX_FILE_NAME);
	sprintf(indexInfo, "%d %s %s\n", person.id, person.name, person.allergy);

	save_in_file(indexFilePtr, indexInfo, fileName);
}