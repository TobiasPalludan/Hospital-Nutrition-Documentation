#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <direct.h>
#include "functions.h"

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
#define PRINT_DATA_SIZE 1000
#define RESET_OPTION 4

#define FILE_PATH "patients/"
#define INDEX_FILE_NAME "PatientIndex.txt"
#define clear() system("cls")

/* Userinterface prototypes*/
void p_main_menu(indexPos *indexArr, int indLen);
void p_new_patient(indexPos *indexArr, int indLen);
void p_existing_patient(indexPos *indexArr, int indLen);
void p_patient_menu(indexPos *indexArr, int p_ID, int indLen);
void p_update(indexPos *indexArr, int p_ID, int indLen);
void p_weight(int p_ID);
void p_intake(indexPos *indexArr, int p_ID, int indLen);
void p_change(int p_ID);
void p_print(int p_ID);
int p_discharge(int p_ID);



int
main (void){
  int indLen = 0;
  indexPos *indexArr;
  char dataFile[] = "Nutritional_database.txt";
  FILE *dtb;

  /* Open the database file and check if open */
  dtb = fopen(dataFile, "r+");
  if(dtb == NULL)
  {
    printf("No database with name \"%s\" exists!\n", dataFile);
    exit(EXIT_FAILURE);
  }
  indexArr = index_database(&indLen, dtb);

  p_main_menu(indexArr, indLen);
  clear();
  free(indexArr);
  fclose(dtb);
  return 0;
}

/* Main menu has 2 parameters, a indexPos pointer and an int indLen!!!!!
 * the function gives the user 4 choices in the userinterface*/
void p_main_menu(indexPos *indexArr, int indLen)
{

  int choice;
  choice = 4;


  while(choice != 0)
  {
      while (choice != 1 && choice != 2 && choice != 0) {
        clear();
        printf("Main Menu\nWelcome,\n\n *Press 1 to create new patient\n *Press 2 to access patient menu\n\n *Press 0 to exit \n\n>");
        scanf("\n%d", &choice);
  }

      if (choice == 1)
      {
        p_new_patient(indexArr, indLen);
        choice = RESET_OPTION;
      }

      else if (choice == 2)
      {
        p_existing_patient(indexArr, indLen);
        choice = RESET_OPTION;
      }
    }
  return;
}

void p_new_patient(indexPos *indexArr, int indLen)
{
  clear();
  /*Promt for input til ny patient*/
  /*Hardcoded*/
  int choice;
  personInfo person;
	conditionHistory personLog;
  choice = RESET_OPTION;
  while (choice != 0)
  {
    printf("Enter variables in order: CPRnumber, Department, Name, Illnes, Weight, Height, Temperature \n *Press 0 to return to Main menu\n\n>");
    scanf("\n%lld", &person.cprNumber);
    choice = person.cprNumber;
    if (choice == 0)
      break;
    scanf("%s %s %s %lf %lf %lf)",  person.department, person.name, personLog.illness, &personLog.weight,
                                    &personLog.height, &personLog.temperature);
    personLog.bmi = BMI(personLog.height, personLog.weight);
    personLog.bmr = BMR(personLog.height, personLog.weight, person.cprNumber);
    print_warning(personLog.bmi);

    while(choice != 0)
    {
      printf("\n*Press 0 to continue to Patient Menu\n\n>");
      scanf("\n%d", &choice);
    }

  add_person(&person);
  add_condition_log(person, personLog);
  p_patient_menu(indexArr, person.id, indLen);
  }
  return;
}

void p_existing_patient(indexPos *indexArr, int indLen)
{
  int p_ID;
  clear();
  printf("Main Menu/Patient Menu\n\n Enter patient ID\n>");
  scanf("\n%d", &p_ID);
  p_patient_menu(indexArr, p_ID, indLen);
  return;
}


void p_patient_menu(indexPos *indexArr, int p_ID, int indLen)
{
  int choice;
  choice = RESET_OPTION;
  clear();
  printf("Main Menu/Patient Menu\n Patient #%d\n\n You have 4 choices.\n *Press 1 to edit/add patient data\n *Press 2 to read patient date\n *Press 3 to discharge patient\n\n *Press 0 to go back to Main Menu\n\n>", p_ID);


  while(choice != 0)
  {
    while (choice != 1 && choice != 2 && choice != 3 && choice != 0) {
      clear();
      printf("Main Menu/Patient Menu\n Patient #%d\n\n You have 4 choices.\n *Press 1 to edit/add patient data\n *Press 2 to read patient date\n *Press 3 to discharge patient\n\n *Press 0 to go back to Main Menu\n\n>", p_ID);
      scanf("\n%d", &choice);
  }

    if (choice == 1)
    {
      p_update(indexArr, p_ID, indLen);
      choice = RESET_OPTION;
    }

    else if (choice == 2)
    {
      p_print(p_ID);
      choice = RESET_OPTION;
    }

    else if (choice == 3)
    {
      choice = p_discharge(p_ID);
    }
  }
  return;
}


void p_update(indexPos *indexArr, int p_ID, int indLen){
  int choice;
  choice = RESET_OPTION;

  while(choice != 0){
    while (choice != 1 && choice != 2 && choice != 3 && choice != 0)
    {
      clear();
      printf("Main Menu/Patient Menu/Update patient data\n Patient #%d\n\n You have 4 choices\n *Press 1 to enter new weight\n *Press 2 to enter new intake\n *Press 3 to change patient info\n\n *Press 0 to go back to Patient menu\n\n>", p_ID);
      scanf("\n%d", &choice);
    }

      if (choice == 1)
      {
        p_weight(p_ID);
        choice = RESET_OPTION;
      }

      else if (choice == 2)
      {
        p_intake(indexArr, p_ID, indLen);
        choice = RESET_OPTION;
      }

      else if (choice == 3)
      {
        p_change(p_ID);
        choice = RESET_OPTION;
      }
  }
  return;
}

void p_weight(int p_ID)
{
  /*Scan new weight*/
  int choice, ID;
  long long int cprNumber;
  double weight;
  conditionHistory personLog;
  FILE *fileptr, *fileptr_ID;
  char place[30], place_ID[30], patient_data[100], useless[30], patient_ID[100], uselesstime[100], date[20];
  sprintf(place, "%s%d/%d condition.txt", FILE_PATH, p_ID, p_ID);
  sprintf(place_ID, "%s%d/%d ID.txt", FILE_PATH, p_ID, p_ID);

  fileptr = fopen(place, "a+");
  fileptr_ID = fopen(place_ID, "r");

  while(fgets(patient_data, PRINT_DATA_SIZE, fileptr) != NULL)
  {
    if(feof(fileptr))
      break;
  }

  fgets(patient_ID, PRINT_DATA_SIZE, fileptr_ID);
  sscanf(patient_ID, " %d, %[^,], %lld, %[^\n]", &ID, useless, &cprNumber, useless);


  sscanf(patient_data, " %[^|] | %lf | %lf | %lf | %d | %lf | %s", uselesstime, &personLog.weight, &personLog.height, &personLog.bmi, &personLog.bmr, &personLog.temperature, personLog.illness);

  /*Måske lave de næste 23 linjer til en funktion*/
  choice = RESET_OPTION;
  while (choice != 0)
  {
    while (choice != 1 && choice != 0)
    {
      clear();
      printf("Main Menu/Patient Menu/Update patient data/Weight Update\n Patient #%d\n\n *enter the new weight\n *Press 0 to go back to Patient_menu\n\n>", p_ID);
      scanf("\n%lf", &weight);

      if (weight == 0)
        break;

      datestamp(date);

      personLog.weight = weight;
      personLog.bmi = BMI(personLog.height, personLog.weight);
      personLog.bmr = BMR(personLog.height, personLog.weight, cprNumber);

      fprintf(fileptr, "\n%18s | %6.1lf |  %3.1lf | %3.1lf | %5d | %4.1lf | %9s |", date, personLog.weight, personLog.height, personLog.bmi, personLog.bmr, personLog.temperature, personLog.illness);
      fclose(fileptr);

      print_warning(personLog.bmi);
      printf("\nThe new patient weight is registered\n *Press 0 to go back to Patient_menu\n\n>");
      scanf("\n%d", &choice);
      while(choice != 0)
      {
        printf("*Press 0 to go back to Patient_menu\n\n>");
        scanf("\n%d", &choice);
      }
    }
  }
  return;
}


void p_intake(indexPos *indexArr, int p_ID, int indLen)
{
  /*Scan new intake*/
  int choice;
  nutrition *meal;
  char dataFile[] = "Nutritional_database.txt";
  FILE *dtb;

  clear();
  printf("Main Menu/Patient Menu/Update patient data/New Intake\n Patient #%d\n\n *Press 1 to insert new intake  \n *Press 0 to go back to Patient_menu\n\n>",  p_ID);
  scanf("\n%d", &choice);

  if (choice != 0)
  {
    /* Open the database file and check if open */
    dtb = fopen(dataFile, "r+");
    if(dtb == NULL)
    {
      printf("No database with name \"%s\" exists!\n", dataFile);
      exit(EXIT_FAILURE);
    }



  	/* Ask for ingredient */
  	meal = ingredient_prompt(indLen, indexArr, dtb);
  	printf("Dish name: %s \nKiloJoules: %d kJ \nProtein: %g g\nFat: %g g\nNo: %d ingredients\n",
  		   meal[0].ingredient, meal[0].kiloJoule, meal[0].protein, meal[0].fat, meal[0].noIngredients);

  	/* Free all dynamically allocated arrays, and close database */

    printf("\nPatient intake is registered\n *Press 0 to go back to Patient_menu\n\n>");
    scanf("\n%d", &choice);
    while (choice != 0)
    {
      printf("*Press 0 to go back to Patient_menu\n\n>");
      scanf("\n%d", &choice);
    }
  }

  /*
   * Param indLen is the length of the index array. Returned by the function as a parameter.
   * Param dtb is the pointer to the database file.*/
  add_food_intake(p_ID, meal);
  free(meal);

  return;
}


void p_change(int p_ID)
{
  /*Change patient data/info*/
  int ID, choice;
  long long int cprNumber;
  FILE *fileptr, *fileptr_ID;
  conditionHistory personLog;
  char place[30], place_ID[30], patient_data[100], useless[30], patient_ID[100], uselesstime[100], date[20];

  sprintf(place, "%s%d/%d condition.txt", FILE_PATH, p_ID, p_ID);
  sprintf(place_ID, "%s%d/%d ID.txt", FILE_PATH, p_ID, p_ID);

  fileptr = fopen(place, "a+");
  fileptr_ID = fopen(place_ID, "r");
  while(fgets(patient_data, PRINT_DATA_SIZE, fileptr) != NULL)
  {
    if(feof(fileptr))
      break;
  }

  fgets(patient_ID, PRINT_DATA_SIZE, fileptr_ID);

  sscanf(patient_data, " %[^|] | %lf | %lf | %lf | %d | %lf | %s", uselesstime, &personLog.weight, &personLog.height, &personLog.bmi, &personLog.bmr, &personLog.temperature, personLog.illness);
  sscanf(patient_ID, " %d, %[^,], %lld, %[^\n]", &ID, useless, &cprNumber, useless);

  clear();

  printf("Main Menu/Patient Menu/Update patient data/Change patient data/info \n Patient #%d\n\n*Press 1 to insert updated patient info\n*Press 0 to go back to Patient_menu\n\n>", p_ID);
  scanf("%d", &choice);
  if (choice != 0){
    clear();
    printf("Main Menu/Patient Menu/Update patient data/Change patient data/info \n Patient #%d\n", p_ID);
    printf("Enter updated info in the order: weight, height, temperature, illness og allergy\n\n"
    "Persondata foer aendring:\n\n| Weight | Height | Temp |   Illness |\n"
    "| %6g | %6g | %4g | %9s |\n\nEnter the new information:\n>",  personLog.weight, personLog.height, personLog.temperature, personLog.illness);

    scanf("\n%lf %lf %lf %s",&personLog.weight, &personLog.height, &personLog.temperature, personLog.illness);

    datestamp(date);
    /*Note at der er forskel på personLog og person
    * Det skal højst sandsynligt ændres!
    * ELler skal det?
    *
    */
    printf("|%s\n", "Persondata efter aendring:");
    printf("\n| %g | %g | %g | %s |", personLog.weight, personLog.height, personLog.temperature, personLog.illness);
    personLog.bmi = BMI(personLog.height, personLog.weight);
    personLog.bmr = BMR(personLog.height, personLog.weight, cprNumber);
    fprintf(fileptr, "\n%18s | %6.1lf |  %3.1lf | %3.1lf | %5d | %4.1lf | %9s |", date, personLog.weight, personLog.height, personLog.bmi, personLog.bmr, personLog.temperature, personLog.illness);
    fclose(fileptr);

    print_warning(personLog.bmi);
    printf("\n\nPatient info is updated\n");
    while(choice!=0)
    {
      printf("*Press 0 to go back to Patient menu\n\n>");
      scanf("\n%d", &choice);
    }
  }
  return;
}


void p_print(int p_ID)
{
  /*Print patient data*/
  FILE *fileptr, *fileptr_log;
  int choice;
  char place[30],  patient_data[200], place_log[30], patient_data_log[200];
  choice = RESET_OPTION;

  sprintf(place, "%s%d/%d ID.txt", FILE_PATH, p_ID, p_ID);
  sprintf(place_log, "%s%d/%d condition.txt", FILE_PATH, p_ID, p_ID);

  fileptr = fopen(place, "r");
  fileptr_log = fopen(place_log, "r");


  fgets(patient_data, PRINT_DATA_SIZE, fileptr);
  while(fgets(patient_data_log, PRINT_DATA_SIZE, fileptr_log)!=NULL)
  {
    if (feof(fileptr_log))
      break;
  }

  fclose(fileptr);
  fclose(fileptr_log);

  clear();
  printf("Main Menu/Patient Menu/Print patient info\n Patient #%d\n\n",  p_ID);
  printf("%s\n", patient_data);

  printf("|       Date        | Weight | Height |  BMI |   BMR | Temp |   Illness |\n|%s\n\n", patient_data_log);

  while(choice != 0)
  {
    printf("*Press 0 to return to patient menu\n\n>");
    scanf("\n%d", &choice);
  }

  return;
}

int p_discharge(int p_ID)
{
  int choice;
  choice = RESET_OPTION;
  clear();
  printf("Main Menu/Patient Menu/Discharging a patient\n Patient #%d\n\n *Press 1 to discharge patient \n\n *Press 0 to go back to Patient_menu\n\n>", p_ID);
  scanf("\n%d", &choice);

  while (choice != 1 &&  choice != 0)
  {
    printf("Please enter a valid choice\n");
    scanf("\n%d", &choice);
  }

  if (choice == 1)
  {
    /*Udskrivning af patient (Discharge, ikke print)*/
    clear();
    printf("Discharging patient #%d ....\n Discharge complete, Press 0 to return to main menu\n>", p_ID);
    scanf("\n%d", &choice);

    while (choice != 0)
    {
      printf("*Press 0 to return to main menu\n>", p_ID);
      scanf("\n%d", &choice);
    }
    return 0;
  }

  else if (choice == 0)
  {
    return RESET_OPTION;
  }
}

/////////////////////////////
