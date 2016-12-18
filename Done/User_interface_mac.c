#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <direct.h>
#include "user_interface_mac.h"

int main (void){
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

/* Main menu lets you have 3 choices; create new patient, access existing patient and exit*/
void p_main_menu(indexPos *indexArr, int indLen)
{

  int choice;
  choice = 4;


  while(choice != 0)
  {
    while (choice != 1 && choice != 2 && choice != 0)
      {
        clear();
        printf("Main Menu\nWelcome,\n\n *Press 1 to create new patient\n *Press 2 to access patient menu\n\n *Press 0 to exit \n\n>");
        scanf("\n%d", &choice);
      }
    switch (choice)
    {
      case 1:
      p_new_patient(indexArr, indLen);
      choice = RESET_OPTION;
      break;

      case 2:
      p_existing_patient(indexArr, indLen);
      choice = RESET_OPTION;
      break;
    }
  }
  return;
}

/*The function scans ands stores for a new patient and prints a warning if BMI is too low, it redirects to p_main_menu
  when it is done creating new patient*/
void p_new_patient(indexPos *indexArr, int indLen)
{
  clear();
  /*Promt for input to new patient*/
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

/*Function acceses existing patient through ID and redirects to p_main_menu*/
void p_existing_patient(indexPos *indexArr, int indLen)
{
  int patientID;
  clear();
  printf("Main Menu/Patient Menu\n\n Enter patient ID\n>");
  scanf("\n%d", &patientID);
  p_patient_menu(indexArr, patientID, indLen);

  return;
}

/*p_patient_menu is the menu for the patient, it lets you have 4 choices; edit patient information,
  read patient information, discharge patient and exit*/
void p_patient_menu(indexPos *indexArr, int patientID, int indLen)
{
  int choice;
  choice = RESET_OPTION;
  clear();
  printf("Main Menu/Patient Menu\n Patient #%d\n\n You have 4 choices.\n *Press 1 to edit/add patient data\n *Press 2 to read patient date\n *Press 3 to discharge patient\n\n *Press 0 to go back to Main Menu\n\n>", patientID);


  while(choice != 0)
  {
    while (choice != 1 && choice != 2 && choice != 3 && choice != 0) {
      clear();
      printf("Main Menu/Patient Menu\n Patient #%d\n\n You have 4 choices.\n *Press 1 to edit/add patient data\n *Press 2 to read patient date\n *Press 3 to discharge patient\n\n *Press 0 to go back to Main Menu\n\n>", patientID);
      scanf("\n%d", &choice);
  }
    switch (choice)
    {
      case 1:
        p_update(indexArr, patientID, indLen);
        choice = RESET_OPTION;
        break;
      case 2:
        p_print(patientID);
        choice = RESET_OPTION;
        break;
      case 3:
        choice = p_discharge(patientID);
        break;
    }
  }
  return;
}

/*The function lets you have 3 choices; update weight, enter new intake, change patient information or go back to patient menu*/
void p_update(indexPos *indexArr, int patientID, int indLen){
  int choice;
  choice = RESET_OPTION;

  while(choice != 0){
    while (choice != 1 && choice != 2 && choice != 3 && choice != 0)
    {
      clear();
      printf("Main Menu/Patient Menu/Update patient data\n Patient #%d\n\n You have 4 choices\n *Press 1 to enter new weight\n *Press 2 to enter new intake\n *Press 3 to change patient info\n\n *Press 0 to go back to Patient menu\n\n>", patientID);
      scanf("\n%d", &choice);
    }
      switch (choice)
      {
        case 1:
          p_weight(patientID);
          choice = RESET_OPTION;
          break;
        case 2:
          p_intake(indexArr, patientID, indLen);
          choice = RESET_OPTION;
          break;
        case 3:
          p_change(patientID);
          choice = RESET_OPTION;
          break;
      }
  }
  return;
}

/*The function scans for new weight and updates patientLog for weight BMI and BMR and adds a timestamp for
  the change in the stored file contiont.txt*/
void p_weight(int patientID)
{
  /*Scan new weight*/
  int choice, ID;
  long long int cprNumber;
  double weight;
  conditionHistory personLog;
  FILE *fileptr, *fileptr_ID;
  char place[30], place_ID[30], patient_data[100], useless[30], patient_ID[100], uselesstime[100], date[20];
  sprintf(place, "%s%d/%d condition.txt", FILE_PATH, patientID, patientID);
  sprintf(place_ID, "%s%d/%d ID.txt", FILE_PATH, patientID, patientID);

  fileptr = fopen(place, "a+");
  fileptr_ID = fopen(place_ID, "r");

  while(fgets(patient_data, PRINT_DATA_SIZE, fileptr) != NULL)
  {
    if(feof(fileptr))
      break;
  }

  fgets(patient_ID, PRINT_DATA_SIZE, fileptr_ID);
  sscanf(patient_ID, " %d, %[^,], %lld, %[^\n]", &ID, useless, &cprNumber, useless);


  sscanf(patient_data, " %[^|] | %lf | %lf | %lf | %d | %lf | %s", uselesstime, &personLog.weight, &personLog.height,
        &personLog.bmi, &personLog.bmr, &personLog.temperature, personLog.illness);


  choice = RESET_OPTION;
  while (choice != 0)
  {
    while (choice != 1 && choice != 0)
    {
      clear();
      printf("Main Menu/Patient Menu/Update patient data/Weight Update\n Patient #%d\n\n *enter the new weight\n *Press 0 to go back to Patient_menu\n\n>", patientID);
      scanf("\n%lf", &weight);

      if (weight == 0)
        break;

      datestamp(date);

      /*Update BMI and BMR after the new weight*/
      personLog.weight = weight;
      personLog.bmi = BMI(personLog.height, personLog.weight);
      personLog.bmr = BMR(personLog.height, personLog.weight, cprNumber);

      fprintf(fileptr, "\n%18s | %6.1lf |  %3.1lf | %3.1lf | %5d | %4.1lf | %9s |", date, personLog.weight,
             personLog.height, personLog.bmi, personLog.bmr, personLog.temperature, personLog.illness);
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


/*The intake is scanned and found through ingredient_prompt, and added to the file IntakeLog and */
void p_intake(indexPos *indexArr, int patientID, int indLen)
{
  /*Scan new intake*/
  int choice;
  nutrition *meal;
  char dataFile[] = "Nutritional_database.txt";
  FILE *dtb;

  clear();
  printf("Main Menu/Patient Menu/Update patient data/New Intake\n Patient #%d\n\n *Press 1 to insert new intake  \n *Press 0 to go back to Patient_menu\n\n>",  patientID);
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

  /* Param indLen is the length of the index array. Returned by the function as a parameter.
     Param dtb is the pointer to the database file.*/
  add_food_intake(patientID, meal);
  free(meal);

  return;
}

/*The function updates the information found in condition.txt by adding a new line based on the scanned input and the date
  the newest line in condition.txt will be the current updated information*/
void p_change(int patientID)
{
  /*Change patient data/info*/
  int ID, choice;
  long long int cprNumber;
  FILE *fileptr, *fileptr_ID;
  conditionHistory personLog;
  char place[30], place_ID[30], patient_data[100], useless[30], patient_ID[100], uselesstime[100], date[20];

  sprintf(place, "%s%d/%d condition.txt", FILE_PATH, patientID, patientID);
  sprintf(place_ID, "%s%d/%d ID.txt", FILE_PATH, patientID, patientID);

  /* Gets the current information, from condition.txt, and the patient cprNumber from ID.txt*/
  fileptr = fopen(place, "a+");
  fileptr_ID = fopen(place_ID, "r");
  while(fgets(patient_data, PRINT_DATA_SIZE, fileptr) != NULL)
  {
    if(feof(fileptr))
      break;
  }

  fgets(patient_ID, PRINT_DATA_SIZE, fileptr_ID);

  sscanf(patient_data, " %[^|] | %lf | %lf | %lf | %d | %lf | %s", uselesstime, &personLog.weight, &personLog.height,
        &personLog.bmi, &personLog.bmr, &personLog.temperature, personLog.illness);

  /*We are interested in the patient cprNumber, for calculating the BMR */
  sscanf(patient_ID, " %d, %[^,], %lld, %[^\n]", &ID, useless, &cprNumber, useless);

  clear();

  printf("Main Menu/Patient Menu/Update patient data/Change patient data/info \n Patient #%d\n\n*Press 1 to insert updated patient info\n*Press 0 to go back to Patient_menu\n\n>", patientID);
  scanf("%d", &choice);
  if (choice != 0){
    clear();
    printf("Main Menu/Patient Menu/Update patient data/Change patient data/info \n Patient #%d\n", patientID);
    printf("Enter updated info in the order: weight, height, temperature, illness og allergy\n\n"
    "Persondata foer aendring:\n\n| Weight | Height | Temp |   Illness |\n"
    "| %6g | %6g | %4g | %9s |\n\nEnter the new information:\n>",  personLog.weight, personLog.height, personLog.temperature, personLog.illness);

    /*Scanning for new info*/
    scanf("\n%lf %lf %lf %s",&personLog.weight, &personLog.height, &personLog.temperature, personLog.illness);

    datestamp(date);

    printf("|%s\n", "Persondata efter aendring:");
    printf("\n| %g | %g | %g | %s |", personLog.weight, personLog.height, personLog.temperature, personLog.illness);

    /*Updates BMI and BMR*/
    personLog.bmi = BMI(personLog.height, personLog.weight);
    personLog.bmr = BMR(personLog.height, personLog.weight, cprNumber);
    fprintf(fileptr, "\n%18s | %6.1lf |  %3.1lf | %3.1lf | %5d | %4.1lf | %9s |", date, personLog.weight, personLog.height,
           personLog.bmi, personLog.bmr, personLog.temperature, personLog.illness);
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

/*The function simply retieves the line of information from ID.txt and the newest line from condition.txt
and prints it*/
void p_print(int patientID)
{
  /*Print patient data*/
  FILE *fileptr, *fileptr_log;
  int choice;
  char place[30],  patient_data[200], place_log[30], patient_data_log[200];
  choice = RESET_OPTION;

  sprintf(place, "%s%d/%d ID.txt", FILE_PATH, patientID, patientID);
  sprintf(place_log, "%s%d/%d condition.txt", FILE_PATH, patientID, patientID);

  fileptr = fopen(place, "r");
  fileptr_log = fopen(place_log, "r");

  /*Scans the patient info from file into string*/
  fgets(patient_data, PRINT_DATA_SIZE, fileptr);
  while(fgets(patient_data_log, PRINT_DATA_SIZE, fileptr_log)!=NULL)
  {
    if (feof(fileptr_log))
      break;
  }

  fclose(fileptr);
  fclose(fileptr_log);

  clear();
  printf("Main Menu/Patient Menu/Print patient info\n Patient #%d\n\n",  patientID);
  printf(" ID# %s\n", patient_data);

  printf("|       Date        | Weight | Height |  BMI |   BMR | Temp |   Illness |\n|%s\n\n", patient_data_log);

  while(choice != 0)
  {
    printf("*Press 0 to return to patient menu\n\n>");
    scanf("\n%d", &choice);
  }

  return;
}

/*This function does not discharge patients, but is only the prompt function/userinterface that allows it.
  If the user choses the to discharge a patien, the user then returns to main menu*/
int p_discharge(int patientID)
{
  int choice;
  choice = RESET_OPTION;
  clear();
  printf("Main Menu/Patient Menu/Discharging a patient\n Patient #%d\n\n *Press 1 to discharge patient \n\n *Press 0 to go back to Patient_menu\n\n>", patientID);
  scanf("\n%d", &choice);

  while (choice != 1 &&  choice != 0)
  {
    printf("Please enter a valid choice\n");
    scanf("\n%d", &choice);
  }

  if (choice == 1)
  {
    /*Discharging patient*/
    clear();
    printf("Discharging patient #%d ....\n Discharge complete, Press 0 to return to main menu\n>", patientID);
    scanf("\n%d", &choice);

    while (choice != 0)
    {
      printf("*Press 0 to return to main menu\n>");
      scanf("\n%d", &choice);
    }
    return 0;
  }
  return RESET_OPTION;
}
