#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#define DEPARTMENT_SIZE 15
#define NAME_SIZE 30
#define ALLERGY_SIZE 50
#define PREFERENCES_SIZE 100
#define ILLNESS_SIZE 100
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
	char illness[ILLNESS_SIZE];
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
	char illness[ILLNESS_SIZE];
	char allergy[ALLERGY_SIZE];
}condition;

void add_food_intake(foodIntake intake);
void add_person(personInfo person);
void add_condition_log(condition conditionLog);
void make_patient_folder(char *string);
void make_folder(personInfo person);
void save_in_file(FILE *filePtr, char string[], char fileName[]);
void update_index_file(personInfo person);
int find_index(FILE *filePtr, char fileName[]);

int main(void)
{
	make_patient_folder(FILE_PATH);/*Maybe move this to either add_person() function, or the main of the  */

	/* remove this when fucntions for adding real patients is there*/
	personInfo Casper = { 3, "afdeling 1", 1110954441, "Casper", "graes", "feber"};
	foodIntake feedCasper = { 3, "18:18", "Kartofler", "kartofler", 2000, 75 };
	condition CasperErSygLog = { 3, "18:18", 70, 192, 23.1, 2400, 41.7, "feber", "graes" };
	add_person(Casper);
	add_food_intake(feedCasper);
	add_condition_log(CasperErSygLog);

	return 0;
}

void add_person(personInfo person)/*Function for adding a person the the system */
{
	FILE *personFilePtr;

	update_index_file(person);
	make_folder(person);

	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE];

	sprintf(fileName, "%s/%d/%d ID.txt", FILE_PATH, person.id, person.id); /*Creates file name from ID of the person*/
	sprintf(log, "%d, %s, %d, %s, %s\n", person.id, person.department, person.cprNumber, person.name, person.allergy);/*Pulls log indformation from stuct*/
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
	sprintf(log, "%d %s %d %d %.2lf %d %.2lf %s %s\n", conditionLog.id, conditionLog.timeStamp, conditionLog.weight, conditionLog.height, conditionLog.bmi, conditionLog.bmr, conditionLog.temperature, conditionLog.illness, conditionLog.allergy); /*Creates file name from ID of the person*/
	save_in_file(condtionFilePtr, log, fileName);
}

void save_in_file(FILE *filePtr, char string[], char fileName[]) /* Saves string in a file, or makes the file if its not already there. Takes filePointer, a string, and a fileName */
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

void make_patient_folder(char *string) /* Creates the main folder to store all patient subfolders */
{
	if (_mkdir(string) == 0)
	{
		printf("made folder: %s\n", string);
	}
	else printf("Folder already exists\n");
}

void make_folder(personInfo person) /* Makes patient subfolders */
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

void update_index_file(personInfo person) /* Updates the index file that tracks all the patients*/
{
	FILE *indexFilePtr;
	char indexLog[NAME_SIZE],
		 fileName[NAME_SIZE];

	sprintf(fileName, "%s%s", FILE_PATH, INDEX_FILE_NAME);
	int index = find_index(indexFilePtr, fileName);
	sprintf(indexLog, "%d %s %s\n", index, person.name, person.illness);

	save_in_file(indexFilePtr, indexLog, fileName);
}

int find_index(FILE *filePtr, char fileName[])
{
	filePtr = fopen(fileName, "r");
	if (filePtr != NULL)
	{
		int index = 0, c = 0;
		char name[NAME_SIZE];
		char illness[NAME_SIZE];

		while (!feof(filePtr))
		{
			fscanf(filePtr, " %d %[A-z] %[A-z]\n", &index, name, illness);
			printf("%d \n", index);
		}
		fclose(filePtr);
		return index + 1;
	}
	else {
		fclose(filePtr);
		return 1;
	}
}