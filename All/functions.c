#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <direct.h>
#include "functions.h"

/* We calculate BMI from the standard equation */
double BMI(double height, double weight){
  height = height / 100;

  return weight / (height * height);
}

/* We calculate BMR from the standard equation and in proportion to gender */
double BMR(double height, double weight, long long int cpr){
  double BMR;
  int age;

  /* We get the age */
  age = get_age(cpr);

  /* Last digit in CPR determine gender. Even number = Female. Odd number = Male. */
  if (cpr % 2 == 0)
  {
    BMR = 665.0955 + 9.5634 * weight + 1.8496 * height - 4.6756 * age;
  }

  else if (cpr % 2 != 0)
  {
    BMR = 66.5 + 13.7516 * weight + 5.0033 * height - 6.755 * age;
  }

  return BMR;
}

/* Based on the current day we find the age. */
int get_age(long long int cpr){
  int age, dateofbirth, year, month, day, temp, n_7;

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  dateofbirth = cpr / 10000;
  n_7 = (cpr / 1000) % 10;
  year = (dateofbirth % 100) + 1900;
  temp = dateofbirth / 100;
  month = temp % 100;
  temp = temp/ 100;
  day = temp % 100;


  if ((n_7 == 4 || n_7 == 9 && year < 1937) )
    year = year + 100;

  else if (n_7 > 4 && n_7 < 1958 )
    year = year + 100;


  age = (tm.tm_year + 1900) - year;

  /* Checks if the person has had birthday this yeah with months and days */
  if (month > tm.tm_mon + 1)
    --age;

  else if (month == (tm.tm_mon + 1) && day > tm.tm_mday)
    --age;

  return age;
}

/* We get the current day by using the library time.h */
void datestamp(char output[]){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  sprintf(output, "%2d-%2d-%4d %2d:%2d", tm.tm_mday, tm.tm_mon + 1,
                tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/* Prints a warning depending on warning_BMI's return value. */
void print_warning( FILE *filPointer, int tilstand)
{
    if(tilstand == 1)
    {
        fprintf(filPointer, "%s\n", "BMI er under 18,5.");
    }
    else if(tilstand == 0)
    {
        fprintf(filPointer, "%s\n", "BMI er mellem 25 og 30.");
    }
    else if(tilstand == -1)
    {
        fprintf(filPointer, "%s\n", "BMI er over 30.");
    }
}

/* Returns a value depending on BMI */
int warning_BMI(double BMI)
{
    if (BMI < 18.5)
        return 1;

    else if (BMI >= 25 && BMI <= 30)
        return 0;

    else if(BMI > 30)
        return -1;
    else
        return 2;
}

/*From filehandler.c*/

void add_person(personInfo *person)		/* Function for adding a person the the system      */
{										/* Calls the function for creating the index aswell */
	FILE *personFilePtr;

	make_patient_folder(FILE_PATH);
	update_index_file(person);
	make_folder(*person);

	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE];

	sprintf(fileName, "%s%d/%d ID.txt", FILE_PATH, person->id, person->id); /*Creates file name from ID of the person*/
	sprintf(log, "%d, %s, %.10lld, %s, %s\n", person->id, person->department, person->cprNumber, person->name, person->allergy);/*Pulls log indformation from stuct*/
	save_in_file(personFilePtr, log, fileName);
}

void add_food_intake(personInfo person, nutritionIntake intake[]) /* Adds a food intake to the patientfile */
{

	/* NEEDS A FIX! needs the size of the "nutritionIntake" array to work! either from as a parameter or as an element in the array!*/

	FILE *foodFilePtr;

	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE],
		 timeStamp[TIME_STAMP_SIZE];

	datestamp(timeStamp);
	/* int a = sizeof(nutritionIntake) / sizeof(intake[0]); */
	/* printf("size of struct arr %d\n", a); */

	sprintf(fileName, "%s%d/%d IntakeLog.txt", FILE_PATH, person.id, person.id); /*Creates file name from ID of the person*/
	printf("%s\n", fileName);

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)					/* Print the dish name,total nutrition, and a timestamp */
		{
			printf("first");
			sprintf(log, "%19s  | %25s | %5dKJ. | %7.2lfg. | %5dg.\n", timeStamp, intake[i].ingredient, intake[i].kiloJoule, intake[i].protein, intake[i].amount);
			save_in_file(foodFilePtr, log, fileName);
		}
		else						/* Print the engredients of the dish */
		{
			sprintf(log, "                     | %25s | %5dKJ. | %7.2lfg. | %5dg.\n", intake[i].ingredient, intake[i].kiloJoule, intake[i].protein, intake[i].amount);
			save_in_file(foodFilePtr, log, fileName);
		}
	}
}

void add_condition_log(personInfo person, conditionHistory conditionLog) /* adds a contition log to the log file. */
{
	FILE *condtionFilePtr;
	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE],
		 timeStamp[TIME_STAMP_SIZE];

  conditionLog.bmi = BMI(conditionLog.height, conditionLog.weight);
  conditionLog.bmr = BMR(conditionLog.height, conditionLog.weight, person.cprNumber);


	datestamp(timeStamp);
	sprintf(fileName, "%s%d/%d condition.txt", FILE_PATH, person.id, person.id); /*Creates file name from ID of the person*/
	sprintf(log, "%18s | %3lf | %3lf | %3.2lf | %4d | %4.2lf | %30s | %30s\n", timeStamp, conditionLog.weight, conditionLog.height, conditionLog.bmi, conditionLog.bmr, conditionLog.temperature, conditionLog.illness, conditionLog.allergy); /*Creates file name from ID of the person*/
	save_in_file(condtionFilePtr, log, fileName);
}

void save_in_file(FILE *filePtr, char string[], char fileName[]) /* Saves string in a file, or makes the file if its not already there. Takes filePointer, a string, and a fileName */
{
	if (filePtr != NULL)				/* appends to file if it exist */
	{
		printf("appended %s\n", fileName);
		filePtr = fopen(fileName, "a");
		fprintf(filePtr, string);
	} else								/* If the file does not exist, a new one is made */
	{
		printf("made %s\n", fileName);
		filePtr = fopen(fileName, "w");
		fprintf(filePtr, string);
	}
	fclose(filePtr);
}

void make_patient_folder(char *string)		/* Creates the main folder to store all patient subfolders */
{
	if (_mkdir(string) == 0)
	{
		printf("made folder: %s\n", string);
	}
	else printf("Folder already exists\n");
}

void make_folder(personInfo person)			/* Makes patient subfolders */
{
	char path[FILE_NAME_SIZE] = { FILE_PATH },
		 idPath[FILE_NAME_SIZE];

	itoa(person.id, idPath, 10);			/* Converts a number to a string (needed for the _mkdir because it needs a string) */
	strcat(path, idPath);

	if (_mkdir(path)==0)
	{
		printf("made folder: %s\n", path);
	} else printf("Folder already exists\n");
}

void update_index_file(personInfo *person)	/* Updates the index file that tracks all the patients */
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

int find_index(FILE *filePtr, char fileName[]) /* Searches index file for higest index number */
{
	filePtr = fopen(fileName, "r");
	if (filePtr != NULL)
	{
		int index = 0, c = 0;
		char name[NAME_SIZE];
		char illness[NAME_SIZE];

		while (!feof(filePtr))
		{
			fscanf(filePtr, " %d %[A-z] %[A-z]\n", &index, name, illness); /* Scans index file for the heigest index assuming the heigst index is last */
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
