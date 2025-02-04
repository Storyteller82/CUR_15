#include <stdio.h>
#include <stdint.h>
#include "temp_api.h"

float average_month_temperature(struct sensor *info, long n, uint8_t month)
{
    long sum = 0, cnt = 0;

    for (long i = 0; i < n; i++)
    {
        if (info[i].month == month)
        {
            sum = sum + info[i].t;
            cnt++;
        }
    }
    return ((float) sum / (float) cnt);
}

int8_t max_month_temperature(struct sensor *info, long n, uint8_t month)
{
    int8_t tmp = -120; 


    for (long i = 0; i < n; i++)
    {
        if (info[i].month == month)
        {
            if (tmp <= info[i].t)
                tmp = info[i].t;
        }
    }
    return tmp;
}

int8_t min_month_temperature(struct sensor *info, long n, uint8_t month)
{
   int8_t tmp = 120;

    for (long i = 0; i < n; i++)
    {
        if (info[i].month == month)
        {
            if (tmp >= info[i].t)
                tmp = info[i].t;
        }
    }
    return tmp;
}

float average_annual_temperature(struct sensor *info, long n)
{
    long sum = 0, cnt = 0;

    for (long i = 0; i < n; i++)
    {
       // if (info[i].year == year)
        //{
            sum += info[i].t;
            cnt++;
        //}
    }
    return ((float) sum / (float) cnt);
}

int8_t max_annual_temperature(struct sensor *info, long n)
{
    int8_t tmp = -120;

    for (long i = 0; i < n; i++)
    {
       // if (info[i].year == year)
        //{
            if (tmp <= info[i].t)
                tmp = info[i].t;
       // }
    }
    return tmp;
}

int8_t min_annual_temperature(struct sensor *info, long n)
{
    int8_t tmp = 120;

    for (long i = 0; i < n; i++)
    {
        //if (info[i].year == year)
        //{
            if (tmp >= info[i].t)
                tmp = info[i].t;
        //}
    }
    return tmp;
}

//==================================================================================================================================================

long read_txt_file_to_info (char *name_of_file, struct sensor* info)
{
    FILE* f;
    f = fopen (name_of_file, "r");
    if (f == NULL)
    {
        printf ("Error open file\n");
    }
    else 
    {
        printf ("OPEN FILE IS OK ++++++++++++++\n");
    }

    long counter = 0;
    int n_scan = 0;
    int year; 
    int month;
    int day; 
    int hour;
    int minit; 
    int t;

    while ((n_scan = fscanf (f, "%4u;%u;%u;%d;%d;%d;\n", &year, &month, &day, &hour, &minit, &t)) > 0)
    {
        if (n_scan < 6)
        {
            char s[20], c;
            n_scan = fscanf(f, "%[^\n]%c", s, &c);
            printf("Wrong format in line %s\n", s);
            continue;
        }
        else
        {
            AddRecord (info, counter++, year, month, day, hour, minit, t);
        }
    }
    fclose (f);
    return counter;
}


// ==============================================================================================
// ================================= старые функции =============================================
// ==============================================================================================


void changeIJ (struct sensor* info, long i, long j) // Обмен местами
{
    struct sensor temp;
    temp = info[i];
    info[i] = info[j];
    info[j] = temp;    
}

void SortByT (struct sensor* info, long n) // Упорядочить по возрастанию температуры
{
    for (long i = 0; i < n; ++i)
        for (long j = i; j < n; ++j)
            if (info[i].t >= info[j].t)
                changeIJ(info, i, j);
}
//==================================================================================================


unsigned int DateToInt(struct sensor *info) // Преобразовать дату в одно число
{
    return info->year << 21 |info->month << 17 | info->day << 12 | info->hour << 7 | info->minit;
} // --------------------^^-----------------^^----------------^^-----------------^ все влезло в 4 байта

void SortByDate (struct sensor* info, long n) // Сортировка по дате
{
    for (long i = 0; i < n; ++i)
        for (long j = i; j < n; ++j)
            if (DateToInt (info + i) >= DateToInt (info + j))
                changeIJ (info, i, j);
}
//==================================================================================================

void AddRecord (struct sensor* info, long number, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minit, int8_t t)
{
    //printf ("ADD_RECORD IS OK +++++++++++++++++++++++++++++++++++++++++++++++\n");
    info[number].year = year;
    info[number].month = month;
    info[number].day = day;
    info[number].hour = hour;
    info[number].minit = minit;
    info[number].t = t;
}

// =================================================================================================

void print (struct sensor* info, long number)
{
    printf ("================================================\n");
        for (long i = 0; i < number; i++)
            printf ("%04d-%02d-%02d %02d:%02d t = %3d\n", info[i].year, info[i].month, info[i].day, info[i].hour, info[i].minit, info[i].t);
}

// ====================================================================================================
/*void load_bin (struct sensor* info, int number)
{
    FILE* f = fopen ("sensor.bin", "rb");
    // ghjdthrf yf jnrhsnbt
    fread (info, number*sizeof(struct sensor), 1, f);
    fclose (f);
}

void save_bin (struct sensor* info, int number)
{
    FILE* f = fopen ("sensor.bin", "wb");
    // ghjdthrf yf jnrhsnbt
    fwrite (info, number*sizeof(struct sensor), 1, f);
    fclose (f);
}

int AddInfo (struct sensor* info)
{
    int counter = 0;
        AddRecord (info, counter++, 2021,9,16,10,10,20);
        AddRecord (info, counter++, 2022,9,2,13,13,-1);
        AddRecord (info, counter++, 2021,1,7,15,15,8);
        AddRecord (info, counter++, 2021,9,5,17,17,1);
        AddRecord (info, counter++, 2021,9,16,10,11,9);
        AddRecord (info, counter++, 2022,9,2,13,14,-9);
        AddRecord (info, counter++, 2021,1,7,15,15,8);
        AddRecord (info, counter++, 2021,1,5,17,16,1);
        AddRecord (info, counter++, 2021,1,16,10,17,9);
        AddRecord (info, counter++, 2022,9,2,13,18,-3);
        AddRecord (info, counter++, 2021,1,7,15,19,8);
        AddRecord (info, counter++, 2021,1,5,17,20,1);
        AddRecord (info, counter++, 2021,9,16,10,21,9);
        AddRecord (info, counter++, 2022,9,2,13,22,-9);
        AddRecord (info, counter++, 2021,1,7,15,23,8);
        AddRecord (info, counter++, 2021,9,5,17,24,1);
        return counter;
}
*/