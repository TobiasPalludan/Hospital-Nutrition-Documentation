#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <direct.h>
#include "functions.h"

/* We calculate BMI from the standard equation */

/* Input: height and weight of a person
   Output: BMI of a person*/
double BMI(double height, double weight){
  height = height / 100;
  /*Omregner højde fra centimeter til meter*/
  return weight / (height * height);
}

/* We calculate BMR from the standard equation and in proportion to gender*/

/* Input: height, weight and CPRnumber of a given person 
   Output: Standard BMR of the given person depending on gender*/
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

/* Input: CPRnumber of a given person
   Output: Age of the given person*/
int get_age(long long int cpr){
  int age, dateofbirth, year, month, day, temp, n_7;
  
  /*time_t is a type from time.h*/
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  /*Temp is a temporary variables which is used to calculate the other variables value*/
  dateofbirth = cpr / 10000;
  n_7 = (cpr / 1000) % 10;
  year = (dateofbirth % 100) + 1900;
  temp = dateofbirth / 100;
  month = temp % 100;
  temp = temp/ 100;
  day = temp % 100;

/*If the if statement is true, the person is born in 2000 or above, but the year(birthyear) wont be above 2000 but between 1900-1999. 
  Therefore we need to add 100 to year(birthyear), so the year(birthyear) will be above 2000 and thereby calculate the right age*/
  if ((n_7 == 4 || n_7 == 9 && year < 1937) )
    year = year + 100;
  
  /*If the if statement is true, the person is born in 2000 or above, but the year(birthyear) wont be above 2000 but between 1900-1999. 
  Therefore we need to add 100 to year(birthyear), so the year(birthyear) will be above 2000 and thereby calculate the right age*/
  else if (n_7 > 4 && n_7 < 1958 )
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
void datestamp(char output[]){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  /*Printing values from struct tm to the array we get through function parameters*/
  sprintf(output, "%.2d-%.2d-%.4d %.2d:%.2d", tm.tm_mday, tm.tm_mon + 1,
                tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/* Prints a warning depending on warning_BMI's return value*/
/* Input: return value of the function warning_BMI
   Output: No return, but will prints a sentence depending on the return value of warning_BMI*/
void print_warning(double BMI)
{
  int tilstand;
  tilstand = warning_BMI(BMI);
    
    /*The warning is getting printed on standard output */
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

/* Returns a value depending on BMI*/ 

/*Input: BMI for the given person, calculated by the function "BMI"
  Output: A value depending on the value of BMI*/
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

  /*Used to acces file or create it via save_in_file*/
	FILE *personFilePtr;

	/*FILE_PATH is a global variable from functions.h which contains the location where the folder should be made*/
	make_patient_folder(FILE_PATH);

	/*person is a variable from functionparameter*/
	update_index_file(person); 

	/*person is a variable from functionparameter*/
	make_folder(*person); 

	/*Creates file name from ID of the person*/
	sprintf(fileName, "%s%d/%d ID.txt", FILE_PATH, person->id, person->id);
	
	/*Pulls log information from stuct*/
	sprintf(log, "%d, %s, %lld, %s\n", person->id, person->department, person->cprNumber, person->name);
	
  /* Saves string in a file, or makes the file if its not already there.*/
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
	
  /*Used to acces file or create it via save_in_file*/
	FILE *foodFilePtr;
  
  /*Function which calculate the actual date and time*/
	datestamp(timeStamp);

	/*Creates file name from ID of the person*/
	sprintf(fileName, "%s%d/%d IntakeLog.txt", FILE_PATH, p_ID, p_ID); 
	printf("%s\n", fileName);
  
  /*Prints information for each Ingredient that the user has entered aswell as dishname and what i contains*/
	for (int i = 0; i < intake[0].noIngredients +1; i++)
	{
		if (i == 0)	/* Prints the dish name,total nutrition, and a timestamp */
		{
			sprintf(log, "%16s   %-21s Energi: %7d KJ. Protein: %6.1lf g. Fat: %6.1lf g\n", timeStamp, intake[i].ingredient, intake[i].kiloJoule, intake[i].protein, intake[i].fat);
			
      /*Saves the string in the array called log in the file which foodfilePtr is pointing at. Or makes the file if its not already there.*/
			save_in_file(foodFilePtr, log, fileName);
		}
		else /* Prints the ingredients of the dish */
		{
      if (intake[i].kiloJoule != 0){
			  sprintf(log, "\n                   %s Energi: %7d KJ. Protein: %6.1lf g. Fat: %6.1lf g. \n", intake[i].ingredient, intake[i].kiloJoule, intake[i].protein, intake[i].fat);
			  
        /*Saves the string in the array called log in the file which foodfilePtr is pointing at.*/
			  save_in_file(foodFilePtr, log, fileName);
        }
		}
	}
	/*Adds newlines to the array log, and prints them in the file  which foodfilePtr is pointing at*/
  sprintf(log, "\n\n");
  save_in_file(foodFilePtr, log, fileName);
}

/* adds a contition log to the conditionfile of the given patient*/
/* Input: a variable person with type personInfo which contains the basic
   information about the patient. A variable conditionLog with type conditionsHistory
   which contains information about the patients health.
   Output: No return, but prints a string containen information about the 
   patient to the file given patientfile called condition.txt */
void add_condition_log(personInfo person, conditionHistory conditionLog) /* adds a contition log to the log file. */
{
	/*Used to acces file or create it via save_in_file*/
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
	sprintf(log, "%18s | %6.1lf |  %3.1lf | %3.1lf | %5d | %4.1lf | %9s |\n", timeStamp, conditionLog.weight, conditionLog.height, conditionLog.bmi, conditionLog.bmr, conditionLog.temperature, conditionLog.illness); 
	
  /*Saves the string in the array called log in the file which condtionFilePtr i pointing at.*/
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
		/*Opens file with the current name*/
		filePtr = fopen(fileName, "a");

		/*Printing the given information in the file which is pointed at*/
		fprintf(filePtr, string);

	} else	/* If the file does not exist, a new one is made */
	{
		/*Opens file and thereby makes it and names it the current name*/
		filePtr = fopen(fileName, "w");

		/*Printing the given information in the file which is pointed at*/
		fprintf(filePtr, string);
	}
	/*Closing file by deleting the pointer to file*/
	fclose(filePtr);
}

/* Creates the main folder to store all patient subfolders at the given location.  
   Input: A string containing the path where the file should be created
   Output: No return.*/
void make_patient_folder(char *string)		
{
	/*Makes folder at the given location, which is given by the function parameter*/
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
  
  /*Makes folder with location according to the string that path contains*/
  _mkdir(path);
}

/* Updates the index file that tracks all the patients by ID, Name and Illness.
   Calls the function find_index to find what ID/index the patient should have*/
/* Input: a pointer to the variable person with the type personInfo
   Output: No return, but prints a string to the indexfile via the the function save_in_file*/
void update_index_file(personInfo *person)
{ 
	/*Used to acces file or create it via save_in_file*/
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
	sprintf(indexLog, "%d %s\n", index, person->name);
  
  /*Prints the string which indexLog contains into the file which name and location */
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
	/*Opens the indexfile in readmode*/
	filePtr = fopen(fileName, "r");

	/*If the file is empty then is filePtr == NULL otherwise is filePtr != NULL*/	
	/*If the if statement is true the file isn't empty and the content is being read*/
	if (filePtr != NULL)
	{
		int index = 0, c = 0;
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
	/*If the file is empty it means that there are no patients registered, 
	therefore it returns 1 which is the highest index at the current time*/
	else {
		fclose(filePtr);
		return 1;
	}
}
