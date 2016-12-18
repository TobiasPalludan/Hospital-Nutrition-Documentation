#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"

/* We calculate BMI from the standard equation */

/* Input: height and weight of a person
   Output: BMI of a person*/
double BMI(double height, double weight){

  height = height / 100;

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


  dateofbirth = cpr / 10000;
  n_7 = (cpr / 1000) % 10;
  year = (dateofbirth % 100) + 1900;
  temp = dateofbirth / 100;
  month = temp % 100;
  temp = temp/ 100;
  day = temp % 100;

/*If the if statement is true, the person is born in 2000 or above, but the year(birthyear) wont be above 2000 but between 1900-1999.
  Therefore we need to add 100 to year(birthyear), so the year(birthyear) will be above 2000 and thereby calculate the right age*/
  if ((n_7 == 4 || n_7 == 9) && year < 1937 )
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

  sprintf(output, "%.2d-%.2d-%.4d %.2d:%.2d", tm.tm_mday, tm.tm_mon + 1,
                tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}

/* Prints a warning depending on warning_BMI's return value*/
/* Input: return value of the function warning_BMI
   Output: No return, but will prints a sentence depending on the return value of warning_BMI*/
void print_warning(double BMI)
{
  int tilstand;
  tilstand = warning_BMI(BMI);

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
