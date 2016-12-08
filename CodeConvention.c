/*
 * Her er en beskrivelse, som alle elsker at se.
 * På dette sted beskriver vi, hvad denne header fil gør.
 * Vi bruger tabs til indentation. Standard size er 4, men det står frit for, at
 * ændre dette individuelt.
 *
 * Altid stort begyndelsesbogstav i kommentarer, og sørg for punktum i multiline comments.
 * Punktum udelades i enden af single line comments.
 */

#include <stdio.h>

/* Dette er en single line comment. Vi bruger aldrig //, da det ikke er ASCII kode */

/*
 * Dette er en multiline comment.
 *
 * Maks linjelængde er 100 characters. Derfor skal kommentarer gerne stå før det de
 * beskriver.
 *
 * Herunder vises de gængse forkortelser. Hvis man tilføjer flere, så skriv det lige på.
 */

/*
 * arr = array
 * cnt = count
 * ptr = pointer
 * iter = iteration
 * no = number (of)
 */


/* Definitioner er ALL CAPS og adskilt med _underscore */
#define MAX_ARR_SIZE 50

int main (void)
{
	/*
	 * Navne på variabler bruger camelCase, og er uden underscore. Globale variabler er
	 * kun i aftale med resten af gruppen.
	 */

	/* Initializing variables */
	int xCoordinate, yCoordinate;
	int points[MAX_ARR_SIZE];

	/* Asking for coordinates from user */
	ask_for_coordinates(x);

	/* Bemærk, hvordan kommentarerne ovenover grupperer og beskriver vores kode */

	return 0;
}

/*
 * Vi går efter så beskrivende funktionsnavne som overhovedet muligt.
 * Funktionen skal med sit navn gerne kunne forklare, hvad den gør.
 * Vær særligt opmærksom på @param og @result, som muliggør Doxygen senere.
 * Også selv om, at de (som i det her tilfælde) er ret obvious.
 *
 * Før hver funktion gives desuden en beskrivelse som følger:
 */

/*
 * Denne funktion beder brugeren om at indtaste koordinater, og gemmer disse i et array.
 *
 * @param coordinateArr is where we store the points that is entered.
 *
 * @return noPointsCreated returns the number of points that were created.
 */
int ask_for_coordinates(int coordinateArr[])
{ /* Bemærk bracket */
	/* Code prompting for coordinates */

	if(a < b)
	{
		/* First line of code */
		/* Second line of code */
	} else { /* Eneste undtagelse til reglen om "brackets på næste linje" */
		/* First line of code */
		/* Second line of code */
	}

	if(a < b)
		/* One line of code */
	else
		/* One line of code */


	int i; /* i værdien initialiseres her, da man ikke kan gøre det i for løkken */
	for(i = 0; i < a; i++) /* i bruges altid i for-løkker */
	{
		/* Something */
		/* Something */
	}

	for(i = 0; i < a; i++)
		/* One line of code */

	/* Print statement, hvor parametre er på nye linjer. */
	printf("KDhwekdkwodjawoj %d %d %d %d\n",
		    etMegetLangtArrayNavn[0].etAndetMegetLangtNavn,
		    etVirkeligLangtNavn[0].detErDaHeltUtroligtMedDeNavne);

	return noPointsCreated;
}

void function_with_many_parameters( int xCoordinate, int yCoordinate, long veryLongName,
									char noticeTheIndentionHere)

/*
 * Last comment:
 * Vi skal neste så lidt som muligt. Hvis der er for mange nestings
 * (f.eks. if i en if, i en if, i en if), vil det blive uoverskueligt. Læg det derfor
 * i en funktion i stedet.
 */

/*
Good luck to us:
"Whenever you think, “This code needs a comment” follow that thought with,
“How could I modify the code so its purpose is obvious?”
Talk with your code, not your comments."

Links for further reading:
Best practices for commenting your code
https://improvingsoftware.com/2011/06/27/5-best-practices-for-commenting-your-code/

UCL - Good Programming Practice (presentation)
http://www.ucl.ac.uk/~ucappgu/seminars/good-practice.pdf


   _____              .___       ___.
  /     \ _____     __| _/____   \_ |__ ___.__. /\
 /  \ /  \\__  \   / __ |/ __ \   | __ <   |  | \/
/    Y    \/ __ \_/ /_/ \  ___/   | \_\ \___  | /\
\____|__  (____  /\____ |\___  >  |___  / ____| \/
        \/     \/      \/    \/       \/\/
___________
\__    ___/_ _______    ____
  |    | |  |  \__  \  /    \
  |    | |  |  // __ \|   |  \
  |____| |____/(____  /___|  /
                    \/     \/
   _____  .__ __    __          .__
  /     \ |__|  | _|  | __ ____ |  |
 /  \ /  \|  |  |/ /  |/ // __ \|  |
/    Y    \  |    <|    <\  ___/|  |__
\____|__  /__|__|_ \__|_ \\___  >____/
        \/        \/    \/    \/
 ____  __.      .__          __          _____  _____
|    |/ _|______|__| _______/  |_  _____/ ____\/ ____\___________
|   pleb   < \_  __ \  |/  ___/\   __\/  _ \   __\\   __\/ __ \_  __ \
|    |  \ |  | \/  |\___ \  |  | (  <_> )  |   |  | \  ___/|  | \/
|____|__ \|__|  |__/____  > |__|  \____/|__|   |__|  \___  >__|
        \/              \/                               \/
 ____  __.
|    |/ _|____    ____________   ___________
|      < \__  \  /  ___/\____ \_/ __ \_  __ \
|    |  \ / __ \_\___ \ |  |_> >  ___/|  | \/
|____|__ (____  /____  >|   __/ \___  >__|
        \/    \/     \/ |__|        \/
     ____.                  ___.
    |    |____    ____  ____\_ |__
    |    \__  \ _/ ___\/  _ \| __ \
/\__|    |/ __ \\  \__(  <_> ) \_\ \
\________(____  /\___  >____/|___  /
              \/     \/          \/
_________
\_   ___ \  ____ _____________ _______ ___.__.
/    \  \/_/ __ \\___   /\__  \\_  __ <   |  |
\     \___\  ___/ /    /  / __ \|  | \/\___  |
 \______  /\___  >_____ \(____  /__|   / ____|
        \/     \/      \/     \/       \/
___________   ___.   .__
\__    ___/___\_ |__ |__|____    ______
  |    | /  _ \| __ \|  \__  \  /  ___/
  |    |(  <_> ) \_\ \  |/ __ \_\___ \
  |____| \____/|___  /__(____  /____  >
                   \/        \/     \/
*/
