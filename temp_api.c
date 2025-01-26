#include <stdio.h>
#include <stdint.h>
//#include "Cur.c"
#include "temp_api.h"




/*struct sensor
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minit;
    int8_t t;
};*/



int average_month_temperature(struct sensor *info, int n, uint8_t month)
{
    int sum = 0, cnt = 0;

    for (int i = 0; i < n; i++)
    {
        if (info[i].month == month)
        {
            sum = sum + info[i].t;
            cnt++;
        }
    }
    return sum / cnt;
}

int8_t max_month_temperature(struct sensor *info, int n, uint8_t month)
{
    int8_t tmp = -120;

    for (int i = 0; i < n; i++)
    {
        if (info[i].month == month)
        {
            if (tmp <= info[i].t)
                tmp = info[i].t;
        }
    }
    return tmp;
}

int8_t min_month_temperature(struct sensor *info, int n, uint8_t month)
{
   int8_t tmp = 120;

    for (int i = 0; i < n; i++)
    {
        if (info[i].month == month)
        {
            if (tmp >= info[i].t)
                tmp = info[i].t;
        }
    }
    return tmp;
}

int average_annual_temperature(struct sensor *info, int n, uint16_t year)
{
    int sum = 0, cnt = 0;

    for (int i = 0; i < n; i++)
    {
        if (info[i].year == year)
        {
            sum += info[i].t;
            cnt++;
        }
    }
    return sum / cnt;
}

int8_t max_annual_temperature(struct sensor *info, int n, uint16_t year)
{
    int8_t tmp = -120;

    for (int i = 0; i < n; i++)
    {
        if (info[i].year == year)
        {
            if (tmp <= info[i].t)
                tmp = info[i].t;
        }
    }
    return tmp;
}

int8_t min_annual_temperature(struct sensor *info, int n, uint16_t year)
{
    int8_t tmp = 120;

    for (int i = 0; i < n; i++)
    {
        if (info[i].year == year)
        {
            if (tmp >= info[i].t)
                tmp = info[i].t;
        }
    }
    return tmp;
}






// ==============================================================================================
// ================================= старые функции =============================================
// ==============================================================================================






void changeIJ (struct sensor* info, int i, int j) // Обмен местами
{
    struct sensor temp;
    temp = info[i];
    info[i] = info[j];
    info[j] = temp;    
}

void SortByT (struct sensor* info, int n) // Упорядочить по возрастанию температуры
{
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (info[i].t >= info[j].t)
                changeIJ(info, i, j);
}
//==================================================================================================


unsigned int DateToInt(struct sensor *info) // Преобразовать дату в одно число
{
    return info->year << 21 |info->month << 17 | info->day << 12 | info->hour << 7 | info->minit;
} // --------------------^^-----------------^^----------------^^-----------------^ все влезло в 4 байта

void SortByDate (struct sensor* info, int n) // Сортировка по дате
{
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (DateToInt (info + i) >= DateToInt (info +j))
                changeIJ (info, i, j);
}
//==================================================================================================

void AddRecord (struct sensor* info, int number, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minit, int8_t t)
{
    info[number].year = year;
    info[number].month = month;
    info[number].day = day;
    info[number].hour = hour;
    info[number].minit = minit;
    info[number].t = t;
}

// =================================================================================================

void print (struct sensor* info, int number)
{
    printf ("================================================\n");
        for (int i = 0; i < number; i++)
            printf ("%04d-%02d-%02d %02d:%02d t = %3d\n", info[i].year, info[i].month, info[i].day, info[i].hour, info[i].minit, info[i].t);
}

// ====================================================================================================
void load_bin (struct sensor* info, int number)
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