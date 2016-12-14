/* In progress*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define clear() system("cls")

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
  int p_ID;
  clear();
  /*Promt for input til ny patient*/
  printf("Enter ID for new patient\n\n>");
  scanf("\n%d", &p_ID);

  p_patient_menu(p_ID);
}

void p_existing_patient(){
  int p_ID;
  clear();
  /*  int p_ID;
    clear();
    scanf("%d\n", p_ID);*/
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
  clear();
  printf("Main Menu/Patient Menu/Update patient data/Weight Update\n Patient #%d\n\n Insert new weight or press 0 to go back to Patient_menu\n\n>", p_ID);
  scanf("\n%d", &choice);

  if (choice != 0){
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
  int choice;
  clear();
  printf("Main Menu/Patient Menu/Update patient data/Change patient data/info \n Patient #%d\n\n Insert updated patient info or press 0 to go back to Patient_menu\n\n>", p_ID);
  scanf("\n%d", &choice);

  if (choice != 0){
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
  int choice;
  clear();
  printf("Main Menu/Patient Menu/Print patient info\n Patient #%d\n\n Vi printer noget patient data\n\n *press 0 to return to patient menu\n\n>",  p_ID);
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
