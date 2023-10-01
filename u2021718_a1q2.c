#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    //to check that the arguments should be more than 2
    if (argc < 2)
    {
        printf("Usage: %s file1.txt file2.txt file3.txt\n", argv[0]);
        return 1;
    }

    //pointer to the pointer of the files

    FILE **filearr = (FILE **)malloc((argc - 1) * sizeof(FILE *));
    //throw error if the file is null
    if (filearr == NULL)
    {
        perror("Failed to allocate memory");
        return 1;
    }

    //loop over the arguments comntaining file names and open each of the file

    for (int i = 1; i < argc; i++)
    {
        filearr[i - 1] = fopen(argv[i], "r");

        //throw an error if there is an error while opening the file
        if (filearr[i - 1] == NULL)
        {
            perror("Failed to open file");
            return 1; // Exit the program if a file can't be opened.
        }
    }
    //declare a character array to store each line after reading from the file
    char current_string[100];
    //variable that acts as a boolean. file has reached the EOF or not
    int done = 0;

    while (!done)
    {
        done = 1; // Assume all files have reached EOF
        //loop over all the files and read single line from each of them
        for (int i = 0; i < argc - 1; i++)
        {
            //store the read line in the variable current_string
            if (fgets(current_string, 100, filearr[i]) != NULL)
            {
                done = 0; // At least one file still has content
                //print the line to the console
                printf("%s", current_string);
            }
        }
    }

    //loop over every file and close it
    for (int i = 0; i < argc - 1; i++)
    {
        if (filearr[i] != NULL)
        {
            fclose(filearr[i]);
        }
    }
    //free the memory that was allocated to the pointer to the pointers of files
    free(filearr);

    return 0;
}
