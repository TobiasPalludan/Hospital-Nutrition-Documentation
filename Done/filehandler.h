#define MAX_CHARS 25
#define DEPARTMENT_SIZE 15
#define NAME_SIZE 30
#define ALLERGY_SIZE 50
#define PREFERENCES_SIZE 100
#define ILLNESS_SIZE 100
#define TIME_STAMP_SIZE 18
#define DISH_NAME_SIZE 20
#define INGREDIENTS_SIZE 20
#define FILE_NAME_SIZE 25
#define LOG_FILE_SIZE 200
#define MAX_LOG_ENTRIES 10
#define PRINT_DATA_SIZE 200

#define FILE_PATH "patients/"
#define INDEX_FILE_NAME "PatientIndex.txt"


typedef struct personInfo /* Struct for containing information for a person in the system */
{
	int id;
	char department[DEPARTMENT_SIZE];
	long long int cprNumber;
	char name[NAME_SIZE];
}personInfo;

typedef struct nutritionIntake /* struck for adding a nutrition intake to a intake history */
{
	char  ingredient[INGREDIENTS_SIZE];
	int   kiloJoule;
	float protein;
	int	  amount;
} nutritionIntake;

typedef struct conditionHistory /* struct for adding a condition log to a condition history */
{
	double weight;
	double height;
	double bmi;
	int bmr;
	double temperature;
	char illness[ILLNESS_SIZE];
}conditionHistory;

typedef struct nutrition
{
	char  ingredient[MAX_CHARS];
	int   kiloJoule;
	double protein;
	double fat;
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



/*Filehandler prototypes*/
void add_person(personInfo *person);
void add_food_intake(int p_ID, nutrition intake[]);
void add_condition_log(personInfo person, conditionHistory conditionLog);
void make_patient_folder(char *string);
void make_folder(personInfo person);
void save_in_file(FILE *filePtr, char string[], char fileName[]);
void update_index_file(personInfo *person);
int find_index(FILE *filePtr, char fileName[]);
