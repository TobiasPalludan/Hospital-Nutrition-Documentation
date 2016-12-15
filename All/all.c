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
void p_main_menu(indexPos *indexArr);
void p_new_patient(indexPos *indexArr);
void p_existing_patient(indexPos *indexArr);
void p_patient_menu(indexPos *indexArr, int p_ID);
void p_update(indexPos *indexArr, int p_ID);
void p_weight(int p_ID);
void p_intake(indexPos *indexArr, int p_ID);
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

  p_main_menu(indexArr);
  clear();
  free(indexArr);
  fclose(dtb);
  return 0;
}

void p_main_menu(indexPos *indexArr){

  int choice;
  choice = 4;


  while(choice != 0){
      while (choice != 1 && choice != 2 && choice != 0) {
        clear();
        printf("Main Menu\nWelcome,\n\n *press 1 to create new patient\n *press 2 to access patient menu\n\n *press 0 to exit \n\n>");
        scanf("\n%d", &choice);
      }

      if (choice == 1){
        p_new_patient(indexArr);
        choice = RESET_OPTION;
      }

      else if (choice == 2){
        p_existing_patient(indexArr);
        choice = RESET_OPTION;
      }
    }
  return;
}

void p_new_patient(indexPos *indexArr){
  clear();
  /*Promt for input til ny patient*/
  /*Hardcoded*/
  personInfo person;
	conditionHistory personLog;

  printf("Enter variables in order: Department, CPRnumber, Name, Allergy, Illnes, Weight, Height, Temperature\n");
  scanf("\n%s %lld %s %s %s %lf %lf %lf", person.department, &person.cprNumber, person.name, person.allergy, person.illness, &personLog.weight,
                                          &personLog.height, &personLog.temperature);
  strcpy(personLog.allergy, person.allergy);
  strcpy(personLog.illness, person.illness);

	add_person(&person);
	add_condition_log(person, personLog);

  p_patient_menu(indexArr, person.id);
  return;
}

void p_existing_patient(indexPos *indexArr){
  int p_ID;
  clear();
  printf("Main Menu/Patient Menu\n\n Enter patient ID\n>");
  scanf("\n%d", &p_ID);
  p_patient_menu(indexArr, p_ID);
  return;
}


void p_patient_menu(indexPos *indexArr, int p_ID){
  int choice;
  choice = RESET_OPTION;
  clear();
  printf("Main Menu/Patient Menu\n Patient #%d\n\n You have 4 choices.\n *press 1 to edit/add patient data\n *press 2 to read patient date\n *press 3 to discharge patient\n\n *press 0 to go back to Main Menu\n\n>", p_ID);


  while(choice != 0){
    while (choice != 1 && choice != 2 && choice != 3 && choice != 0) {
      clear();
      printf("Main Menu/Patient Menu\n Patient #%d\n\n You have 4 choices.\n *press 1 to edit/add patient data\n *press 2 to read patient date\n *press 3 to discharge patient\n\n *press 0 to go back to Main Menu\n\n>", p_ID);
      scanf("\n%d", &choice);
      }

    if (choice == 1){
      p_update(indexArr, p_ID);
      choice = RESET_OPTION;
    }

    else if (choice == 2){
      p_print(p_ID);
      choice = RESET_OPTION;
    }

    else if (choice == 3){
      choice = p_discharge(p_ID);
    }
  }
  return;
}


void p_update(indexPos *indexArr, int p_ID){
  int choice;
  choice = RESET_OPTION;

  while(choice != 0){
    while (choice != 1 && choice != 2 && choice != 3 && choice != 0) {
      clear();
      printf("Main Menu/Patient Menu/Update patient data\n Patient #%d\n\n You have 4 choices\n *press 1 to enter new weight\n *press 2 to enter new intake\n *press 3 to change patient info\n\n *press 0 to go back to Patient menu\n\n>", p_ID);
      scanf("\n%d", &choice);
      }

      if (choice == 1)
      {
        p_weight(p_ID);
        choice = RESET_OPTION;
      }

      else if (choice == 2)
      {
        p_intake(indexArr, p_ID);
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

void p_weight(int p_ID){
  /*Scan new weight*/
  int choice;
  double weight;
  conditionHistory person;
  FILE* fileptr;
  char place[30], patient_data[100], uselesstime[100], date[20];
  sprintf(place, "%s%d/%d condition.txt", FILE_PATH, p_ID, p_ID);

  fileptr = fopen(place, "a+");

  while(fgets(patient_data, PRINT_DATA_SIZE, fileptr) != NULL)
  {
    if(feof(fileptr))
    {
      break;
    }
  }


  sscanf(patient_data, " %[^|] | %lf | %lf | %lf | %d | %lf | %s | %s", uselesstime, &person.weight, &person.height, &person.bmi, &person.bmr, &person.temperature, person.illness, person.allergy);

  /*Måske lave de næste 23 linjer til en funktion*/
  choice = RESET_OPTION;
  while (choice != 0){
    while (choice != 1 && choice != 0) {
    clear();
    printf("Main Menu/Patient Menu/Update patient data/Weight Update\n Patient #%d\n\n *press 1 to enter new weight\n *press 0 to go back to Patient_menu\n\n>", p_ID);
    scanf("\n%d", &choice);
    }

    if (choice == 1){
      printf("Enter new weight press 0 to cancel\n>");
      scanf("\n%lf", &weight);

      if (weight == 0)
      break;

      datestamp(date);
      person.weight = weight;
      fprintf(fileptr, "\n%s | %.2lf | %.2lf | %.2lf | %d | %.2lf | %s | %s", date, person.weight, person.height, person.bmi, person.bmr, person.temperature, person.illness, person.allergy);
      fclose(fileptr);

      printf("\nThe new patient weight is registered\n *press 0 to go back to Patient_menu\n\n>");
      scanf("\n%d", &choice);
    }
  }

  return;
}

void p_intake(indexPos *indexArr, int p_ID){
  /*Scan new intake*/
  int choice, indLen = 0;
  nutrition *meal;
  char dataFile[] = "Nutritional_database.txt";
  FILE *dtb;

  clear();
  printf("Main Menu/Patient Menu/Update patient data/New Intake\n Patient #%d\n\n Insert new intake or press 0 to go back to Patient_menu\n\n>",  p_ID);
  scanf("\n%d", &choice);

  if (choice != 0){
    /* Open the database file and check if open */
    dtb = fopen(dataFile, "r+");
    if(dtb == NULL)
    {
      printf("No database with name \"%s\" exists!\n", dataFile);
      exit(EXIT_FAILURE);
    }



  	/* Ask for ingredient */
  	meal = ingredient_prompt(indLen, indexArr, dtb);
  	printf("Dish name: %s \nKiloJoules: %d kJ \nProtein: %g g \nWeight: %g g\nNo: %d ingredients\n",
  		   meal[0].ingredient, meal[0].kiloJoule, meal[0].protein, meal[0].weight, meal[0].noIngredients);

  	/* Free all dynamically allocated arrays, and close database */

    printf("\nPatient intake is registered\n *press 0 to go back to Patient_menu\n\n>");
    scanf("\n%d", &choice);
    while (choice != 0){
      printf("*press 0 to go back to Patient_menu\n\n>");
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

void p_change(int p_ID){
  /*Change patient data/info*/
  FILE* fileptr;
  personInfo person;
  int choice;
  char place[30], patient_data[100], uselesstime[100], date[20];

  sprintf(place, "%s%d/%d condition.txt", FILE_PATH, p_ID, p_ID);

  fileptr = fopen(place, "a+");

  while(fgets(patient_data, PRINT_DATA_SIZE, fileptr) != NULL)
  {
    if(feof(fileptr))
    {
      break;
    }
  }

  clear();
  sscanf(patient_data, " %[^|] | %lf | %lf | %lf | %d | %lf | %s | %s", uselesstime, &person.weight, &person.height, &person.bmi, &person.bmr, &person.temperature, person.illness, person.allergy);

  printf("Main Menu/Patient Menu/Update patient data/Change patient data/info \n Patient #%d\n\n*press 1 to insert updated patient info\n*press 0 to go back to Patient_menu\n\n>", p_ID);
  scanf("%d", &choice);
  if (choice != 0){
    clear();
    printf("Main Menu/Patient Menu/Update patient data/Change patient data/info \n Patient #%d\n", p_ID);
    printf("Enter updated info in the order: weight, height, temperature, illness og allergy\n\n"
    "Persondata foer aendring:\n\n| Weight | Height | Temp |  Illness  |  Allergy  |\n"
    "| %6g | %6g | %4g | %9s | %9s |\n\nEnter the new information:\n>",  person.weight, person.height, person.temperature, person.illness, person.allergy);

    scanf("\n%lf %lf %lf %s %s",&person.weight, &person.height, &person.temperature, person.illness, person.allergy);

    datestamp(date);

    printf("|%s\n", "Persondata efter aendring:");
    printf("\n| %g | %g | %g | %s | %s |", person.weight, person.height, person.temperature, person.illness, person.allergy);
    person.bmi = BMI(person.height, person.weight);
    person.bmr = BMR(person.height, person.weight, person.cprNumber);
    fprintf(fileptr, "\n %s | %6g | %6g | %5.1lf | %5d | %4g | %9s | %9s |", date, person.weight, person.height, person.bmi, person.bmr, person.temperature, person.illness, person.allergy);
    fclose(fileptr);

    printf("\n\nPatient info is updated\n");
    while(choice!=0){
      printf("*press 0 to go back to Patient menu\n\n>");
      scanf("\n%d", &choice);
      }
    }
  return;
}


void p_print(int p_ID){
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
  while(fgets(patient_data_log, PRINT_DATA_SIZE, fileptr_log)!=NULL){
    if (feof(fileptr_log))
    break;
    }

  fclose(fileptr);
  fclose(fileptr_log);

  clear();
  printf("Main Menu/Patient Menu/Print patient info\n Patient #%d\n\n",  p_ID);
  printf("%s\n", patient_data);

  printf("|       Date       | Weight |   Height |   BMI |  BMR  | Temp |   Illness |   Allergy |\n|%s\n\n", patient_data_log);

  while(choice != 0){
    printf("*press 0 to return to patient menu\n\n>");
    scanf("\n%d", &choice);
    }

  return;
}

int p_discharge(int p_ID){
  int choice;
  choice = RESET_OPTION;
  clear();
  printf("Main Menu/Patient Menu/Discharging a patient\n Patient #%d\n\n *press 1 to discharge patient \n\n *press 0 to go back to Patient_menu\n\n>", p_ID);
  scanf("\n%d", &choice);

  while (choice != 1 &&  choice != 0) {
    printf("Please enter a valid choice\n");
    scanf("\n%d", &choice);
  }

  if (choice == 1){
    /*Udskrivning af patient (Discharge, ikke print)*/
    clear();
    printf("Discharging patient #%d ....\n Discharge complete, press 0 to return to main menu\n>", p_ID);
    scanf("\n%d", &choice);

    while (choice != 0){
      printf("*press 0 to return to main menu\n>", p_ID);
      scanf("\n%d", &choice);
      }
    return 0;
  }

  else if (choice == 0){
    return RESET_OPTION;
  }
}

/////////////////////////////
