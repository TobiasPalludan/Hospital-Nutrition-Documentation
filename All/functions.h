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
#define PRINT_DATA_SIZE 1000

#define FILE_PATH "patients/"
#define INDEX_FILE_NAME "PatientIndex.txt"
#define clear() system("cls")

typedef struct personInfo /* Struct for containing information for a person in the system */
{
	int id;
	char department[DEPARTMENT_SIZE];
	long long int cprNumber;
	char name[NAME_SIZE];
	char allergy[ALLERGY_SIZE];
	char illness[ILLNESS_SIZE];
	double weight;
	double height;
	double bmi;
	int bmr;
	double temperature;
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
	char allergy[ALLERGY_SIZE];
}conditionHistory;

/*Lib.c prototypes*/
double BMI(double height, double weight);
double BMR(double height, double weight, long long int cpr);
int get_age(long long int cpr);
void datestamp(char output[]);
void print_warning( FILE *filPointer, int tilstand);
int warning_BMI(double BMI);

/*Filehandler prototypes*/
void add_person(personInfo *person);
void add_food_intake(personInfo person, nutritionIntake intake[]);
void add_condition_log(personInfo person, conditionHistory conditionLog);
void make_patient_folder(char *string);
void make_folder(personInfo person);
void save_in_file(FILE *filePtr, char string[], char fileName[]);
void update_index_file(personInfo *person);
int find_index(FILE *filePtr, char fileName[]);
