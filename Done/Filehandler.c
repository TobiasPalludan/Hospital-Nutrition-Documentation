#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <direct.h>
#include "lib.h"
#include "filehandler.h"

	/*Function for adding a person the the system */
  /*Calls the function for creating the index aswell
    The function are creating the general folder for patients
    aswell as an folder for each patients which contains op to
    three files for that patient

    Input: pointer to a variable of the type personInfo.
    Output: No return*/
void add_person(personInfo *person)
{
	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE];

	FILE *personFilePtr;

	make_patient_folder(FILE_PATH);
	update_index_file(person);
  make_folder(*person);

	/*Creates file name from ID of the person*/
	sprintf(fileName, "%s%d/%d ID.txt", FILE_PATH, person->id, person->id);

	/*Pulls log information from stuct*/
	sprintf(log, "%d, %s, %.10lld, %s\n", person->id, person->department, person->cprNumber, person->name);

  save_in_file(personFilePtr, log, fileName);
}

/* Adds a food intake to the patients file */
/* Input: The ID of the patient aswell as an array
   containing information about the patients intake
   Output: No return, but it prints out a string containing information
   about the intake to the patients file called Intakelog.txt*/

void add_food_intake(int p_ID, nutrition intake[])
{
  char fileName[FILE_NAME_SIZE],
		   log[LOG_FILE_SIZE],
		   timeStamp[TIME_STAMP_SIZE];

 	FILE *foodFilePtr;

 	datestamp(timeStamp);

	/*Creates file name from ID of the person*/
	sprintf(fileName, "%s%d/%d IntakeLog.txt", FILE_PATH, p_ID, p_ID);
	printf("%s\n", fileName);

  /*Prints information for each Ingredient that the user has entered aswell as dishname and what i contains*/
	for (int i = 0; i < intake[0].noIngredients +1; i++)
	{
		if (i == 0)	/* Prints the dish name,total nutrition, and a timestamp */
		{
			sprintf(log, "%16s   %-21s Energi: %7d KJ. Protein: %6.1lf g. Fat: %6.1lf g\n", timeStamp, intake[i].ingredient,
             intake[i].kiloJoule, intake[i].protein, intake[i].fat);

      save_in_file(foodFilePtr, log, fileName);
		}
		else /* Prints the ingredients of the dish */
		{
      if (intake[i].kiloJoule != 0){
			  sprintf(log, "\n                   %s Energi: %7d KJ. Protein: %6.1lf g. Fat: %6.1lf g. \n", intake[i].ingredient,
               intake[i].kiloJoule, intake[i].protein, intake[i].fat);

        save_in_file(foodFilePtr, log, fileName);
        }
		}
	}
  sprintf(log, "\n\n");
  save_in_file(foodFilePtr, log, fileName);
}

/* adds a contition log to the conditionfile of the given patient*/
/* Input: a variable person with type personInfo which contains the basic
   information about the patient. A variable conditionLog with type conditionsHistory
   which contains information about the patients health.
   Output: No return, but prints a string containen information about the
   patient to the file given patientfile called condition.txt */

void add_condition_log(personInfo person, conditionHistory conditionLog)
{

	FILE *condtionFilePtr;

	char fileName[FILE_NAME_SIZE],
		 log[LOG_FILE_SIZE],
		 timeStamp[TIME_STAMP_SIZE];


  conditionLog.bmi = BMI(conditionLog.height, conditionLog.weight);
  conditionLog.bmr = BMR(conditionLog.height, conditionLog.weight, person.cprNumber);


	datestamp(timeStamp);

	/*Creates file name from ID of the person, so file name is: ID condition.txt*/
	sprintf(fileName, "%s%d/%d condition.txt", FILE_PATH, person.id, person.id);


	sprintf(log, "%18s | %6.1lf |  %3.1lf | %3.1lf | %5d | %4.1lf | %9s |\n", timeStamp, conditionLog.weight, conditionLog.height,
         conditionLog.bmi, conditionLog.bmr, conditionLog.temperature, conditionLog.illness);


	save_in_file(condtionFilePtr, log, fileName);
}

/* Saves string in a file, or makes the file if its not already there.*/
/* Input: A filepointer, string containing the information which should be
   saved in the file, and last a string containing path and name of the file
   the information should be saved in
   Output: No return, but saves the information given as input in a file*/
void save_in_file(FILE *filePtr, char string[], char fileName[])
{
	if (filePtr != NULL) /* appends to file if it exist */
	{

		filePtr = fopen(fileName, "a");


		fprintf(filePtr, string);

	}
  else	/* If the file does not exist, a new one is made */
	{

		filePtr = fopen(fileName, "w");


		fprintf(filePtr, string);
	}

	fclose(filePtr);
}

/* Creates the main folder to store all patient subfolders at the given location.
   Input: A string containing the path where the file should be created
   Output: No return.*/
void make_patient_folder(char *string)
{
	/*Makes folder at the given location, which is given by the string as a function parameter*/
  _mkdir(string);
}

/*Makes patient subfolders at a given location*/
/*Input: A variable person with the type personInfo
  Output: No return*/
void make_folder(personInfo person)
{
	char path[FILE_NAME_SIZE] = { FILE_PATH },
		 idPath[FILE_NAME_SIZE];

  /* Converts a number to a string (needed for the _mkdir because it needs a string) */
	itoa(person.id, idPath, 10);

	/*Append idPath to path, makes a string with path and idPath*/
	strcat(path, idPath);

  _mkdir(path);
}

/* Updates the index file that tracks all the patients by ID, Name and Illness.
   Calls the function find_index to find what ID/index the patient should have*/
/* Input: a pointer to the variable person with the type personInfo
   Output: No return, but prints a string to the indexfile via the the function save_in_file*/
void update_index_file(personInfo *person)
{

	FILE *indexFilePtr;

	char indexLog[NAME_SIZE],
		 fileName[NAME_SIZE];

 sprintf(fileName, "%s%s", FILE_PATH, INDEX_FILE_NAME);

  /*find_index returns what index/ID the patient should have*/
	int index = find_index(indexFilePtr, fileName);

	person->id = index;
	sprintf(indexLog, "%d %s\n", index, person->name);
  save_in_file(indexFilePtr, indexLog, fileName);
}

/* Searches index file for higest index number. If the indexfile already exist
    the function will return the value of the highest index+1 which will be the index
    and ID of the next patient who is about the registered to the system*/
 /* Input: A pointer to a file and a string containing the path of the file
    which is going to be opened, in this scenario "patients/PatientIndex.txt"
    Output: return the index/ID of the person who is about to be registered in the system*/
int find_index(FILE *filePtr, char fileName[]) /* Searches index file for higest index number */
{
	filePtr = fopen(fileName, "r");

	/*If the file is empty then is filePtr == NULL otherwise is filePtr != NULL*/
	if (filePtr != NULL)
	{
		int index = 0;
		char name[NAME_SIZE];

		while (!feof(filePtr))
		{
			/*Scans index file for the heigest index assuming the heigst index is last */
			/*Scans all lines and finds the last index/highest index in the file and returns that value + 1*/
			fscanf(filePtr, " %d %[A-z]\n", &index, name);
			printf("%d \n", index);
		}
		fclose(filePtr);
		return index + 1;
	}
	/*If the file is empty it means that there are no patients registered*/
  else
  {
		fclose(filePtr);
		return 1;
	}
}
