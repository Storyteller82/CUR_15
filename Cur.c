#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 30000000
#include "temp_api.h"

// ====================================================================================================
//struct sensor info[SIZE] = {0};  // создаем массив структур
long number = 0;

int main (int argc, char* argv[])
{
    printf ("\n");
    printf ("\n");
    printf ("\n");
    printf ("\n");
    printf ("This program is designed to analyze a temperature data file.\n");
    printf ("To start the program, use the following parameters:\n");
    printf ("-h to call for help\n");
    printf ("-f file name - to connect a file with data for processing\n");
    printf ("-m month number - for displaying statistics for the selected month\n");
    printf ("For example: -f file.csv -m 9\n");
    printf ("\n");
    printf ("\n");

    int month = 0; 
    char name_of_file[30] = {0};

    for(int i = 1; i < argc; i++)  // начнем с первого, т.к. нулевой в argv это название самого файла программы. 
    {
        if (argv[i][0] == '-')  // если первый символ строки "-", то это параметр и нужно выбирать из списка
        {
            switch (argv[i][1])  // смотрим второй символ строки - это и есть наш параметр
            {
                case 'h':
                {
                    printf ("parameters: [-h] halp\n"); 
                    printf ("         : [-f name_of_file.csv]\n");
                    printf ("         : [-m number_of_month] (1 - 12)\n");
                    printf ("For example: .\\Cur -f temperature_small.csv -m 9\n");
                    printf ("\n");
                    printf ("\n");
                    break;
                }
                case 'f':
                {
                    sscanf (argv[i+1], "%s", name_of_file);
                    i++;
                    break;
                }
                case 'm':
                {
                    sscanf (argv[i+1], "%d", &month);
                    i++;
                    break;
                }
                default:
                    break;
            }
        }
    }

    struct sensor* info = malloc(SIZE*sizeof(struct sensor));

    if(!info)
    {
        return -1;
    }

    int number = read_txt_file_to_info (name_of_file, info);

    //SortByDate (info, number); // Сортировка по дате // ВИСИТ НА БОЛЬШОМ ФАЙЛЕ

    //print (info, number); // нашей функцией выводим на экран // ОЧЕНЬ ДОЛГО НА БОЛЬШОМ ФАЙЛЕ
    printf ("=============================================================================\n");
    printf ("\n");
    printf ("\n");

    if ((month == 0) && (name_of_file[0] != 0))
    {
        printf ("PARAMETERS IS OK\n");
        printf ("YOUR FILE IS %s\n", name_of_file);
        printf ("\n");
        printf ("\n");
        printf ("In year average is = %lf\n", average_annual_temperature(info, number));
        printf ("In year max is = %d\n", max_annual_temperature(info, number));
        printf ("In year min is = %d\n", min_annual_temperature(info, number));
        printf ("\n");
        printf ("\n");

    } 
    else if ((name_of_file[0] != 0) && ((month > 0) && (month < 13)))
    {
        printf ("PARAMETERS IS OK\n");
        printf ("YOUR FILE IS <%s> AND MONTH IS %d\n", name_of_file, month);
        printf ("\n");
        printf ("\n");
        printf ("In month %d average is = %lf\n", month, average_month_temperature (info, number, month));
        printf ("In month max is = %d\n", max_month_temperature(info, number, month));
        printf ("In month min is = %d\n", min_month_temperature(info, number, month));
        printf ("\n");
        printf ("\n");
    }
    else
    {
        printf ("!!!!!!!!!!!!!!!!!!    PARAMETERS IS NOT OK    !!!!!!!!!!!!!!!!!!!\n");
        return 1;
    }
        
    free(info);
    
    return 0;
}