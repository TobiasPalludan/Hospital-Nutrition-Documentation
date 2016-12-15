/*Header file for Nutritional_database*/
#define MAX_LINE_LEN 50
#define MAX_CHARS 25
#define DATABASE_DEPTH 15
#define MAX_INDEX 100

/* Struct, where element 0 is the meal, and element >0 is a part of the meal */
typedef struct nutrition
{
	char  ingredient[MAX_CHARS];
	int   kiloJoule;
	double protein;
	double weight;
	int noIngredients;
} nutrition;

typedef struct indexPos
{
	char ingredientName[MAX_CHARS];
	long int position;
} indexPos;

typedef struct searchTerm
{
    char ingredientName[MAX_CHARS];
    long int position;
    float weight;
} searchTerm;

/* Prototypes */
indexPos* index_database(int *indLen, FILE *dtb);
void load_index(FILE *ind, indexPos *indexArr, int indLen);
nutrition* ingredient_prompt(int indLen, indexPos indexArr[MAX_INDEX], FILE *dtb);
void stringarrToLowercase(char *stringArr);
nutrition* find_database_value(int noSearchTerms, int indLen, indexPos indexArr[MAX_INDEX],
FILE *dtb, searchTerm foodArr[MAX_LINE_LEN], nutrition* dish, double weight[]);
