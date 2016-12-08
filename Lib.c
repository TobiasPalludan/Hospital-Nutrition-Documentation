#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Lib.h"

/* We calculate BMI from the standard equation */
double BMI(double height, double weight){
  height = height / 100;

  return weight / (height * height);
}

/* We calculate BMR from the standard equation and in proportion to gender */
double BMR(double height, double weight, long long int cpr){
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

  sprintf(output, "%d-%d-%d %d:%d:%d", tm.tm_mday, tm.tm_mon + 1,
                tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/* Prints a warning depending on warning_BMI's return value. */
void print_warning( FILE *filPointer, int tilstand)
{
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

/* Returns a value depending on BMI */
int warning_BMI(double BMI)
{
    if (BMI < 18.5)
        return 1;

    else if (BMI >= 25 && BMI <= 30)
        return 0;

    else if(BMI > 30)
        return -1;
    else
        return 2;
}
