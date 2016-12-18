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
  const double c_1 = 665.0955, c_2 = 9.5634, c_3 = 1.8496, c_4 = 4.6756, c_5 = 66.5, c_6 = 13.7516, c_7 = 5.0033, c_8 = 6.755;
  int age;

  /* We get the age */
  age = get_age(cpr);

  /* Last digit in CPR determine gender. Even number = Female. Odd number = Male. */
  if (cpr % 2 == 0)
  {
    return c_1 + c_2 * weight + c_3 * height - c_4 * age;
  }

  else if (cpr % 2 != 0)
  {
    return c_5 + c_6 * weight + c_7 * height - c_8 * age;
  }
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

  sprintf(output, "%.2d-%.2d-%.4d %.2d:%.2d", tm.tm_mday, tm.tm_mon + 1,
                tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/* Prints a warning depending on warning_BMI's return value. */
void print_warning(double BMI)
{
  int tilstand;
  tilstand = warning_BMI(BMI);

    if(tilstand == 1)
    {
        printf("\n WARNING: BMI is under 18,5.\n");
    }
    else if(tilstand == 2)
    {
        printf("\nWARNING: BMI is between 25 og 30.\n");
    }
    else if(tilstand == 3)
    {
        printf("\nWARNING: BMI is over 30.\n");
    }
}

/* Returns a value depending on BMI */
int warning_BMI(double BMI)
{
    if (BMI < 18.5)
        return 1;

    else if (BMI >= 25 && BMI <= 30)
        return 2;

    else if(BMI > 30)
        return 3;

    else
        return 0;
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
	sprintf(log, "%d, %s, %lld, %s\n", person->id, person->department, person->cprNumber, person->name);/*Pulls log indformation from stuct*/
	save_in_file(personFilePtr, log, fileName);
}

void add_food_intake(int p_ID, nutrition intake[]) /* Adds a food intake to the patientfile */
{

	/* NEEDS A FIX! needs the size of the "nutritionIntake" array to work! either from as a parameter or as an element in the array!*/

	FILE *foodFilePtr;

	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE],
		 timeStamp[TIME_STAMP_SIZE];

	datestamp(timeStamp);
	/* int a = sizeof(nutritionIntake) / sizeof(intake[0]); */
	/* printf("size of struct arr %d\n", a); */

	sprintf(fileName, "%s%d/%d IntakeLog.txt", FILE_PATH, p_ID, p_ID); /*Creates file name from ID of the person*/
	printf("%s\n", fileName);

	for (int i = 0; i < intake[0].noIngredients +1; i++)
	{
		if (i == 0)					/* Print the dish name,total nutrition, and a timestamp */
		{
			sprintf(log, "%16s   %-21s Energi: %7d KJ. Protein: %6.1lf g. Fat: %6.1lf g\n", timeStamp, intake[i].ingredient, intake[i].kiloJoule, intake[i].protein, intake[i].fat);
			save_in_file(foodFilePtr, log, fileName);
		}
		else						/* Print the engredients of the dish */
		{
      if (intake[i].kiloJoule != 0){
			  sprintf(log, "\n                   %s Energi: %7d KJ. Protein: %6.1lf g. Fat: %6.1lf g. \n", intake[i].ingredient, intake[i].kiloJoule, intake[i].protein, intake[i].fat);
			  save_in_file(foodFilePtr, log, fileName);
        }
		}
	}
  sprintf(log, "\n\n");
  save_in_file(foodFilePtr, log, fileName);
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
	sprintf(log, "%18s | %6.1lf |  %3.1lf | %3.1lf | %5d | %4.1lf | %9s |\n", timeStamp, conditionLog.weight, conditionLog.height, conditionLog.bmi, conditionLog.bmr, conditionLog.temperature, conditionLog.illness); /*Creates file name from ID of the person*/
	save_in_file(condtionFilePtr, log, fileName);
}

void save_in_file(FILE *filePtr, char string[], char fileName[]) /* Saves string in a file, or makes the file if its not already there. Takes filePointer, a string, and a fileName */
{
	if (filePtr != NULL)				/* appends to file if it exist */
	{
		filePtr = fopen(fileName, "a");
		fprintf(filePtr, string);
	} else								/* If the file does not exist, a new one is made */
	{
		filePtr = fopen(fileName, "w");
		fprintf(filePtr, string);
	}
	fclose(filePtr);
}

void make_patient_folder(char *string)		/* Creates the main folder to store all patient subfolders */
{
  _mkdir(string);
}

void make_folder(personInfo person)			/* Makes patient subfolders */
{
	char path[FILE_NAME_SIZE] = { FILE_PATH },
		 idPath[FILE_NAME_SIZE];

	itoa(person.id, idPath, 10);			/* Converts a number to a string (needed for the _mkdir because it needs a string) */
	strcat(path, idPath);

  _mkdir(path);
}

void update_index_file(personInfo *person)	/* Updates the index file that tracks all the patients */
{
	FILE *indexFilePtr;
	char indexLog[NAME_SIZE],
		 fileName[NAME_SIZE];

	sprintf(fileName, "%s%s", FILE_PATH, INDEX_FILE_NAME);
	int index = find_index(indexFilePtr, fileName);
	person->id = index;
	sprintf(indexLog, "%d %s\n", index, person->name);

	save_in_file(indexFilePtr, indexLog, fileName);
}

int find_index(FILE *filePtr, char fileName[]) /* Searches index file for higest index number */
{
	filePtr = fopen(fileName, "r");
	if (filePtr != NULL)
	{
		int index = 0, c = 0;
		char name[NAME_SIZE];

		while (!feof(filePtr))
		{
			fscanf(filePtr, " %d %[A-z]\n", &index, name); /* Scans index file for the heigest index assuming the heigst index is last */
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
