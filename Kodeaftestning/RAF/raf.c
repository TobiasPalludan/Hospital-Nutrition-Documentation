#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 15
#define DATABASE 10

struct person {
    char    firstName[MAX_NAME];
    char    lastName[MAX_NAME];
    int     yearBorn;
};

typedef struct person person;

person make_person(char *firstName, char *lastName, int yearBorn){
        person result;
        strcpy(result.firstName, firstName); strcpy(result.lastName, lastName);
        result.yearBorn = yearBorn;

        return result;
    }

int main(void)
{
    int m = 0, len = 0, i = 0, j = 0;
    person ID[DATABASE];
    int position[DATABASE][2];

    ID[0] = make_person("John", "Andersen", 1967);
    ID[1] = make_person("Martin", "Jorgensen", 2003);
    ID[2] = make_person("Susan", "Himmelblå", 1667);
    ID[3] = make_person("Kristoffer", "Jensen", 1997);
    ID[4] = make_person("Selene", "Jacobsen", 1778);
    ID[5] = make_person("Anders", "Mikkelsen", 1889);
    ID[6] = make_person("Karoline", "Hansen", 2010);
    ID[7] = make_person("Lotte", "Boa", 1994);
    ID[8] = make_person("Mikkel", "Hansen", 1959);
    ID[9] = make_person("Lise", "Jacobsen", 1969);
    ID[10] = make_person("Jens", "Mikkelsen", 2009);
    
    FILE *ifp;

    ifp = fopen("randomacces", "wb");

    fprintf(ifp, "First name:\tLast name:\tYear:\n");

    for (i = 0; i < DATABASE; i++)
    {
        fprintf(ifp, "%s\t\t%s\t%d\n",
                ID[i].firstName, ID[i].lastName, ID[i].yearBorn);
        len = ftell(ifp);
        
        for (j = 0; j < 2; j++)
        {
            position[i][j] = len;
            printf("position[%d][%d] = %d\n", i, j, len);
        }
    }

    fseek(ifp, position[1][0], SEEK_SET);

    /*
     * fputs("Soren Jensen 1967 slem diare\n", ifp);
     *
     * fseek(ifp, 6, SEEK_SET);
     * fwrite("Andersen", ifp);
     */

    fclose(ifp);

    return 0;
}