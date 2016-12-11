#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct graphSet
{
	/* Time */
	int day;
	int month;
	int year;

	/* Nutritional information */
	int kJEaten;

	/* Graph information */
	int xCoor;
	int yCoor;
} graphSet;

void produce_graph( graphSet *test );

int main (void)
{

	graphSet test[5];/* = {10, 12, 2016, 2500},
	{10, 12, 2016, 1939},
	{10, 12, 2016, 3398},
	{10, 12, 2016, 3671},
	10, 12, 2016, 2038};*/

	produce_graph(test);

	return 0;
}

void produce_graph( graphSet *test )
{
	int i, u;
	FILE *image_file;
	int r, g, b;
	int diff;

	image_file = fopen("graphTest.pnm", "wb");

	fputs("P6\n", image_file); 
	fputs("500 500\n", image_file);
	fputs("255\n", image_file);

	for(i = 0; i < 500; i++)
	{
		for(u = 0; u < 500; u++)
		{
			r = 0; g = 0; b = 0;
      		fputc(r, image_file);
      		fputc(g, image_file);
      		fputc(b, image_file);
		}
	}

	struct tm start_date;
  struct tm end_date;
  time_t start_time, end_time;
  double seconds;

  start_date.tm_hour = 0;  start_date.tm_min = 0;  start_date.tm_sec = 0;
  start_date.tm_mon = 1; start_date.tm_mday = 20; start_date.tm_year = 2016;

  end_date.tm_hour = 0;  end_date.tm_min = 0;  end_date.tm_sec = 0;
  end_date.tm_mon = 1; end_date.tm_mday = 30; end_date.tm_year = 2016;

  start_time = mktime(&start_date);
  end_time = mktime(&end_date);

  seconds = difftime(end_time, start_time);

  printf ("%.f seconds difference\n", seconds);

}