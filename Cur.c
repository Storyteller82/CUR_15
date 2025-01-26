#include <stdio.h>
#include <stdint.h>
//#include <string.h>
#define SIZE 30



/*struct sensor
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minit;
    int8_t t;
};
*/

#include "temp_api.h"
// ====================================================================================================
struct sensor info[SIZE]; // создаем массив структур
int main (void)
{
    

    int number = AddInfo (info); // заполняем массив структур

    printf ("min = %d\n", min_month_temperature (info, number, 9));

    printf ("average = %d\n", average_month_temperature (info, number, 9)); 

     printf ("max = %d\n", max_month_temperature (info, number, 9)); 


    print (info, number); // нашей функцией выводим на экран
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