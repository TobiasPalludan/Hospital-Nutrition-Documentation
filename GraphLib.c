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
int determine_dataset_coor(graphSet *test, int hPixels, int lPixels, int margin, int noEntries);
int create_label_coorset(int labelSet[][2], int diff);
int test_dataset_coor(graphSet *test, int x, int y, int noEntries);
int test_labelset_coor(int labelSet[][2], int noLabels, int x, int y);

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
	int noEntries = 5, margin = 20;
	int labelSet[20000][2];

	image_file = fopen("graphTest.pnm", "wb");

	fputs("P6\n", image_file); 
	fprintf(image_file, "%d %d\n", hPixels, lPixels);
	fputs("255\n", image_file);

	int diff = determine_dataset_coor(test, hPixels, lPixels, margin, noEntries);
	int noLabels = create_label_coorset(labelSet, diff);

	for(int y = hPixels; y >= 1; y--)
	{
		for(int x = 1; x <= lPixels; x++)
		{
			r = 255; g = 255; b = 255;
			
			if(test_labelset_coor(labelSet, noLabels, x, y))
			{
				r = 0; g = 0; b = 0;
			}

			if(test_dataset_coor(test, x, y, noEntries)) {
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

int determine_dataset_coor(graphSet *test, int hPixels, int lPixels, int margin, int noEntries)
{
	int biggestKJ = test[0].kJEaten;
	int smallestKJ = test[0].kJEaten;
	int log, dens, diff;
	int valueX, valueY;

	diff = diff_in_days(test, noEntries);
	printf("%d\n", diff);
	dens  = (lPixels - 2 * margin) / (diff + 1);

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

	return biggestKJ - smallestKJ;
}

void create_zero(int startX, int startY, int labelSet[][2], int *count)
{
	int height = 10, width = 6, thickness = 2;

	/* Top */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Venstre side */
	for(int j = 0; j < height - thickness; j++)
	{
		for(int i = 0; i < thickness; i++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j - thickness;
			*count += 1;
		}
	}

	/* Højre side */
	for(int j = 0; j < height - thickness; j++)
	{
		for(int i = 0; i < thickness; i++)
		{
			labelSet[*count][0] = startX + i + width - thickness;
			labelSet[*count][1] = startY - j - thickness;
			*count += 1;
		}
	}

	/* Bund */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j - height + thickness;
			*count += 1;
		}
	}
}

int create_one(int startX, int startY, int labelSet[][2], int *count)
{
	int height = 10, width = 6, thickness = 2;

	/* Dut i toppen */
	for(int i = 0; i < width / 3; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Stilken */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < height - thickness; j++)
		{
			labelSet[*count][0] = startX + width / 3 + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Bunden */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - height + thickness - j;
			*count += 1;
		}
	}
}

int create_two(int startX, int startY, int labelSet[][2], int *count)
{
	int height = 10, width = 6, thickness = 2;

	/* Bjælken i toppen */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Højre side */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + (width / 3 * 2) + i;
			labelSet[*count][1] = startY - thickness - j;
			*count += 1;
		}
	}

	/* Bjælken i midten */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - thickness * 2 - j;
			*count += 1;
		}
	}

	/* Venstre side */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - thickness * 3 - j;
			*count += 1;
		}
	}

	/* Bjælken i bunden */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - thickness * 4 - j;
			*count += 1;
		}
	}
}

int create_three(int startX, int startY, int labelSet[][2], int *count)
{
	int height = 10, width = 6, thickness = 2;

	/* Bjælken i toppen */
	for(int i = 0; i < width - thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Bjælken i midten */
	for(int i = 0; i < width - thickness * 1.5; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i + thickness * 0.5;
			labelSet[*count][1] = startY - j - thickness * 2;
			*count += 1;
		}
	}

	/* Bjælken i bunden */
	for(int i = 0; i < width - thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j - height + thickness;
			*count += 1;
		}
	}

	/* Venstre side  */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < height; j++)
		{
			labelSet[*count][0] = startX + i + width - thickness;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}
}

int create_four(int startX, int startY, int labelSet[][2], int *count)
{
	int height = 10, width = 6, thickness = 2;

	/* Venstre bjælke */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < height / 3 * 2; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Højre bjælke */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < height; j++)
		{
			labelSet[*count][0] = startX + width - thickness + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Midterbjælke */
	for(int i = 0; i < width - thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - thickness * 2 - j;
			*count += 1;
		}
	}
}

int create_five(int startX, int startY, int labelSet[][2], int *count)
{
	int height = 10, width = 6, thickness = 2;

	/* Bjælken i toppen */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Højre side */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - thickness - j;
			*count += 1;
		}
	}

	/* Bjælken i midten */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - thickness * 2 - j;
			*count += 1;
		}
	}

	/* Venstre side */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + (width / 3 * 2) + i;
			labelSet[*count][1] = startY - thickness * 3 - j;
			*count += 1;
		}
	}

	/* Bjælken i bunden */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - thickness * 4 - j;
			*count += 1;
		}
	}
}

int create_six(int startX, int startY, int labelSet[][2], int *count)
{
	int height = 10, width = 6, thickness = 2;

	/* Bjælken i toppen */
	for(int i = 0; i < width - thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i + thickness;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Bjælken i midten */
	for(int i = 0; i < width - thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i + thickness;
			labelSet[*count][1] = startY - j - thickness * 2;
			*count += 1;
		}
	}

	/* Bjælken i bunden */
	for(int i = 0; i < width - thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i + thickness;
			labelSet[*count][1] = startY - j - height + thickness;
			*count += 1;
		}
	}

	/* Venstre side  */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < height; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Højre side */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i + width - thickness;
			labelSet[*count][1] = startY - j - height + thickness * 2;
			*count += 1;
		}
	}
}

int create_seven(int startX, int startY, int labelSet[][2], int *count)
{
	int height = 10, width = 6, thickness = 2;

	/* Bjælken i toppen */
	for(int i = 0; i < width - thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Bjælken i højre side */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < height; j++)
		{
			labelSet[*count][0] = startX + i + width - thickness;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}
}

void create_eight(int startX, int startY, int labelSet[][2], int *count)
{
	int height = 10, width = 6, thickness = 2;

	/* Top */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Venstre side */
	for(int j = 0; j < height - thickness; j++)
	{
		for(int i = 0; i < thickness; i++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j - thickness;
			*count += 1;
		}
	}

	/* Højre side */
	for(int j = 0; j < height - thickness; j++)
	{
		for(int i = 0; i < thickness; i++)
		{
			labelSet[*count][0] = startX + i + width - thickness;
			labelSet[*count][1] = startY - j - thickness;
			*count += 1;
		}
	}

	/* Bund */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j - height + thickness;
			*count += 1;
		}
	}

	/* Midten */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i + thickness;
			labelSet[*count][1] = startY - j - thickness * 2;
			*count += 1;
		}
	}
}

int create_nine(int startX, int startY, int labelSet[][2], int *count)
{
	int height = 10, width = 6, thickness = 2;

	/* Bjælken i toppen */
	for(int i = 0; i < width - thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i + thickness;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Bjælken i midten */
	for(int i = 0; i < width - thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i + thickness;
			labelSet[*count][1] = startY - j - thickness * 2;
			*count += 1;
		}
	}

	/* Bjælken i bunden */
	for(int i = 0; i < width - thickness; i++)
	{
		for(int j = 0; j < thickness; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j - height + thickness;
			*count += 1;
		}
	}

	/* Højre side  */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < height; j++)
		{
			labelSet[*count][0] = startX + i + width - thickness;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}

	/* Venstre side */
	for(int i = 0; i < thickness; i++)
	{
		for(int j = 0; j < thickness * 3; j++)
		{
			labelSet[*count][0] = startX + i;
			labelSet[*count][1] = startY - j;
			*count += 1;
		}
	}
}

int int_pow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
           result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}

void callNumbers(int value, int labelSet[0][2], int *count, int yValue)
{
	int log = log10(value);
	int printNumber;
	int position = 5;

	for(int i = log; i >= 0; i--)
	{
		printNumber = value % int_pow(10, i + 1) / int_pow(10, i);
		printf("%d\n", value % int_pow(10, i + 1) / int_pow(10, i));

		switch(printNumber)
		{
			case 0: create_zero (position, yValue + 5, labelSet, count); break;
			case 1: create_one  (position, yValue + 5, labelSet, count); break;
			case 2: create_two  (position, yValue + 5, labelSet, count); break;
			case 3: create_three(position, yValue + 5, labelSet, count); break;
			case 4: create_four (position, yValue + 5, labelSet, count); break;
			case 5: create_five (position, yValue + 5, labelSet, count); break;
			case 6: create_six  (position, yValue + 5, labelSet, count); break;
			case 7: create_seven(position, yValue + 5, labelSet, count); break;
			case 8: create_eight(position, yValue + 5, labelSet, count); break;
			case 9: create_nine (position, yValue + 5, labelSet, count); break;
		}

		position += 7;
	}
}

int create_label_coorset(int labelSet[][2], int diff)
{
	int arrPos = 0;

	int valueY = (((500 - 2 * 20) * (diff)) / 
				 (100 * int_pow(10, 2)) * 20) + 20;

	/* Height 100 */
	callNumbers(diff / 5 * 1, labelSet, &arrPos, (((500 - 2 * 20) * (diff)) / 
				 (100 * int_pow(10, 2)) * 0) + 20);

	/* Height 200 */
	callNumbers(diff / 5 * 2, labelSet, &arrPos, (((500 - 2 * 20) * (diff)) / 
				 (100 * int_pow(10, 2)) * 20) + 20);

	/* Height 300 */
	callNumbers(diff / 5 * 3, labelSet, &arrPos, (((500 - 2 * 20) * (diff)) / 
				 (100 * int_pow(10, 2)) * 40) + 20);

	/* Height 400 */
	callNumbers(diff / 5 * 4, labelSet, &arrPos, (((500 - 2 * 20) * (diff)) / 
				 (100 * int_pow(10, 2)) * 60) + 20);

	/* Height 500 */
	callNumbers(diff / 5 * 5, labelSet, &arrPos, (((500 - 2 * 20) * (diff)) / 
				 (100 * int_pow(10, 2)) * 100) + 20);

	return arrPos;
}

int test_dataset_coor(graphSet *test, int x, int y, int noEntries)
{
	for(int i = 0; i < noEntries; i++)
	{
		if(sqrt(pow((test[i].xCoor - x), 2) + pow(test[i].yCoor - y, 2)) < 5)
			return 1;
	}

	return 0;
}

int test_labelset_coor(int labelSet[][2], int noLabelCoors, int x, int y)
{
	for(int i = 0; i < noLabelCoors; i++)
	{
		if(labelSet[i][0] == x && labelSet[i][1] == y)
			return 1;
	}

	return 0;
}