#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 15
#define DATABASE 100

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

int main(void){

    person john[100];

    john[0] = make_person("John", "Andersen", 1967);
    john[1] = make_person("Martin", "Jorgensen", 2003);
    john[2] = make_person("Susan", "Himmelbla", 1667);

    FILE *ifp;

    ifp = fopen("randomacces", "wb");

    for (int i = 0; i < 3; i++){
        fprintf(ifp, "%s %s %d\n",
                john[i].firstName, john[i].lastName, john[i].yearBorn);
    }

/*

    fputs("Soren Jensen 1967 slem diare\n", ifp);

    fseek(ifp, 6, SEEK_SET);
    fwrite("Andersen", ifp);
*/

    fclose(ifp);

    return 0;
}