#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Lib.h"

/* Vi udregner BMI ud fra standard formlen */
double BMI(double height, double weight){
  height = height / 100;

  return weight / (height * height);
}

/* Vi udregner BMR ud fra standard formlen og i forhold til hvilket køn */
double BMR(double height, double weight, long long int cpr){
  double BMR;
  int age;

  /* Vi henter alderen */
  age = get_age(cpr);

  /* CPR ender på et lige tal = kvinde. Ulige tal = mand. */
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

/* Vi finder alderen ud fra datoen i dag. Datoen i dag findes vha. time.h */
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

  /* Tjekker om man i nuværende år er fyldt år med måneder og dage */
  if (month > tm.tm_mon + 1)
    --age;

  else if (month == (tm.tm_mon + 1) && day > tm.tm_mday)
    --age;

  return age;
}

/* Fortæller nuværende tidspunkt med dato. */
void datestamp(char output[]){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  sprintf(output, "%d-%d-%d %d:%d:%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/* Printer advarsel afhængig af advarsel_BMI's return værdi */
void print_advarsel( FILE *filPointer, int tilstand)
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

/* Returner værdi afhængig af BMI */
int advarsel_BMI(double BMI)
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
