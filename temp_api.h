#include <stdint.h>

struct sensor
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minit;
    int8_t t;
};


int average_month_temperature (struct sensor* info, int n, uint8_t month);

int8_t max_month_temperature (struct sensor* info, int n, uint8_t month);

int8_t min_month_temperature (struct sensor* info, int n, uint8_t month);

int average_annual_temperature (struct sensor* info, int n, uint16_t year);

int8_t max_annual_temperature (struct sensor* info, int n, uint16_t year);

int8_t min_annual_temperature (struct sensor* info, int n, uint16_t year);


// ==============================================================================================
// ================================= старые функции =============================================
// ==============================================================================================


unsigned int DateToInt (struct sensor* info); // Преобразовать дату в одно число

void SortByDate (struct sensor* info, int n); // Сортировка по дате

void AddRecord (struct sensor* info, int number, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minit, int8_t t);

void print (struct sensor* info, int number);

void load_bin (struct sensor* info, int number);

void save_bin (struct sensor* info, int number);

void changeIJ (struct sensor* info, int i, int j); // Обмен местами

void SortByT (struct sensor* info, int n); // Упорядочить по возрастанию температуры

int AddInfo (struct sensor* info);