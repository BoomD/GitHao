#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// display how the program should be called
void help();

// opens the corresponding file and stores the data samples into an integer array
int * readData(char *filename, int * n, int *max);

// offset the signal by offset_value and save results into a new file
void offseting(int *array, double offset_value, int file_number, int n);

// scale the signal by scale_factor and save results into a new file
void scaling(int *array, double scale_factor, int file_number, int n);

// create a copy of the raw file
void rename_file(int *array, int n, int max, char *new_file_name);

// takes an integer array and return the average value
double average(int *array, int n);

// takes an integer array and return the maximum value
int find_max(int *array, int n);

// statistic the signal and save results into a new file
void statistic(int *array, int n, int file_number);

// center the signal and save results into a new file
void center(int *array, int n, int file_number);

// takes an integer array and return the minimum value
int find_min(int *array, int n);

// normalize the signal and save results into a new file
void normalize(int *array, int n, int file_number);

int main(int argc, char *argv[])
{
    int optid, file_number, o = 0, s = 0, r = 0, n = 0, S = 0, C = 0, N = 0, max = 0;
    double offset = 0, scale = 1;
    char new_file_name[100] = {'\0'}, file_name[100]  = {'\0'};
    for(optid = 1; optid < argc && argv[optid][0] == '-'; optid++)
    {
        // help
        if (argv[optid][1] == 'h')
        {
            help();
        }

        // file number
        else if (argv[optid][1] == 'n')
        {
            if(optid + 1 < argc)
            {
                file_number = atoi(argv[++optid]);
            }
            else
            {
                printf("Usage:./My_Lab4_program 每n file_number\n");
                exit(0);
            }
        }

        // offset
        else if (argv[optid][1] == 'o')
        {
            if(optid + 1 < argc)
            {
                offset = atof(argv[++optid]);
                o = 1;
            }
            else
            {
                printf("Usage:./My_Lab4_program 每o offset\n");
                exit(0);
            }
        }

        // scale
        else if (argv[optid][1] == 's')
        {
            if(optid + 1 < argc)
            {
                scale = atof(argv[++optid]);
                s = 1;
            }
            else
            {
                printf("Usage:./My_Lab4_program 每s scale\n");
                exit(0);
            }
        }

        // rename file
        else if (argv[optid][1] == 'r')
        {
            if(optid + 1 < argc)
            {
                sprintf(new_file_name, "%s.txt", argv[++optid]);
                r = 1;
            }
            else
            {
                printf("Usage:./My_Lab4_program 每r new_file_name\n");
                exit(0);
            }
        }

        // statistics
        else if (argv[optid][1] == 'S')
        {
            S = 1;
        }

        // center
        else if (argv[optid][1] == 'C')
        {
            C = 1;
        }

        // normalize
        else if (argv[optid][1] == 'N')
        {
            N = 1;
        }

        // invalid command
        else
        {
            printf("Invalid command\n");
            help();
            exit(0);
        }
    }

    // read file
    sprintf(file_name, "Raw_data_%02d.txt", file_number);
    int *array = readData(file_name, &n, &max);

    if(o)
    {
        offseting(array, offset, file_number, n);
    }

    if(s)
    {
        scaling(array, scale, file_number, n);
    }

    if(r)
    {
        rename_file(array, n, max, new_file_name);
    }

    if(S)
    {
        statistic(array, n, file_number);
    }

    if(C)
    {
        center(array, n, file_number);
    }

    if(N)
    {
        normalize(array, n, file_number);
    }
	free(array);
    return 0;
}

void help()
{
    printf("-n file number(value needed)\n");
    printf("-o offset value(value needed)\n");
    printf("-s scale factor(value needed)\n");
    printf("-r rename files(name needed)\n");
    printf("-h help\n");
    printf("-S get statistics\n");
    printf("-C center the signal\n");
    printf("-N normalize signal\n");
}

int * readData(char *filename, int *n, int *max)
{
    FILE *f;
    if ((f = fopen(filename, "r")) == NULL)
    {
        printf("Can't read %s\n", filename);
        exit(0);
    }

    int i;
    fscanf(f, "%d %d", n, max);

    int *array = (int *)malloc(sizeof(int) **n);

    for(i = 0; i < *n; i++)
    {
        fscanf(f, "%d", &array[i]);
    }

    fclose(f);

    return array;
}

void offseting(int *array, double offset_value, int file_number, int n)
{
    char file_name[100] = {'\0'};
    sprintf(file_name, "Offset_data_%02d.txt", file_number);
    FILE *f;
    if((f = fopen(file_name, "w")) == NULL)
    {
        printf("Can't write to %s\n", file_name);
        exit(0);
    }
    fprintf(f, "%d %f\n", n, offset_value);

    int i;
    for(i = 0; i < n; i++)
    {
        fprintf(f, "%.4f\n", array[i] + offset_value);
    }

    fclose(f);
}

void scaling(int *array, double scale_factor, int file_number, int n)
{
    char file_name[100] = {'\0'};
    sprintf(file_name, "Scaled_data_%02d.txt", file_number);
    FILE *f;
    if((f = fopen(file_name, "w")) == NULL)
    {
        printf("Can't write to %s\n", file_name);
        exit(0);
    }
    fprintf(f, "%d %f\n", n, scale_factor);

    int i;
    for(i = 0; i < n; i++)
    {
        fprintf(f, "%.4f\n", array[i] * scale_factor);
    }

    fclose(f);
}

void rename_file(int *array, int n, int max, char *new_file_name)
{
    FILE *f;
    if((f = fopen(new_file_name, "w")) == NULL)
    {
        printf("Can't write to %s\n", new_file_name);
        exit(0);
    }

    fprintf(f, "%d %d\n", n, max);

    int i;
    for(i = 0; i < n; i++)
    {
        fprintf(f, "%d\n", array[i]);
    }

    fclose(f);
}

double average(int *array, int n)
{
    double total = 0;
    int i;
    for (i = 0; i < n; i++)
        total += array[i];

    return total / n;
}

int find_max(int *array, int n)
{
    int max = array[0];
    int i;
    for (i = 1; i < n; i++)
    {
        if(array[i] > max)
            max = array[i];
    }

    return max;
}

void statistic(int *array, int n, int file_number)
{
    char file_name[100] = {'\0'};
    sprintf(file_name, "Statistics_data_%02d.txt", file_number);
    FILE *f;
    if((f = fopen(file_name, "w")) == NULL)
    {
        printf("Can't write to %s\n", file_name);
        exit(0);
    }
    fprintf(f, "%.4f\n%d\n", average(array, n), find_max(array, n));
    fclose(f);
}

void center(int *array, int n, int file_number)
{
    char file_name[100] = {'\0'};
    sprintf(file_name, "Centered_data_%02d.txt", file_number);
    FILE *f;
    if((f = fopen(file_name, "w")) == NULL)
    {
        printf("Can't write to %s\n", file_name);
        exit(0);
    }
    double ave = average(array, n);
    fprintf(f, "%d %.4f\n", n, ave);

    int i;
    for(i = 0; i < n; i++) {
        fprintf(f, "%.4f\n", array[i] - ave);
    }
    fclose(f);
}

int find_min(int *array, int n)
{
    int min = array[0];
    int i;
    for (i = 1; i < n; i++)
    {
        if(array[i] < min)
            min = array[i];
    }

    return min;
}

void normalize(int *array, int n, int file_number)
{
    char file_name[100] = {'\0'};
    sprintf(file_name, "Normalized_data_%02d.txt", file_number);
    FILE *f;
    if((f = fopen(file_name, "w")) == NULL)
    {
        printf("Can't write to %s\n", file_name);
        exit(0);
    }
    int min, max;
    min = find_min(array, n);
    max = find_max(array, n);
    fprintf(f, "%d %.4f\n", n, (double)min / (max - min));

    int i;
    for(i = 0; i < n; i++) {
        fprintf(f, "%.4f\n", (double)(array[i] - min) / (max - min));
    }
    fclose(f);
}
