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
int diff_in_days( graphSet *test, int noEntries );
void determineCoorset(graphSet *test, int dens, int hPixels, int lPixels, int margin, int diff);
int testCoordinates(graphSet *test, int x, int y, int noEntries);

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
	int diff, noEntries = 5;
	int dens, margin = 20;

	diff = diff_in_days(test, noEntries);
	printf("%d\n", diff);
	dens  = (lPixels - 2 * margin) / (diff + 1);


	image_file = fopen("graphTest.pnm", "wb");

	fputs("P6\n", image_file); 
	fprintf(image_file, "%d %d\n", hPixels, lPixels);
	fputs("255\n", image_file);

	determineCoorset(test, dens, hPixels, lPixels, margin, diff);

	for(int y = hPixels; y >= 1; y--)
	{
		for(int x = 1; x <= lPixels; x++)
		{
			r = 255; g = 255; b = 255;
			
			if(testCoordinates(test, x, y, noEntries)) {
				r = 255; g = 0; b = 0;
			}

			fputc(r, image_file);
			fputc(g, image_file);
			fputc(b, image_file);
		}
	}
}

int diff_in_days( graphSet *test, int noEntries )
{
	int dayDiff;
	time_t start_time, end_time;
	double seconds;

	for(int i = 0; i < noEntries; i++)
	{
		test[i].coorTime.tm_hour = 0; test[i].coorTime.tm_min = 0; test[i].coorTime.tm_sec = 0;
	}

	start_time = mktime(&(test[0].coorTime));
	end_time = mktime(&(test[0].coorTime));

	for(int i = 0; i < noEntries; i++)
	{
		if(mktime(&(test[i].coorTime)) < start_time)
			start_time = mktime(&(test[i].coorTime));
		if(mktime(&(test[i].coorTime)) > end_time)
			end_time = mktime(&(test[i].coorTime));
	}

	seconds = difftime(end_time, start_time);

	dayDiff = seconds / SEC_IN_DAY;

	printf ("%d days difference\n", dayDiff);

	return dayDiff;
}

void determineCoorset(graphSet *test, int dens, int hPixels, int lPixels, int margin, int diff)
{
	int biggestKJ = test[0].kJEaten;
	int smallestKJ = test[0].kJEaten;
	int log;
	int valueX, valueY;

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
		valueY = (((hPixels - 2 * margin) * (biggestKJ - smallestKJ)) / 
				(100 * pow(10, log)) * test[i].kJEaten) + margin;
		test[i].yCoor = valueY;

		valueX = (i * (lPixels - 2 * margin)) / diff + 20;
		test[i].xCoor = valueX;

		printf("Entry: %d. PixelX: %d. PixelY: %d. Value: %d\n", i, test[i].xCoor, test[i].yCoor, test[i].kJEaten);
	}
}

int testCoordinates(graphSet *test, int x, int y, int noEntries)
{
	for(int i = 0; i < noEntries; i++)
	{
		if(sqrt(pow((test[i].xCoor - x), 2) + pow(test[i].yCoor - y, 2)) < 5)
			return 1;
	}
	return 0;
}