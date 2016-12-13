#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "Lib.c"

#define DEPARTMENT_SIZE 15
#define NAME_SIZE 30
#define ALLERGY_SIZE 50
#define PREFERENCES_SIZE 100
#define ILLNESS_SIZE 100
#define TIME_STAMP_SIZE 18
#define DISH_NAME_SIZE 20
#define INGREDIENTS_SIZE 20
#define FILE_NAME_SIZE 25
#define LOG_FILE_SIZE 200
#define MAX_LOG_ENTRIES 10

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
	int weight;
	int height;
	double bmi;
	int bmr;
	double temperature;
}personInfo;

typedef struct nutritionIntake
{
	char  ingredient[INGREDIENTS_SIZE];
	int   kiloJoule;
	float protein;
	int	  amount;
} nutritionIntake;

typedef struct conditionHistory 
{
	int weight;
	int height;
	double bmi;
	int bmr;
	double temperature;
	char illness[ILLNESS_SIZE];
	char allergy[ALLERGY_SIZE];
}conditionHistory;

void add_person(personInfo *person);
void add_food_intake(personInfo person, nutritionIntake intake[]);
void add_condition_log(personInfo person, conditionHistory conditionLog);
void make_patient_folder(char *string);
void make_folder(personInfo person);
void save_in_file(FILE *filePtr, char string[], char fileName[]);
void update_index_file(personInfo *person);
int find_index(FILE *filePtr, char fileName[]);

int main(void)
{
	make_patient_folder(FILE_PATH);/*Maybe move this to either add_person() function, or the main of the  */

	/* remove this when fucntions for adding real patients is there*/
	personInfo Casper = { 3, "afdeling 1", 1110954441, "Casper", "graes", "feber"};

	nutritionIntake feedCasper[3] = {
										{"Kartofler med Sovs", 2000, 50.2, 150 },
										{"Kartofler", 1500, 10.2, 100},
										{"Sovs", 500, 40, 50 }
									};
	conditionHistory CasperErSygLog = {70, 192, 23.1, 2400, 41.7, "feber", "graes" };

	add_person(&Casper);
	add_food_intake(Casper, feedCasper);
	add_condition_log(Casper, CasperErSygLog);
	
	return 0;
}

void add_person(personInfo *person)/*Function for adding a person the the system */
{
	FILE *personFilePtr;

	update_index_file(person);
	make_folder(*person);

	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE];

	sprintf(fileName, "%s%d/%d ID.txt", FILE_PATH, person->id, person->id); /*Creates file name from ID of the person*/
	sprintf(log, "%d, %s, %d, %s, %s\n", person->id, person->department, person->cprNumber, person->name, person->allergy);/*Pulls log indformation from stuct*/
	save_in_file(personFilePtr, log, fileName);
}

void add_food_intake(personInfo person, nutritionIntake intake[]) /* Adds a food intake to their patientfile */
{

	/* NEEDS A FIX! needs the size of the "nutritionIntake" array to work! either from as a parameter or as an element in the array!*/

	FILE *foodFilePtr;

	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE],
		 timeStamp[TIME_STAMP_SIZE];

	datestamp(timeStamp);
	/* int a = sizeof(nutritionIntake) / sizeof(intake[0]); */
	sprintf(fileName, "%s%d/%d IntakeLog.txt", FILE_PATH, person.id, person.id); /*Creates file name from ID of the person*/
	printf("%s\n", fileName);

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			printf("first");
			sprintf(log, "%19s  | %25s | %5dKJ. | %7.2lfg. | %5dg.\n", timeStamp, intake[i].ingredient, intake[i].kiloJoule, intake[i].protein, intake[i].amount);
			save_in_file(foodFilePtr, log, fileName);
		}
		else
		{
			sprintf(log, "                     | %25s | %5dKJ. | %7.2lfg. | %5dg.\n", intake[i].ingredient, intake[i].kiloJoule, intake[i].protein, intake[i].amount);
			save_in_file(foodFilePtr, log, fileName);
		}
	}
}

void add_condition_log(personInfo person, conditionHistory conditionLog)
{
	FILE *condtionFilePtr;
	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE],
		 timeStamp[TIME_STAMP_SIZE];

	datestamp(timeStamp);
	sprintf(fileName, "%s%d/%d condition.txt", FILE_PATH, person.id, person.id); /*Creates file name from ID of the person*/
	sprintf(log, "%18s | %3d | %3d | %3.2lf | %4d | %4.2lf | %30s | %30s\n", timeStamp, conditionLog.weight, conditionLog.height, conditionLog.bmi, conditionLog.bmr, conditionLog.temperature, conditionLog.illness, conditionLog.allergy); /*Creates file name from ID of the person*/
	save_in_file(condtionFilePtr, log, fileName);
}

void save_in_file(FILE *filePtr, char string[], char fileName[]) /* Saves string in a file, or makes the file if its not already there. Takes filePointer, a string, and a fileName */
{
	if (filePtr != NULL)
	{
		printf("appended %s\n", fileName);
		filePtr = fopen(fileName, "a");
		fprintf(filePtr, string);
	} else
	{
		printf("made %s\n", fileName);
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

void update_index_file(personInfo *person) /* Updates the index file that tracks all the patients*/
{
	FILE *indexFilePtr;
	char indexLog[NAME_SIZE],
		 fileName[NAME_SIZE];

	sprintf(fileName, "%s%s", FILE_PATH, INDEX_FILE_NAME);
	int index = find_index(indexFilePtr, fileName);
	person->id = index;
	sprintf(indexLog, "%d %s %s\n", index, person->name, person->illness);

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