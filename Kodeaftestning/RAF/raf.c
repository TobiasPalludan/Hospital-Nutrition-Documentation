#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 15
#define DATABASE 10

struct nutrition {
    char  ingredient[MAX_CHARS];
    int   kiloJoule;
    float protein;
};

typedef struct nutrition nutrition;

nutrition make_person(char *ingredient, int kiloJoule, float protein){
        nutrition result;
        strcpy(result.ingredient, ingredient);
        result.kiloJoule = kiloJoule;
        result.protein = protein;

        return result;
    }

int main(void)
{
    char ingredient;
    char filename[] = "Nutritional database.txt";
    int len = 0;
    int i, j;
    person ID[DATABASE];
    int position[DATABASE][1];

    ID[0] = make_person("Potato",   , 3);
    ID[1] = make_person("Apple",    , 0);
    ID[2] = make_person("Cucumber", , 1);
    ID[3] = make_person("Banana",   , 1);
    ID[4] = make_person("Orange",   216, 0.9);
    ID[5] = make_person();
    ID[6] = make_person();
    ID[7] = make_person();
    ID[8] = make_person();
    ID[9] = make_person();

    printf("Enter the name of the patient you want to edit: ");
    scanf(" %s", &patient);
    
    FILE *ifp;
    ifp = fopen(filename, "w+");

    if(ifp == NULL) {
        ifp = fopen(filename, "w");
        fclose(ifp);
        ifp = fopen(filename, "w+");
    }

    fprintf(ifp, "First name:\t\tLast name:\tYear:\n");

    for (i = 0; i < DATABASE; i++)
    {
        len = ftell(ifp);
        fprintf(ifp, "%s\t%s\t%d\n",
                ID[i].firstName, ID[i].lastName, ID[i].yearBorn);
        
        for (j = 0; j < 1; j++)
        {
            position[i][j] = len;
            printf("position[%d][%d] = %d\n", i, j, len);
        }
    }

    fseek(ifp, position[1][0], SEEK_SET);

    //fputs("HEJ!", ifp);
    fprintf(ifp, "HEJ!");

    /*
     * fputs("Soren Jensen 1967 slem diare\n", ifp);
     *
     * fseek(ifp, 6, SEEK_SET);
     * fwrite("Andersen", ifp);
     */

    fclose(ifp);

    return 0;
}