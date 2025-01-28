#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define SIZE 30
#include "temp_api.h"

// ====================================================================================================
//int SIZE = 1;
struct sensor info[SIZE]; // создаем массив структур
int number = 0;

int main (int argc, char* argv[])
{
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

    int number = AddInfo(info); // заполняем массив структур

    print (info, number); // нашей функцией выводим на экран
    printf ("=============================================================================\n");

    if ((month == 0) && (name_of_file[0] != 0))
    {
        printf ("PARAMETERS IS OK\n");
        printf ("YOUR FILE IS %s\n", name_of_file);
        printf ("In year average is = %d\n", average_annual_temperature(info, number));
        printf ("In year max is = %d\n", max_annual_temperature(info, number));
        printf ("In year min is = %d\n", min_annual_temperature(info, number));

    } 
    else if ((name_of_file[0] != 0) && ((month > 0) && (month < 13)))
    {
        printf ("PARAMETERS IS OK\n");
        printf ("YOUR FILE IS <%s> AND MONTH IS %d\n", name_of_file, month);
        printf ("In month %d average is = %d\n", month, average_month_temperature (info, number, month));
        printf ("In month max is = %d\n", max_month_temperature(info, number, month));
        printf ("In month min is = %d\n", min_month_temperature(info, number, month));
    }
    else
    {
        printf ("!!!!!!!!!!!!!!!!!!    PARAMETERS IS NOT OK    !!!!!!!!!!!!!!!!!!!\n");
        return 1;
    }
   
        
    

    //int number = read_txt_file_to_info (name_of_file, info); // заполняем массив структур
    //printf ("min = %d\n", min_month_temperature (info, number, 9));

    //printf ("In month %d average is = %d\n", month, average_month_temperature (info, number, month)); 

    // printf ("max = %d\n", max_month_temperature (info, number, 9)); 

    //print (info, number); // нашей функцией выводим на экран
                                                                                                        /*printf ("\nSort by T\n");
                                                                                                        SortByT (info, number);
                                                                                                        print (info, number); // нашей функцией выводим на экран
                                                                                                        printf ("\nSort by Date\n");
                                                                                                        SortByDate (info, number);
                                                                                                        print (info, number); // нашей функцией выводим на экран
                                                                                                        save_bin (info, number);
                                                                                                        */
    return 0;
}