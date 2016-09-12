/* Use Binary Search in order to find string in text file */
/* By Andrew Toledo */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int main(int argc, char **argv[]){

/*Comments: I used codeblocks as the IDE to compile my c program. There was an error as well as some funky stuff between program arguments
            when trying to compile (I had to directly link the textfile for fopen instead of using argv[1]). So there maybe some problems as I could not debug */
/* Other than the IDE program argument problem, the program should work correctly! */

    char letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};


	FILE *fp;
	/* Chose to limit string length for memory */
    char buffer[12]; /*initialize array to hold string (max 50 chars) */
    char searchString[12];
	int i, left, right, mid;
	int lines = 1;
	char **p;
	char ch;
    int solution = -1;




	if (argc !=  3){
		printf("Incorrect number of arguments");
		return -1;
	}



	/* Read in text file */

    fp = fopen(argv[1],"r");
    if (!fp){
        return 1;
	}

	/* Need amount of lines */
	while(!feof(fp))
	{
		ch = fgetc(fp);

		if(ch == '\n')
		{
			lines++;
		}
	}


	/*malloc first dimension */
	p = malloc(sizeof(char *) * lines);
    printf("Lines: %d\n", lines);

	/* rewind */
	rewind(fp);


    i = 1;

	/* allocate memory for each line (2nd dimension)*/
	/* Get lines one by one and put into char array */
	/* Convert all strings to lower case */

    while (fgets(buffer,sizeof(buffer), fp)){
        p[i] = malloc (sizeof(char *) * 12);
		strcpy(p[i], buffer);
		p[i][strcspn(p[i],"\n")] = '\0';
		strlwr(p[i]);
        printf("p[%d]: %s\n",i,p[i]);
        i++;

	}


    strcpy(searchString, argv[2]);
    strlwr(searchString);

    /*variables for binary search */
    left = 1;
    right = lines;


	/*Do binary search */


    while(left < right){

        /* Check for odd/even */

        if ((left + right)% 2 == 0){
            mid = (left + right)/2;
        }
        else{
            mid = ((left + right)/2) + 1;
        }




        if (strcmp(searchString,p[mid]) == 0){
            solution = mid;
            printf("String found at line: %d", solution );
            break;

        }


        else if(strcmp(searchString,p[mid]) == -1){
            right = mid - 1;

        }
        else{
            left = mid + 1;

        }

    }



    /* if not found */
	if (solution != mid){
        printf("String not found. Should be put after line: %d", mid);

	}

    /* free data */
	i = 0;

	for (i = 0; i <= lines; i++){
		free(p[i]);

	}



	fclose(fp);




    return 0;

}
