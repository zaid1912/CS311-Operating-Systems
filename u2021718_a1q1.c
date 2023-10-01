#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Insufficient arguments!\nUsage: ./matadd infilename outfilename\n");
        exit(-1);
    }

    // it is necessary that the file names are exactly "matfile1.txt" and "matfile2.txt"
    printf("\n%s\n", argv[1]);

   
    // open file 1
    FILE *matfile1 = fopen(argv[1], "r");

    // open file 2
    FILE *matfile2 = fopen(argv[2], "r");
    // check if the files are NULL
    if (matfile1 == NULL || matfile2 == NULL)
    {
        printf("Error opening file\n");
        exit(-1);
    }

    // rows and columns defined in first matrix file
    int rows1, cols1 = 0;

    fscanf(matfile1, "%d %d", &rows1, &cols1);

    printf("first line read is:  %d %d from file %s\n", rows1, cols1, argv[1]);

    // rows and columns of the second matrix file
    int rows2, cols2 = 0;

    fscanf(matfile2, "%d %d", &rows2, &cols2);

    printf("first line read is:  %d %d from file %s\n", rows2, cols2, argv[2]);

    if (cols1 != rows2)
    {
        printf("\nInput Dimentions do not match for matrix multiplication\n");
        exit(-4);
    }

    // dynamically create the first matrix
    int *mat1[rows1];

    for (int i = 0; i < rows1; i++)
    {
        mat1[i] = (int *)malloc(cols1 * sizeof(int));
    }

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols1; j++)
        {
            fscanf(matfile1, "%d", &mat1[i][j]);
            // printf("%d", mat1[i][j]);
        }
    }

    // printf("\nstored\n");

    // dynamically create the second matrix
    int *mat2[rows2];

    for (int i = 0; i < rows2; i++)
    {
        mat2[i] = (int *)malloc(cols2 * sizeof(int));
    }

    for (int i = 0; i < rows2; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            fscanf(matfile2, "%d", &mat2[i][j]);
            // printf("%d", mat2[i][j]);
        }
    }

    // dynamically create the output matrix
    int *outputmat[rows1];

    for (int i = 0; i < rows1; i++)
    {
        outputmat[i] = (int *)malloc(cols2 * sizeof(int));
    }

    // matrix multiplication and storing the result into output matrix
    for (int i = 0; i < rows1; ++i)
        for (int j = 0; j < cols2; ++j)
            for (int k = 0; k < cols1; ++k)
            {
                outputmat[i][j] += mat1[i][k] * mat2[k][j];
            }
    bool outFileExists = false;
    FILE *outfile;
    if (argv[3])
    {
        outfile = fopen(argv[3], "w");
        if (outfile == NULL)
        {
            printf("Error: failed to open output file: %s", argv[2]);
            exit(-1);
        }

        outFileExists = true;
    }
    // displaying the resultant matrix
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            //if the argv[3] exists that means we have to store the resulting matrix to that file(outfile)
            if (outFileExists)
            {
                fprintf(outfile, " %d ", outputmat[i][j]);
            }
            //otherwise just print the resultant matrix to the console
            else
            {

                printf(" %d ", outputmat[i][j]);
            }
        }
        //for going to the next line after each row is printed in the output file
        if (outFileExists)
        {
            fprintf(outfile, "\n");
        }
        else
        {

            printf("\n");
        }
    }
    // freeing the memory allocated for matrix 1 and 2
    for (int i = 0; i < rows1; i++)
    {
        free(mat1[i]);
        free(outputmat[i]);
    }

    for (int i = 0; i < rows2; i++)
    {
        free(mat2[i]);
    }

    //close the files

    fclose(matfile1);
    fclose(matfile2);

    return 0;
}