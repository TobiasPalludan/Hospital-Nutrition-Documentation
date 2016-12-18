#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <direct.h>
#include "functions.h"

/* We calculate BMI from the standard equation */

/* Input: height and weight of a given person
   Output: BMI of the given person*/
double BMI(double height, double weight)
{
	/*Omregner højde fra centimeter til meter*/
  height = height / 100;

  return weight / (height * height);
}

/* We calculate BMR from the standard equation and in proportion to gender*/

/* Input: height, weight and CPRnumber of a given person 
   Output: Standard BMR of the given person*/
double BMR(double height, double weight, long long int cpr)
{
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

/* Input: CPRnumber of a given person
   Output: Age of the given person*/
int get_age(long long int cpr)
{
  int age, dateofbirth, year, month, 
      day, temp, cprdigitno7;
  
  /*time_t is a type from time.h <<<<<<<<<<<<<<<<<<<<<<<<<<<Hvad gør time(NULL) og *localtime(&t)<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  /*Temp is a temporary variables which is used to calculate the other variables value*/
  dateofbirth = cpr / 10000;
  cprdigitno7 = (cpr / 1000) % 10;
  year = (dateofbirth % 100) + 1900;
  temp = dateofbirth / 100;
  month = temp % 100;
  temp = temp/ 100;
  day = temp % 100;
  
  /*If the if statement is true, the person is born in 2000 or above, but the year(birthyear) wont be above 2000 but between 1900-1999. 
  Therefore we need to add 100 to year(birthyear), so the year(birthyear) will be above 2000 and thereby calculate the right age*/
  if ((cprdigitno7 == 4 ||cprdigitno7 == 9 && year < 1937))
    year = year + 100;

  /*If the if statement is true, the person is born in 2000 or above, but the year(birthyear) wont be above 2000 but between 1900-1999. 
  Therefore we need to add 100 to year(birthyear), so the year(birthyear) will be above 2000 and thereby calculate the right age*/
  else if (cprdigitno7 > 4 && cprdigitno7 < 9 && year < 1958)
    year = year + 100;

  /*tm.tm_year = actualyear(2016) - 1900 = 116. Age is = (116+1900) - birthyear*/
  age = (tm.tm_year + 1900) - year;

  /* Checks if the person has had birthday this yeah with months and days */
  /*If month(birthmonth) is bigger than the actual month(tm.tm_mon), then the person havent had birthday yet this year and therefore we need to -1 to age*/
  if (month > tm.tm_mon + 1)
    --age;
  
  /*If month(birthmonth) is equal to the actual month(tm.tm_mon) we need to check if day(day og birth) is bigger then the actual day(tm.tm_mday).
    If the is true the person havent had birthday yet and therefore we need to -1 to age*/
  else if (month == (tm.tm_mon + 1) && day > tm.tm_mday)
    --age;

  return age;
}

/* We get the current day by using the library time.h */

/*Input: Empty array which shall contain the date and time 
  Output: No return, but the empty array will be assigned to values
          which represents the current date and time*/
void datestamp(char output[])
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  /*Printing values from struct tm to the array we get through function parameters*/
  sprintf(output, "%.2d-%.2d-%.4d %.2d:%.2d", tm.tm_mday, tm.tm_mon + 1,
                  tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/* Prints a warning depending on warning_BMI's return value*/
/* Input: Pointer to a file, return value of the function warning_BMI
   Output: No return, but will prints a sentence depending on the return value of warning_BMI*/
void print_warning( FILE *filPointer, int tilstand)
{
	  /*The warning is getting printed on the file (bliver den også printet i prompten?<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
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

/* Returns a value depending on BMI*/ 

/*Input: BMI for the given person, calculated by the function "BMI"
  Output: A value depending on the value of BMI*/
int warning_BMI(double BMI)
{
    if (BMI < 18.5)
    {
      return 1;
    }

    else if (BMI >= 25 && BMI <= 30)
    {
      return 0;
    }

    else if(BMI > 30)
    {
        return -1;
    }
    else/*If the BMI is normal*/
    {
        return 2;
    }
}

/*From filehandler.c*/

	/* Function for adding a person the the system */
  /* Calls the function for creating the index aswell
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
  /**/
	make_patient_folder(FILE_PATH);/*FILE_PATH is a global variable from functions.h which contains the location where the folder should be made*/
	update_index_file(person); /*person is a variable from functionparameter*/
	make_folder(*person); /*person is a variable from functionparameter*/

	sprintf(fileName, "%s%d/%d ID.txt", FILE_PATH, person->id, person->id); /*Creates file name from ID of the person*/

	sprintf(log, "%d, %s, %.10lld, %s, %s\n", person->id, person->department, person->cprNumber,
	                                          person->name, person->allergy);/*Pulls log information from stuct*/

	save_in_file(personFilePtr, log, fileName); /* Saves string in a file, or makes the file if its not already there. */
}
/* Adds a food intake to the patients file 
   Input: The ID of the patient aswell as an array
   containing information about the patients intake
   Output: No return, but it prints out a string containing information
   about the intake to the patients file called Intakelog.txt*/
void add_food_intake(int p_ID, nutrition intake[]) 
{

	/* NEEDS A FIX! needs the size of the "nutritionIntake" array to work! either from as a parameter or as an element in the array!*/
	FILE *foodFilePtr;


	char fileName[FILE_NAME_SIZE],
		   log[LOG_FILE_SIZE],
		   timeStamp[TIME_STAMP_SIZE];

	datestamp(timeStamp); /*Function which calculate the actual date and time*/

	/* int a = sizeof(nutritionIntake) / sizeof(intake[0]); */
	/* printf("size of struct arr %d\n", a); */

	sprintf(fileName, "%s%d/%d IntakeLog.txt", FILE_PATH, p_ID, p_ID); /*Creates file name from ID of the person, so file name is: ID IntakeLog.txt*/
	printf("%s\n", fileName);
  
  /*Prints information for each Ingredient that the user has entered aswell as dishname and what i contains*/
	for (int i = 0; i < intake[0].noIngredients +1; i++)
	{
		if (i == 0) /* Print the dish name, total nutrition for the dish, and a timestamp */
		{
			printf("first");/*Hvorfor printes dette ikke?*/
			sprintf(log, "%16s  | %25s | %5dKJ. | %7.2lfg. | %5dg.\n", timeStamp, intake[i].ingredient, intake[i].kiloJoule, 
			                                                           intake[i].protein, intake[i].weight);
			save_in_file(foodFilePtr, log, fileName); /*Saves the string in the array called log in the file which foodfilePtr i pointing at. Or makes the file if its not already there.*/
		}
		else/* Print the ingredients of the dish */
		{
			sprintf(log, "                  | %25s | %5dKJ. | %7.2lfg. | %5dg.\n", intake[i].ingredient, intake[i].kiloJoule, 
				                                                                     intake[i].protein, intake[i].weight);
			save_in_file(foodFilePtr, log, fileName); /*Saves the string in the array called log in the file which foodfilePtr i pointing at.*/
		}
	}
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
  
  /*Assigns the variable conditionLog's BMI and BMR to the return value of the BMI and BMR function*/
  conditionLog.bmi = BMI(conditionLog.height, conditionLog.weight);
  conditionLog.bmr = BMR(conditionLog.height, conditionLog.weight, person.cprNumber);

  /*Calculates the current date and time*/
	datestamp(timeStamp);

  /*Creates file name from ID of the person, so file name is: ID condition.txt*/
	sprintf(fileName, "%s%d/%d condition.txt", FILE_PATH, person.id, person.id); 
	
	/*Assigning values to the array called log, which then contain the information which should be printed into the file, which happens via the function save_in_file*/
	sprintf(log, "%18s | %3lf | %3lf | %3.2lf | %4d | %4.2lf | %30s | %30s\n", timeStamp, conditionLog.weight, conditionLog.height,
	                                                                           conditionLog.bmi, conditionLog.bmr, conditionLog.temperature,
	                                                                           conditionLog.illness, conditionLog.allergy); 
	
	/*Saves the string in the array called log, in the file which condtionFilePtr i pointing at.*/
	save_in_file(condtionFilePtr, log, fileName);
}
/* Saves string in a file, or makes the file if its not already there.*/
/* Input: A filepointer, string containing the information which should be
   saved in the file, and last a string containing path and name of the file 
   the information should be saved in
   Output: No return, but saves the information given as input in a file*/
void save_in_file(FILE *filePtr, char string[], char fileName[])
{
	if (filePtr != NULL)/*appends to file if it exist*/
	{
		printf("appended %s\n", fileName); /*Information about if the file exists or not*/
		filePtr = fopen(fileName, "a"); /*Opens file with the current name*/
		fprintf(filePtr, string); /*Printing the given information in the file which is pointed at*/
	} 
	else /* If the file does not exist, a new one is made */
	{
		printf("made %s\n", fileName);  /*Information about if the file exists or not*/
		filePtr = fopen(fileName, "w");/*Opens file and thereby makes it and names it the current name*/
		fprintf(filePtr, string); /*Printing the given information in the file which is pointed at*/
	}
	fclose(filePtr); /*Closing file by deleting the pointer to file*/
} 

/* Creates the main folder to store all patient subfolders at the given location.  
   Input: A string containing the path where the file should be created
   Output: No return.*/
void make_patient_folder(char *string) 
{
	if (_mkdir(string) == 0) /*Makes folder at the given location, which is given by the function parameter*/
	{
		printf("made folder: %s\n", string);
	}
	else 
	{
		printf("Folder already exists\n");
  }
}
/*Makes patient subfolders at a given location*/
/*Input: A variable person with the type personInfo
  Output: No return*/
void make_folder(personInfo person)	
{
	char path[FILE_NAME_SIZE] = { FILE_PATH },
		   idPath[FILE_NAME_SIZE];

	itoa(person.id, idPath, 10);	/* Converts a number to a string (needed for the _mkdir because it needs a string) */
	strcat(path, idPath); /*Append idPath to path, makes a string with path and idPath*/
  
  /*Makes folder with location according to the string that path contains*/
	if (_mkdir(path)==0) 
	{
		printf("made folder: %s\n", path);
	} 
	else
  {
	  printf("Folder already exists\n");
  }
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
  
  /*Makes string named "fileName" which contains the value of the global
   variables FILE_PATH and INDEX_FILE_NAME which comes from functions.h*/
	sprintf(fileName, "%s%s", FILE_PATH, INDEX_FILE_NAME);
  
  /*find_index returns what index/ID the patient should have*/
  int index = find_index(indexFilePtr, fileName);
  	
	person->id = index;
	/*Makes the string which will be printed into the indexfile via save_in_file*/
	sprintf(indexLog, "%d %s %s\n", index, person->name, person->illness);
  
  /*Prints the string which indexLog contains into the file which name and location 
  is desribed in the string that are stored in the char array: fileName. Here it is patients/PatientIndex.txt
  if this file do not exit the file is being made*/
	save_in_file(indexFilePtr, indexLog, fileName);
}

 /* Searches index file for higest index number. If the indexfile already exist
    the function will return the value of the highest index+1 which will be the index
    and ID of the next patient who is about the registered to the system*/
 /* Input: A pointer to a file and a string containing the path of the file
    which is going to be opened, in this scenario "patients/PatientIndex.txt"
    Output: return the index/ID of the person who is about to be registered in the system*/
int find_index(FILE *filePtr, char fileName[])
{
	/*Opens the indexfile in readmode*/
	filePtr = fopen(fileName, "r");
	/*If the file is empty then is filePtr == NULL otherwise is filePtr != NULL*/	
	/*If the if statement is true the file isn't empty and the content is being read*/
	if (filePtr != NULL)
	{
		int index = 0, c = 0;
		char name[NAME_SIZE];
		char illness[NAME_SIZE];

		while (!feof(filePtr))
		{ 
			/*Scans index file for the heigest index assuming the heigst index is last */
			/*Scans all lines and finds the last index/highest index in the file and returns that value + 1*/
			fscanf(filePtr, " %d %[A-z] %[A-z]\n", &index, name, illness); 
			printf("%d \n", index);
		}
		fclose(filePtr);
		return index + 1;
	}
	/*If the file is empty it means that there are no patients registered, 
	therefore it returns 1 which is the highest index at the current time*/
	else {
		fclose(filePtr);
		return 1;
	}
}
