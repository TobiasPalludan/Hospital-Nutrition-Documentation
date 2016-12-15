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

#define FILE_PATH "patients/"
#define INDEX_FILE_NAME "PatientIndex.txt"
#define clear() system("cls")

/* Userinterface prototypes*/
void p_main_menu();
void p_new_patient();
void p_existing_patient();
void p_patient_menu();
void p_update();
void p_weight();
void p_intake();
void p_change();
void p_print();
void p_discharge();



int
main (void){
  p_main_menu();
  return 0;
}

void p_main_menu(){

  int choice = 9;
  while(choice != 0)
  {
    choice = 9;
    clear();
    printf("Main Menu\nWelcome,\n\n *press 1 to create new patient\n *press 2 to access patient menu\n\n *press 0 to exit \n\n>");
    scanf("\n%d", &choice);

    while (choice != 1 && choice != 2 && choice != 0) {
      printf("Please enter a valid choice\n");
      scanf("\n%d", &choice);
    }

    if (choice == 1){
      p_new_patient();
    }

    else if (choice == 2){
      p_existing_patient();
    }

    else if (choice == 0){
      clear();
    }
  }
}
void p_new_patient(){
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

  p_patient_menu(person.id);
}

void p_existing_patient(){
  int p_ID;
  clear();
  printf("Main Menu/Patient Menu\n\n Enter patient ID\n>");
  scanf("\n%d", &p_ID);
  p_patient_menu(p_ID);
}


void p_patient_menu(int p_ID){
  int choice;
  clear();
  printf("Main Menu/Patient Menu\n Patient #%d\n\n You have 4 choices.\n *press 1 to edit/add patient data\n *press 2 to read patient date\n *press 3 to discharge patient\n\n *press 0 to go back to Main Menu\n\n>", p_ID);
  scanf("\n%d", &choice);
  while (choice != 1 && choice != 2 && choice != 3 && choice != 0) {
    printf("Please enter a valid choice\n");
    scanf("\n%d", &choice);
  }

  if (choice == 1){
    p_update(p_ID);
  }

  if (choice == 2){
    p_print(p_ID);
  }

  if (choice == 3){
    p_discharge(p_ID);
  }

  if (choice == 0){
    p_main_menu(p_ID);
  }
}



void p_update(int p_ID){
  int choice;
  clear();
  printf("Main Menu/Patient Menu/Update patient data\n Patient #%d\n\n You have 4 choices\n *press 1 to enter new weight\n *press 2 to enter new intake\n *press 3 to change patient info\n\n *press 0 to go back to Patient menu\n\n>", p_ID);
  scanf("\n%d", &choice);

  while (choice != 1 && choice != 2 && choice != 3 && choice != 0) {
    printf("Please enter a valid choice\n");
    scanf("\n%d", &choice);
  }

  if (choice == 1){
    p_weight(p_ID);
  }

  if (choice == 2){
    p_intake(p_ID);
  }

  if (choice == 3){
    p_change(p_ID);
  }

  if (choice == 0){
    p_patient_menu(p_ID);
  }
}

void p_weight(int p_ID){
  /*Scan new weight*/
  int choice;
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
  clear();
  printf("Main Menu/Patient Menu/Update patient data/Weight Update\n Patient #%d\n\n Insert new weight or press 0 to go back to Patient_menu\n\n>", p_ID);
  scanf("\n%d", &choice);
  
  if (choice != 0){
    datestamp(date);
    person.weight = choice;
    fprintf(fileptr, "\n%s | %.2lf | %.2lf | %.2lf | %d | %.2lf | %s | %s", date, person.weight, person.height, person.bmi, person.bmr, person.temperature, person.illness, person.allergy);
    fclose(fileptr);


    printf("\nThe new patient weight is registered\n *press 0 to go back to Patient_menu\n\n>");
    scanf("\n%d", &choice);
    if (choice == 0){
      p_patient_menu(p_ID);
    }
  }
  if (choice == 0){
    p_patient_menu(p_ID);
  }
}

void p_intake(int p_ID){
  /*Scan new intake*/
  int choice;
  clear();
  printf("Main Menu/Patient Menu/Update patient data/New Intake\n Patient #%d\n\n Insert new intake or press 0 to go back to Patient_menu\n\n>",  p_ID);
  scanf("\n%d", &choice);

  if (choice != 0){
    /*Hardcoded*/
    personInfo Casper = { 2, "afdeling 1", 1110954441, "Casper", "noddeallergi", "feber"};
    nutritionIntake feedCasper[3] = {
                      {"Kartofler med Sovs", 2000, 50.2, 150 },
                      {"Kartofler", 1500, 10.2, 100},
                      {"Sovs", 500, 40, 50 }
                    };

    add_food_intake(Casper, feedCasper);

    printf("\nPatient intake is registered\n *press 0 to go back to Patient_menu\n\n>");
    scanf("\n%d", &choice);
    if (choice == 0){
      p_patient_menu(p_ID);
    }
  }
  if (choice == 0){
    p_patient_menu(p_ID);
  }
}

void p_change(int p_ID){
  /*Change patient data/info*/
  FILE* fileptr;
  conditionHistory person;
  double choice;
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
  
  printf("Main Menu/Patient Menu/Update patient data/Change patient data/info \n Patient #%d\n\nInsert updated patient info in the order: weight, height, BMI, BMR, temperature, illness og allergy \n\n or press 0 to go back to Patient_menu", p_ID);
  printf("\n\n%s\n", "Persondata foer aendring");
  printf("\n%s\n\n>", patient_data); 
  scanf("\n%lf %lf %lf %d %lf %s %s",&choice, &person.height, &person.bmi, &person.bmr, &person.temperature, person.illness, person.allergy);

  if (choice != 0){
    person.weight = choice;
    datestamp(date);
  
    printf("%s\n", "Persondata efter aendring");
    printf("\n%s | %.2lf | %.2lf | %.2lf | %d | %.2lf | %s | %s", date, person.weight, person.height, person.bmi, person.bmr, person.temperature, person.illness, person.allergy);
 
    fprintf(fileptr, "\n%s | %.2lf | %.2lf | %.2lf | %d | %.2lf | %s | %s", date, person.weight, person.height, person.bmi, person.bmr, person.temperature, person.illness, person.allergy);
    fclose(fileptr);

    printf("\nPatient info is updated\n *press 0 to go back to Patient_menu\n\n>");
    scanf("\n%d", &choice);
    if (choice == 0){
      p_patient_menu(p_ID);
    }
  }
  if (choice == 0){
    p_patient_menu(p_ID);
  }
}


void p_print(int p_ID){
  /*Print patient data*/
  FILE *fileptr, *fileptr_log;
  int choice;
  char place[30],  patient_data[200], place_log[30], patient_data_log[200];

  sprintf(place, "%s%d/%d ID.txt\0", FILE_PATH, p_ID, p_ID);
  sprintf(place_log, "%s%d/%d condition.txt\0", FILE_PATH, p_ID, p_ID);

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
  if (fileptr_log == NULL)
  printf("NULL\n");
  printf("\nPlace : %s, Place_log: %s\n", place, place_log);
  printf("Main Menu/Patient Menu/Print patient info\n Patient #%d\n\n",  p_ID);
  printf("%s\n", patient_data);

  printf("%s\n\n", patient_data_log);
  printf("*press 0 to return to patient menu\n\n>");
  scanf("\n%d", &choice);
  if (choice == 0){
    p_patient_menu(p_ID);
  }
}

void p_discharge(int p_ID){
  int choice;
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
    if (choice == 0){
      p_main_menu(p_ID);
    }
  }

  else if (choice == 0){
    p_patient_menu(p_ID);
  }
}

/////////////////////////////
