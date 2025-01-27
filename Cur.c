#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define SIZE 30
#include "temp_api.h"

// ====================================================================================================

struct sensor info[SIZE]; // создаем массив структур

int main (int argc, char* argv[])
{
    int month = 0; 
    char name_of_file[30] = {0};

    for(int i = 1; i < argc; i++)  // начнем с первого, т.к. нулевой в argv это название самого файла программы. 
    {
        

        // char* str = argv[i];
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

    if ((name_of_file[0] != 0) && ((month > 0) && (month < 13)))
        printf ("PARAMETERS IS OK +++++++++++++++++++++++++++++++++++++++++++++++\n");





int number = AddInfo (info); // заполняем массив структур
    //printf ("min = %d\n", min_month_temperature (info, number, 9));

    //printf ("average = %d\n", average_month_temperature (info, number, 9)); 

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