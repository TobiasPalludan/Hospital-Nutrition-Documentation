#include <stdio.h>
#include <stdlib.h>

#define DEPARTMENT_SIZE 15
#define NAME_SIZE 30
#define ALLERGY_SIZE 50
#define PREFERENCES_SIZE 100

typedef struct PersonInfo {
	int id;
	char department[DEPARTMENT_SIZE];
	int cprNumber;
	char name[NAME_SIZE];
	int height;
	char allergy[ALLERGY_SIZE];
	char preferences[PREFERENCES_SIZE];
}PersonInfo;

typedef struct foodIntake {
	char *dishName;
	char *indgredients;
	int totalKJ;
	int percentageEaten;
}foodIntake;

int main(void)
{

}