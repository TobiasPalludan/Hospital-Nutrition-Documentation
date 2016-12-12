#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SEC_IN_DAY 86400

typedef struct tm tm;

typedef struct graphSet
{
	tm coorTime;

	/* Nutritional information */
	int kJEaten;

	/* Graph information */
	int xCoor;
	int yCoor;
} graphSet;

void produce_graph( graphSet *test );
int diff_in_days( tm start_date, tm end_date );
void determineCoorset(graphSet *test, int dens, int hPixels, int lPixels);

int main (void)
{
	tm start_date, end_date;

	graphSet test[5];

	test[0].coorTime.tm_mday = 20; test[0].coorTime.tm_mon = 0; test[0].coorTime.tm_year = 116;
	test[1].coorTime.tm_mday = 21; test[1].coorTime.tm_mon = 0; test[1].coorTime.tm_year = 116;
	test[2].coorTime.tm_mday = 23; test[2].coorTime.tm_mon = 0; test[2].coorTime.tm_year = 116;
	test[3].coorTime.tm_mday = 24; test[3].coorTime.tm_mon = 0; test[3].coorTime.tm_year = 116;
	test[4].coorTime.tm_mday = 25; test[4].coorTime.tm_mon = 0; test[4].coorTime.tm_year = 116;

	test[0].kJEaten = 0;
	test[1].kJEaten = 20;
	test[2].kJEaten = 40;
	test[3].kJEaten = 60;
	test[4].kJEaten = 100;


	produce_graph(test);

	return 0;
}

void produce_graph( graphSet *test )
{
	int i, u;
	int hPixels = 500, lPixels = 500;
	FILE *image_file;
	int r, g, b;
	int diff;
	int dens, margin = 20;

	diff = diff_in_days(test[0].coorTime, test[4].coorTime);
	printf("%d\n", diff);
	dens  = lPixels / (diff + 1);


	/*image_file = fopen("graphTest.pnm", "wb");

	fputs("P6\n", image_file); 
	fprintf(image_file, "%d %d\n", hPixels, lPixels);
	fputs("255\n", image_file);*/

	determineCoorset(test, dens, hPixels, lPixels);

	/*for(i = 1; i <= hPixels; i++)
	{
		for(u = 1; u <= lPixels; u++)
		{
			r = 255; g = 255; b = 255;
			if(245 < i && i <= 256) {
				if ( || dens2 - (u % dens2) > dens2 - 5) {
					r = 255; g = 0; b = 0;
				}
			}

			fputc(r, image_file);
			fputc(g, image_file);
			fputc(b, image_file);
		}
	}*/
}

int diff_in_days( tm start_date, tm end_date )
{
	int dayDiff;
	time_t start_time, end_time;
	double seconds;

	end_date.tm_hour = 0;   end_date.tm_min = 0;   end_date.tm_sec = 0;
	start_date.tm_hour = 0; start_date.tm_min = 0; start_date.tm_sec = 0;

	start_time = mktime(&start_date);
	end_time = mktime(&end_date);

	seconds = difftime(end_time, start_time);

	dayDiff = seconds / SEC_IN_DAY;

	printf ("%d days difference\n", dayDiff);

	return dayDiff;
}

void determineCoorset(graphSet *test, int dens, int hPixels, int lPixels)
{
	int biggestKJ = test[0].kJEaten;
	int smallestKJ = test[0].kJEaten;
	int log;

	for(int i = 0; i < 5; i++)
	{
		if(biggestKJ < test[i].kJEaten)
			biggestKJ = test[i].kJEaten;
		if (smallestKJ > test[i].kJEaten)
			smallestKJ = test[i].kJEaten;
	}

	log = log10(biggestKJ);

	for(int i = 0; i < 5; i++)
	{
		printf("Log: %d\n", log);
		int value = (hPixels * (biggestKJ - smallestKJ)) / (100 * pow(10, log)) * test[i].kJEaten;
		printf("Entry: %d. PixelPos: %d. Value: %d\n", i, value, test[i].kJEaten);
	}
}